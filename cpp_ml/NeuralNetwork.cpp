#include "NeuralNetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork(): NeuralNetwork({1, 1, 1}, 1.0, new Xorshift(), new Sigmoid()) {}

NeuralNetwork::NeuralNetwork(std::vector<int> _topology, double _learningRate, RandomNumberGenerator* _rng, ActivationFunction* _activation) {
  topology = _topology;
  layersCount = topology.size();
  learningRate = _learningRate;
  rng = _rng;
  activation = _activation;

  weight.resize(layersCount - 1);
  bias.resize(layersCount - 1);
  deltaWeight.resize(layersCount - 1);
  deltaBias.resize(layersCount - 1);

  for(int i=0;i<layersCount - 1;i++) {
    weight[i] = Matrix(topology[i], topology[i + 1]);
    bias[i] = Matrix(1, topology[i + 1]);
    deltaWeight[i] = Matrix(topology[i], topology[i + 1]);
    deltaBias[i] = Matrix(1, topology[i + 1]);

    weight[i].randomize(rng);
    bias[i].randomize(rng);
  }
}

Matrix NeuralNetwork::feedForward(Matrix input) {
  for(int i=0;i<layersCount - 1;i++) {
    input = input * weight[i] + bias[i];
    input.getActivation(activation);
  }

  return input;
}

void NeuralNetwork::backPropagation(Matrix input, Matrix output) {
  std::vector<Matrix> layers;
  Matrix delta;
  
  layers.push_back(input);
  for(int i=0;i<layersCount - 1;i++) {
    input = (input * weight[i]) + bias[i];
    input.getActivation(activation);

    layers.push_back(input);
  }

  delta = hadamardProduct(input - output, getActivationDerivative(layers[layersCount - 1], activation));

  deltaBias[layersCount - 2] += delta;
  deltaWeight[layersCount - 2] += transpose(layers[layersCount - 2]) * delta;

  for(int i=layersCount - 3;i>=0;i--) {
    delta = hadamardProduct(delta * transpose(weight[i + 1]), getActivationDerivative(layers[i + 1], activation));

    deltaBias[i] += delta;
    deltaWeight[i] += transpose(layers[i]) * delta;
  }
}

void NeuralNetwork::train(std::vector<Matrix> inputs, std::vector<Matrix> outputs) {
  for(int i=0;i<layersCount - 1;i++) {
    deltaWeight[i].zero();
    deltaBias[i].zero();
  }

  for(int i=0;i<(int)(inputs.size());i++) {
    backPropagation(inputs[i], outputs[i]);
  }

  for(int i=0;i<layersCount - 1;i++) {
    for(int j=0;j<deltaWeight[i].getRows();j++) {
      for(int z=0;z<deltaWeight[i].getCols();z++) {
        deltaWeight[i][j][z] /= (double)(inputs.size());
        weight[i][j][z] -= learningRate * deltaWeight[i][j][z];
      }
    }

    for(int j=0;j<deltaBias[i].getRows();j++) {
      for(int z=0;z<deltaBias[i].getCols();z++) {
        deltaBias[i][j][z] /= (double)(inputs.size());
        bias[i][j][z] -= learningRate * deltaBias[i][j][z];
      }
    }
  }
}
