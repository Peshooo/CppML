#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>

#include "Sigmoid.h"
#include "Xorshift.h"
#include "Matrix.h"

class NeuralNetwork {
  RandomNumberGenerator* rng;
  ActivationFunction* activation;
  int layersCount;
  std::vector<int> topology;
  std::vector<Matrix> weight, bias, deltaWeight, deltaBias;
  double learningRate;

  void backPropagation(Matrix, Matrix);

  public:
    NeuralNetwork();
    NeuralNetwork(std::vector<int>, double, RandomNumberGenerator*, ActivationFunction*);

    Matrix feedForward(Matrix);
    void train(std::vector<Matrix>, std::vector<Matrix>);
};

#endif
