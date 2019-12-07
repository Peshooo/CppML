#ifndef MATRIX_H
#define MATRIX_H

#include "Sigmoid.h"
#include "Xorshift.h"

class Matrix {
  int rows, cols;
  double **a;

  public:
    //Constructors/Destructors 
    Matrix();
    Matrix(int, int);
    Matrix(const Matrix&);
    ~Matrix();

    //Getters/Setters
    int getRows() const;
    int getCols() const;

    //Operators
    double* &operator [](const int&) const;

    void operator =(const Matrix&);

    void operator -=(const Matrix&) const;
    void operator +=(const Matrix&) const;
    
    //Utils
    void zero();
    void randomize(RandomNumberGenerator*);
    void getActivation(ActivationFunction*);
    void getActivationDerivative(ActivationFunction*);
};

Matrix operator +(Matrix a, Matrix b);
Matrix operator -(Matrix a, Matrix b);
Matrix operator *(Matrix a, Matrix b);

Matrix transpose(Matrix a);
double dotProduct(Matrix a, Matrix b);
Matrix hadamardProduct(Matrix a, Matrix b);

Matrix getActivation(Matrix, ActivationFunction*);
Matrix getActivationDerivative(Matrix, ActivationFunction*);

#endif
