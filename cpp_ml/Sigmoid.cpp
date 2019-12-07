#include <bits/stdc++.h>
#include "Sigmoid.h"

using namespace std;

double Sigmoid::getActivation(double x) {
  return 1.0 / (1.0 + exp(-x));
}

double Sigmoid::getActivationDerivative(double x) {
  return x * (1.0 - x);
}
