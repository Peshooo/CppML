#include <cmath>
#include "Sigmoid.h"

double Sigmoid::getActivation(double x) {
  return 1.0 / (1.0 + std::exp(-x));
}

double Sigmoid::getActivationDerivative(double x) {
  return x * (1.0 - x);
}
