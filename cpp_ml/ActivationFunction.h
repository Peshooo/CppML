#ifndef ACTIVATION_FUNCTION_H
#define ACTIVATION_FUNCTION_H

class ActivationFunction {
  public:
    virtual double getActivation(double) = 0;
    virtual double getActivationDerivative(double) = 0;
};

#endif
