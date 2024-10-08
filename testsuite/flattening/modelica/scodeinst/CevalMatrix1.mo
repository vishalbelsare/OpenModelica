// name: CevalMatrix1
// keywords:
// status: correct
//
//

model CevalMatrix1
  parameter Integer N = 3;
  Real B[N, 6, 3*N];
equation
  for i in 2:N - 1 loop
    B[i,:,:] = [zeros(6, 3*(i - 2)), identity(6), zeros(6, 3*(N - i))];
  end for;
end CevalMatrix1;

// Result:
// class CevalMatrix1
//   final parameter Integer N = 3;
//   Real B[1,1,1];
//   Real B[1,1,2];
//   Real B[1,1,3];
//   Real B[1,1,4];
//   Real B[1,1,5];
//   Real B[1,1,6];
//   Real B[1,1,7];
//   Real B[1,1,8];
//   Real B[1,1,9];
//   Real B[1,2,1];
//   Real B[1,2,2];
//   Real B[1,2,3];
//   Real B[1,2,4];
//   Real B[1,2,5];
//   Real B[1,2,6];
//   Real B[1,2,7];
//   Real B[1,2,8];
//   Real B[1,2,9];
//   Real B[1,3,1];
//   Real B[1,3,2];
//   Real B[1,3,3];
//   Real B[1,3,4];
//   Real B[1,3,5];
//   Real B[1,3,6];
//   Real B[1,3,7];
//   Real B[1,3,8];
//   Real B[1,3,9];
//   Real B[1,4,1];
//   Real B[1,4,2];
//   Real B[1,4,3];
//   Real B[1,4,4];
//   Real B[1,4,5];
//   Real B[1,4,6];
//   Real B[1,4,7];
//   Real B[1,4,8];
//   Real B[1,4,9];
//   Real B[1,5,1];
//   Real B[1,5,2];
//   Real B[1,5,3];
//   Real B[1,5,4];
//   Real B[1,5,5];
//   Real B[1,5,6];
//   Real B[1,5,7];
//   Real B[1,5,8];
//   Real B[1,5,9];
//   Real B[1,6,1];
//   Real B[1,6,2];
//   Real B[1,6,3];
//   Real B[1,6,4];
//   Real B[1,6,5];
//   Real B[1,6,6];
//   Real B[1,6,7];
//   Real B[1,6,8];
//   Real B[1,6,9];
//   Real B[2,1,1];
//   Real B[2,1,2];
//   Real B[2,1,3];
//   Real B[2,1,4];
//   Real B[2,1,5];
//   Real B[2,1,6];
//   Real B[2,1,7];
//   Real B[2,1,8];
//   Real B[2,1,9];
//   Real B[2,2,1];
//   Real B[2,2,2];
//   Real B[2,2,3];
//   Real B[2,2,4];
//   Real B[2,2,5];
//   Real B[2,2,6];
//   Real B[2,2,7];
//   Real B[2,2,8];
//   Real B[2,2,9];
//   Real B[2,3,1];
//   Real B[2,3,2];
//   Real B[2,3,3];
//   Real B[2,3,4];
//   Real B[2,3,5];
//   Real B[2,3,6];
//   Real B[2,3,7];
//   Real B[2,3,8];
//   Real B[2,3,9];
//   Real B[2,4,1];
//   Real B[2,4,2];
//   Real B[2,4,3];
//   Real B[2,4,4];
//   Real B[2,4,5];
//   Real B[2,4,6];
//   Real B[2,4,7];
//   Real B[2,4,8];
//   Real B[2,4,9];
//   Real B[2,5,1];
//   Real B[2,5,2];
//   Real B[2,5,3];
//   Real B[2,5,4];
//   Real B[2,5,5];
//   Real B[2,5,6];
//   Real B[2,5,7];
//   Real B[2,5,8];
//   Real B[2,5,9];
//   Real B[2,6,1];
//   Real B[2,6,2];
//   Real B[2,6,3];
//   Real B[2,6,4];
//   Real B[2,6,5];
//   Real B[2,6,6];
//   Real B[2,6,7];
//   Real B[2,6,8];
//   Real B[2,6,9];
//   Real B[3,1,1];
//   Real B[3,1,2];
//   Real B[3,1,3];
//   Real B[3,1,4];
//   Real B[3,1,5];
//   Real B[3,1,6];
//   Real B[3,1,7];
//   Real B[3,1,8];
//   Real B[3,1,9];
//   Real B[3,2,1];
//   Real B[3,2,2];
//   Real B[3,2,3];
//   Real B[3,2,4];
//   Real B[3,2,5];
//   Real B[3,2,6];
//   Real B[3,2,7];
//   Real B[3,2,8];
//   Real B[3,2,9];
//   Real B[3,3,1];
//   Real B[3,3,2];
//   Real B[3,3,3];
//   Real B[3,3,4];
//   Real B[3,3,5];
//   Real B[3,3,6];
//   Real B[3,3,7];
//   Real B[3,3,8];
//   Real B[3,3,9];
//   Real B[3,4,1];
//   Real B[3,4,2];
//   Real B[3,4,3];
//   Real B[3,4,4];
//   Real B[3,4,5];
//   Real B[3,4,6];
//   Real B[3,4,7];
//   Real B[3,4,8];
//   Real B[3,4,9];
//   Real B[3,5,1];
//   Real B[3,5,2];
//   Real B[3,5,3];
//   Real B[3,5,4];
//   Real B[3,5,5];
//   Real B[3,5,6];
//   Real B[3,5,7];
//   Real B[3,5,8];
//   Real B[3,5,9];
//   Real B[3,6,1];
//   Real B[3,6,2];
//   Real B[3,6,3];
//   Real B[3,6,4];
//   Real B[3,6,5];
//   Real B[3,6,6];
//   Real B[3,6,7];
//   Real B[3,6,8];
//   Real B[3,6,9];
// equation
//   B[2,1,1] = 1.0;
//   B[2,1,2] = 0.0;
//   B[2,1,3] = 0.0;
//   B[2,1,4] = 0.0;
//   B[2,1,5] = 0.0;
//   B[2,1,6] = 0.0;
//   B[2,1,7] = 0.0;
//   B[2,1,8] = 0.0;
//   B[2,1,9] = 0.0;
//   B[2,2,1] = 0.0;
//   B[2,2,2] = 1.0;
//   B[2,2,3] = 0.0;
//   B[2,2,4] = 0.0;
//   B[2,2,5] = 0.0;
//   B[2,2,6] = 0.0;
//   B[2,2,7] = 0.0;
//   B[2,2,8] = 0.0;
//   B[2,2,9] = 0.0;
//   B[2,3,1] = 0.0;
//   B[2,3,2] = 0.0;
//   B[2,3,3] = 1.0;
//   B[2,3,4] = 0.0;
//   B[2,3,5] = 0.0;
//   B[2,3,6] = 0.0;
//   B[2,3,7] = 0.0;
//   B[2,3,8] = 0.0;
//   B[2,3,9] = 0.0;
//   B[2,4,1] = 0.0;
//   B[2,4,2] = 0.0;
//   B[2,4,3] = 0.0;
//   B[2,4,4] = 1.0;
//   B[2,4,5] = 0.0;
//   B[2,4,6] = 0.0;
//   B[2,4,7] = 0.0;
//   B[2,4,8] = 0.0;
//   B[2,4,9] = 0.0;
//   B[2,5,1] = 0.0;
//   B[2,5,2] = 0.0;
//   B[2,5,3] = 0.0;
//   B[2,5,4] = 0.0;
//   B[2,5,5] = 1.0;
//   B[2,5,6] = 0.0;
//   B[2,5,7] = 0.0;
//   B[2,5,8] = 0.0;
//   B[2,5,9] = 0.0;
//   B[2,6,1] = 0.0;
//   B[2,6,2] = 0.0;
//   B[2,6,3] = 0.0;
//   B[2,6,4] = 0.0;
//   B[2,6,5] = 0.0;
//   B[2,6,6] = 1.0;
//   B[2,6,7] = 0.0;
//   B[2,6,8] = 0.0;
//   B[2,6,9] = 0.0;
// end CevalMatrix1;
// endResult
