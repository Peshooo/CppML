#ifndef SIGMOID_H
#define SIGMOID_H

#include "ActivationFunction.h"

class Sigmoid : public ActivationFunction {
  public:
    double getActivation(double);
    double getActivationDerivative(double);
};

#endif
