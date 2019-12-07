#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "ActivationFunction.h"
#include "RandomNumberGenerator.h"
#include "Matrix.h"
#include <bits/stdc++.h>

using namespace std;

class NeuralNetwork {
  RandomNumberGenerator* rng;
  ActivationFunction* activation;
  int layersCount;
  vector<int> topology;
  vector<Matrix> weight, bias, deltaWeight, deltaBias;
  double learningRate;

  void backPropagation(Matrix, Matrix);

  public:
    NeuralNetwork();
    NeuralNetwork(vector<int>, double, RandomNumberGenerator*, ActivationFunction*);

    Matrix feedForward(Matrix);
    void train(vector<Matrix>, vector<Matrix>);
};

#endif
