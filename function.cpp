#include "function.h"
#include <list> 

double viewingMatrix[16];
double modelMatrix[16]; 
double stack[32][16];
type polygonType;
int stackCounter;

void normalize(double * vector, int count);
void translate(double * matrix, double x, double y, double z);

void viewNormalization(double * eye, double * center, double * up, double * width, double * height, double * length) {
  double w[3], u[3], v[3];
  double matrix2[16], resultMatrix[16];
  double a, b; 

  w[0] = eye[0] - center[0];
  w[1] = eye[1] - center[1];
  w[2] = eye[2] - center[2];

  normalize(w, 3);

  crossproduct(up, w, u);

  normalize(u, 3);

  crossproduct(w, u, v);

  matrix2[0] = u[0];
  matrix2[1] = u[1];
  matrix2[2] = u[2];
  matrix2[3] = 0;

  matrix2[4] = v[0];
  matrix2[5] = v[1];
  matrix2[6] = v[2];
  matrix2[7] = 0;

  matrix2[8] = w[0];
  matrix2[9] = w[1];
  matrix2[10] = w[2];
  matrix2[11] = 0;

  matrix2[12] = 0;
  matrix2[13] = 0;
  matrix2[14] = 0;
  matrix2[15] = 1;

  printmat(4, 4, matrix2);

  identity(4, viewingMatrix);
  translate(viewingMatrix, -eye[0], -eye[1], -eye[2]);

  printmat(4,4, viewingMatrix);
  multiplication(4,4,4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  printmat(4, 4, viewingMatrix);


  // shear
  a = ((width[0] + width[1]) / 2) / length[0];
  b = ((height[0] + height[1]) / 2) / length[0];

  cout << "a: " << a << " b: " << b << endl;
  identity(4, matrix2); 
  matrix2[2] = a;
  matrix2[6] = b;

  printmat(4, 4, matrix2); 

  multiplication(4, 4, 4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  // scale in x and y
  identity(4, matrix2);
  matrix2[0] = length[0] / ( (width[0] - width[1]) / 2);  // near / (right - left) / 2
  matrix2[5] = length[0] / ( (height[0] - height[1]) / 2);  // near / (top - bottom) / 2

  printmat(4, 4, matrix2);

  multiplication(4, 4, 4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  // scale in z
  identity(4, matrix2);
  matrix2[0] = 1 / length[1];
  matrix2[5] = 1 / length[1];
  matrix2[10] = 1 / length[1];

  printmat(4, 4, matrix2);

  multiplication(4, 4, 4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  printmat(4, 4, viewingMatrix);
}

void JLLoadIdentity() {
  identity(4, modelMatrix);
}

void JLTranslate(double x, double y, double z) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[3]  = x;
  tempMatrix[7]  = y;
  tempMatrix[11] = z;

  multiplication(4,4,4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);
}

void JLRotate(double angle, double xAxis, double yAxis, double zAxis) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  if(xAxis)
    rotate('x', angle, tempMatrix);
  if(yAxis)
    rotate('y', angle, tempMatrix);
  if(zAxis)
    rotate('z', angle, tempMatrix);

  multiplication(4, 4, 4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);
}

void JLScale(double xScale, double yScale, double zScale) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[0] = xScale;
  tempMatrix[1] = yScale;
  tempMatrix[2] = zScale;

  multiplication(4, 4, 4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);
}

void JLPushMatrix() {
  for(int i= 0; i < 4; i++)
    for (int j = 0; j< 4; j++)
      stack[stackCounter - 1][i*4+j] = modelMatrix[i*4+j];
  
  stackCounter++;
}

void JLPopMatrix() {
  stackCounter--;
}

void JLBegin(type m) {
  polygonType = m;
}

void JLEnd() {
  if(polygonType == triangle)

  if(polygonType == quad)
  

  polygonType = nothing;
}

void JLVertex(double x, double y, double z) {
  
  double coord[] = {x, y, z, 1};
  double final[4];
  double resultMatrix[16];
  multiplication(4, 4, 4, viewingMatrix, modelMatrix, resultMatrix);
  multiplication(4, 4, 1, resultMatrix, coord, final);

  printf("x: %f, y: %f, z: %f\n", final[0], final[1], final[2]);

  switch(polygonType) {
    case triangle:
      
      break;
    case quad:
    
      break;
    default: 
      break;
  }
}

void printMatrix() {
  printmat(4, 4, modelMatrix);
}
// Helper Method
void translate(double * matrix, double x, double y, double z) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[3]  = x;
  tempMatrix[7]  = y;
  tempMatrix[11] = z;

  multiplication(4, 4, 4, matrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, matrix, resultMatrix);
}

void normalize(double * vector, int count) {
  double denominator;

  for (int i = 0; i < count; i++) {
    denominator += (vector[i] * vector[i]);
  }

  denominator = sqrt(denominator);

  for(int i = 0; i < count; i++) {
    vector[i] = vector[i] / denominator;
  }
}