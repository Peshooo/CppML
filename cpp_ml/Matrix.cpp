#include "Matrix.h"

Matrix::Matrix(): rows(0), cols(0), a(nullptr) {}

Matrix::Matrix(int _rows, int _cols) {
  rows = _rows;
  cols = _cols;

  a = new double* [rows];
  for(int i=0;i<rows;i++) {
    a[i] = new double [cols] ();
  }
}

Matrix::Matrix(const Matrix &x) {
  rows = x.getRows();
  cols = x.getCols();

  a = new double* [rows];
  for(int i=0;i<rows;i++) {
    a[i] = new double [cols];

    for(int j=0;j<cols;j++) {
      a[i][j] = x[i][j];
    }
  }
}

Matrix::~Matrix() {
  for(int i=0;i<rows;i++) {
    delete [] a[i];
  }

  delete [] a;
}

int Matrix::getRows() const {
  return rows;
}

int Matrix::getCols() const {
  return cols;
}

double*& Matrix::operator [](const int &idx) const {
  return a[idx];
}

void Matrix::operator =(const Matrix &x) {
  for(int i=0;i<rows;i++) {
    delete [] a[i];
  }

  delete [] a;

  rows = x.getRows();
  cols = x.getCols();

  a = new double* [rows];
  for(int i=0;i<rows;i++) {
    a[i] = new double [cols];

    for(int j=0;j<cols;j++) {
      a[i][j] = x[i][j];
    }
  }
}

void Matrix::operator +=(const Matrix &x) const {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<cols;j++) {
      a[i][j] += x[i][j];
    }
  }
}

void Matrix::operator -=(const Matrix &x) const {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<cols;j++) {
      a[i][j] -= x[i][j];
    }
  }
}

Matrix operator +(Matrix a, Matrix b) {
  Matrix ans(a);
  
  ans += b;
  
  return ans;
}

Matrix operator -(Matrix a, Matrix b) {
  Matrix ans(a);

  ans -= b;

  return ans;
}

Matrix operator *(Matrix a, Matrix b) {
  Matrix ans(a.getRows(), b.getCols());

  for(int i=0;i<a.getRows();i++) {
    for(int j=0;j<b.getCols();j++) {
      for(int z=0;z<a.getCols();z++) {
        ans[i][j] += a[i][z] * b[z][j];
      }
    }
  }

  return ans;
}

void Matrix::zero() {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<cols;j++) {
      a[i][j] = 0.0;
    }
  }
}

void Matrix::randomize(RandomNumberGenerator* rng) {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<cols;j++) {
      a[i][j] = rng->rand_01();
      if(rng->next() % 2) a[i][j] = -a[i][j];
    }
  }
}

void Matrix::getActivation(ActivationFunction* activation) {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<cols;j++) {
      a[i][j] = activation->getActivation(a[i][j]);
    }
  }
}

void Matrix::getActivationDerivative(ActivationFunction* activation) {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<cols;j++) {
      a[i][j] = activation->getActivationDerivative(a[i][j]);
    }
  }
}

Matrix getActivation(Matrix a, ActivationFunction* activation) {
  a.getActivation(activation);
  return a;
}

Matrix getActivationDerivative(Matrix a, ActivationFunction* activation) {
  a.getActivationDerivative(activation);
  return a;
}

Matrix transpose(Matrix a) {
  Matrix ans(a.getCols(), a.getRows());
  
  for(int i=0;i<a.getRows();i++) {
    for(int j=0;j<a.getCols();j++) {
      ans[j][i] = a[i][j];
    }
  }

  return ans;
}

double dotProduct(Matrix a, Matrix b) {
  double ans = 0.0;

  for(int i=0;i<a.getRows();i++) {
    for(int j=0;j<a.getCols();j++) {
      ans += a[i][j] * b[i][j];
    }
  }

  return ans;
}

Matrix hadamardProduct(Matrix a, Matrix b) {
  Matrix ans(a.getRows(), a.getCols());

  for(int i=0;i<a.getRows();i++) {
    for(int j=0;j<a.getCols();j++) {
      ans[i][j] = a[i][j] * b[i][j];
    }
  }

  return ans;
}
