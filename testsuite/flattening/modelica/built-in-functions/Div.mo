// name: Div
// keywords: div
// status: correct
//
// Tests the built-in div function
//

model Div
  Real r;
equation
  r = div(45, 4);
  annotation(__OpenModelica_commandLineOptions="-d=-newInst");
end Div;

// Result:
// class Div
//   Real r;
// equation
//   r = 11.0;
// end Div;
// endResult
