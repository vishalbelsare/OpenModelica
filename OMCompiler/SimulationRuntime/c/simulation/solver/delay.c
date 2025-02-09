/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF THE BSD NEW LICENSE OR THE
 * GPL VERSION 3 LICENSE OR THE OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs: http://www.openmodelica.org or
 * http://www.ida.liu.se/projects/OpenModelica, and in the OpenModelica
 * distribution. GNU version 3 is obtained from:
 * http://www.gnu.org/copyleft/gpl.html. The New BSD License is obtained from:
 * http://www.opensource.org/licenses/BSD-3-Clause.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, EXCEPT AS
 * EXPRESSLY SET FORTH IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE
 * CONDITIONS OF OSMC-PL.
 *
 */

#if !defined(OMC_NDELAY_EXPRESSIONS) || OMC_NDELAY_EXPRESSIONS>0

/*! \file delay.c
 */

#include "delay.h"
#include "epsilon.h"
#include "../../util/omc_error.h"
#include "../../util/ringbuffer.h"
#include "../../openmodelica.h"

#include <stdio.h>
#include <stdlib.h>

/* Private prototypes */
void printDelayBuffer(void* data, int stream, void* elemPointer);


/**
 * @brief Find row with greatest time that is smaller than or equal to 'time'.
 *
 * @param[in] time          Time value to search for.
 * @param[in] delayStruct   Ringbuffer with stored delay values.
 *                          Looks like a matrix with columns of type TIME_AND_VALUE.
 * @return int              Row with maximum time value smaller equal to time.
 */
static int findTime(double time, RINGBUFFER *delayStruct)
{
  int end = ringBufferLength(delayStruct);
  int pos = 0;
  double curTime, prevTime;
  TIME_AND_VALUE* bufferElem;

  /* Check if ring buffer is valid */
  assertStreamPrint(NULL, ringBufferLength(delayStruct) > 0, "delay: In function findTime\nEmpty ring buffer.");
  bufferElem = getRingData(delayStruct, pos);
  curTime = bufferElem->t;

  /* If searched time is smaller then first element return first position */
  if (time < curTime) {
    return pos;
  }

  /* Search for time starting at begin of ring buffer */
  while (pos < end-1) {
    pos++;
    bufferElem = getRingData(delayStruct, pos);
    prevTime = curTime;
    curTime = bufferElem->t;

    if (curTime > time) {
      pos--;
      // Found time in previous step
      break;
    }
  }
  assertStreamPrint(NULL, pos < end, "delay: In function findTime\nCould not find time");

  return pos;
}


/**
 * @brief Look for events between `oldTime` and `newTime`
 *
 * @param[in] time          Time value to search for.
 * @param[in] delayStruct   Ringbuffer with stored delay values.
 *                          Looks like a matrix with columns of type TIME_AND_VALUE.
 * @return modelica_boolean Boolean indicating if an event was found.
 */
static modelica_boolean searchEvent(double time, RINGBUFFER *delayStruct)
{
  int end = ringBufferLength(delayStruct);
  int pos = 0;
  double curTime, prevTime;
  TIME_AND_VALUE* bufferElem;
  modelica_boolean foundEvent = FALSE;

  bufferElem = getRingData(delayStruct, pos);
  curTime = bufferElem->t;

  /* If searched time is smaller then first element we have no event */
  if (time < curTime) {
    return FALSE;
  }

  /* Search for time starting at begin of ring buffer */
  while (pos < end-1) {
    pos++;
    bufferElem = getRingData(delayStruct, pos);
    prevTime = curTime;
    curTime = bufferElem->t;

    /* Check for an event */
    if (fabs(prevTime-curTime) < 1e-12) {
      foundEvent = TRUE;
      break;
    }
    if (curTime > time) {
      break;
    }
  }

  if (foundEvent) {
    printRingBuffer(delayStruct, OMC_LOG_DEBUG, printDelayBuffer);
  }

  return foundEvent;
}


/**
 * @brief Store expression value in delay.
 *
 * @param data          Storing all simulation/model data.
 * @param threadData    Used for error handling.
 * @param exprNumber    Index of delay.
 * @param exprValue     Value to store in delay ringbuffer.
 * @param delayTime     Time to delay expValue.
 * @param delayMax      Maximum allowed delay time, defaults to delayTime.
 */
void storeDelayedExpression(DATA* data, threadData_t *threadData, int exprNumber, double exprValue, double delayTime, double delayMax)
{
  RINGBUFFER* delayStruct = data->simulationInfo->delayStructure[exprNumber];
  int row;
  int length = ringBufferLength(delayStruct);
  double time = data->localData[0]->timeValue;
  TIME_AND_VALUE tpl;
  TIME_AND_VALUE* lastElem;

  assertStreamPrint(threadData, exprNumber < data->modelData->nDelayExpressions, "storeDelayedExpression: invalid expression number %d", exprNumber);
  assertStreamPrint(threadData, 0 <= exprNumber, "storeDelayedExpression: invalid expression number %d", exprNumber);

  /* Check if time is greater equal then last stored time in delay structure */
  /* ph: Is this needed because of event search? */
  if (length > 0) {
    lastElem = getRingData(delayStruct, length-1);
    while (time < lastElem->t && length > 0) {
      removeLastRingData(delayStruct,1);
      length = ringBufferLength(delayStruct);
      if (length > 0) {
        lastElem = getRingData(delayStruct, length-1);
      }
    }
  }

  /* Check if (time,value) pair is already saved
   * This should happen after an event was found and the event iteration finished */
  if (length > 0) {
    if (fabs(lastElem->t-time) < 1e-10 && fabs(lastElem->value-exprValue) < 1e-10) {
      /* Dequeue no longer needed values from ring buffer */
      row = findTime(time-delayTime+1e-10, delayStruct);
      if (row > 0) {
        dequeueNFirstRingDatas(delayStruct, row);
      }
      return;
    }
  }

  /* Append expression value to delay ring buffer */
  tpl.t = time;
  tpl.value = exprValue;
  appendRingData(delayStruct, &tpl);

  /* Dequeue no longer needed values from ring buffer */
  row = findTime(time-delayTime+DBL_EPSILON, delayStruct);
  if (row > 0 && !searchEvent(time-delayTime+DBL_EPSILON, delayStruct)) {
    dequeueNFirstRingDatas(delayStruct, row);
  }

  /* Debug print */
  infoStreamPrint(OMC_LOG_DELAY, 0, "storeDelayed[%d] (%g,%g) position=%d", exprNumber, time, exprValue, ringBufferLength(delayStruct));
  printRingBuffer(delayStruct, OMC_LOG_DELAY, printDelayBuffer);
}


/**
 * @brief Evaluate delay expression.
 *
 * @param data          Pointer to data.
 * @param threadData    Pointer to thread data.
 * @param exprNumber    Index of delay expression.
 * @param exprValue     Value of delay expression.
 * @param delayTime     Amount of time exprValue should be delayed.
 * @param delayMax      Maximum time to delay exprValue.
 * @return double       Return delayed value.
 */
double delayImpl(DATA* data, threadData_t *threadData, int exprNumber, double exprValue, double delayTime, double delayMax)
{
  RINGBUFFER* delayStruct = data->simulationInfo->delayStructure[exprNumber];
  double timeStamp;
  double time0, time1, value0, value1;
  double timedif;
  double dt0;
  double dt1;
  double retVal;
  int i;
  int length = ringBufferLength(delayStruct);
  double time = data->localData[0]->timeValue;

  infoStreamPrint(OMC_LOG_DELAY, 0, "delayImpl: exprNumber = %d, exprValue = %g, time = %g, delayTime = %g", exprNumber, exprValue, time, delayTime);

  /* Check for errors */
  assertStreamPrint(threadData, 0 <= exprNumber, "invalid exprNumber = %d", exprNumber);
  assertStreamPrint(threadData, exprNumber < data->modelData->nDelayExpressions, "invalid exprNumber = %d", exprNumber);
  assertStreamPrint(threadData, delayTime >= 0, "Negative delay requested: delayTime = %g", delayTime);
  assertStreamPrint(threadData, delayTime >= DASSL_STEP_EPS, "delayImpl: delayTime is zero or too small.\n" \
    "OpenModelica doesn't support delay operator with zero delay time.");
  assertStreamPrint(threadData, delayTime <= delayMax, "Too large delay requested: delayTime = %g, delayMax = %g", delayTime, delayMax);

  /* Return expression value before simulation start */
  if (time <= data->simulationInfo->startTime) {
    return exprValue;
  }

  /*  Empty delay buffer at initialization phase */
  if (length == 0) {
    infoStreamPrint(OMC_LOG_EVENTS, 0, "delayImpl: Missing initial value, using argument value %g instead.", exprValue);
    return exprValue;
  }

  /* Return oldest element in ring buffer */
  if (time <= data->simulationInfo->startTime + delayTime) {
    return ((TIME_AND_VALUE*)getRingData(delayStruct, 0))->value;
  }
  /* return expr(time-delayTime) */
  else {
    timeStamp = time - delayTime;

    /* find the row for the lower limit */
    if (timeStamp > ((TIME_AND_VALUE*)getRingData(delayStruct, length - 1))->t) {
      /* delay between the last accepted time step and the current time */
      time0 = ((TIME_AND_VALUE*)getRingData(delayStruct, length - 1))->t;
      value0 = ((TIME_AND_VALUE*)getRingData(delayStruct, length - 1))->value;
      time1 = time;
      value1 = exprValue;
    } else {
      i = findTime(timeStamp, delayStruct);
      assertStreamPrint(threadData, i < length, "%d = i < length = %d", i, length);
      time0 = ((TIME_AND_VALUE*)getRingData(delayStruct, i))->t;
      value0 = ((TIME_AND_VALUE*)getRingData(delayStruct, i))->value;

      /* was it the last value? */
      if (i+1 == length) {
        return value0;
      }
      time1 = ((TIME_AND_VALUE*)getRingData(delayStruct, i+1))->t;
      value1 = ((TIME_AND_VALUE*)getRingData(delayStruct, i+1))->value;
    }
    /* Return left value */
    if (time0 == timeStamp) {
      return value0;
    }
    /* Return right value */
    else if (time1 == timeStamp) {
      return value1;
    }
    /* linear interpolation */
    /* FIXME instead of linear, do the same interpolation order as the integrator */
    else {
      timedif = time1 - time0;
      dt0 = time1 - timeStamp;
      dt1 = timeStamp - time0;
      retVal = (value0 * dt0 + value1 * dt1) / timedif;
      return retVal;
    }
  }
}


/**
 * @brief Returns value of zero crossing at current simulation time.
 *
 * @param data            Storing all simulation/model data.
 * @param threadData      Used for error handling.
 * @param exprNumber      Index of delay.
 * @param relationIndex   Index of relation used for zero crossing.
 * @param delayTime       Time to delay expValue.
 * @return double         Value of zeroCrossing at current simulation time.
 */
double delayZeroCrossing(DATA* data, threadData_t *threadData, unsigned int exprNumber, unsigned int relationIndex, double delayTime)
{
  RINGBUFFER* delayStruct = data->simulationInfo->delayStructure[exprNumber];
  double zeroCrossingValue = data->simulationInfo->zeroCrossingsPre[relationIndex];
  double time = data->localData[0]->timeValue;

  if (ringBufferLength(delayStruct) == 0) {
    return zeroCrossingValue;
  }

  /* Flip sign of ZC if an event was found */
  if (searchEvent(time - delayTime, delayStruct)) {
    return -zeroCrossingValue;
  } else {
    return zeroCrossingValue;
  }
}


/**
 * @brief Print transported quantity data to stream.
 *
 * Prints tuple (time, value).
 *
 * @param data          Void pointer to bufferElemData.
 *                      Will be casted to TIME_AND_VALUE*.
 * @param stream        Stream of OMC_LOG_STREAM type.
 * @param elemPointer   Address of element storing this data.
 */
void printDelayBuffer(void* data, int stream, void* elemPointer)
{
  TIME_AND_VALUE* bufferElemData = (TIME_AND_VALUE*) data;
  infoStreamPrint(stream, 0, "%p: (%e,%e)", elemPointer, bufferElemData->t, bufferElemData->value);
}

#endif
