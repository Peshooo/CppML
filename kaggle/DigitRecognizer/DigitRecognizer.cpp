#include <iostream>
#include <fstream>
#include <vector>

#include "../../cpp_ml/cpp_ml.h"

const int BATCH_SIZE = 20;

ActivationFunction* activation = new Sigmoid();
RandomNumberGenerator* rng = new Xorshift();
NeuralNetwork net({784, 20, 10}, 1.0, rng, activation);
std::vector<Matrix> trainInput, trainOutput;

std::vector<int> split(std::string s) {
  int curr = 0;
  std::vector<int> ans;

  for(int i=0;i<(int)(s.size());i++) {
    if(s[i]==',') {
      ans.push_back(curr);
      curr = 0;
    } else {
      curr *= 10;
      curr += s[i] - '0';
    }
  }

  ans.push_back(curr);

  return ans;
}

void timeStamp() {
  std::cerr<<"Time: "<<(int)(std::clock() * 1000.0 / CLOCKS_PER_SEC)<<" ms."<<std::endl;
}

void parseTrainingData() {
  std::ifstream IN("train.csv");
  Matrix input(1, 784), output(1, 10);
  std::string trash;

  trainInput.reserve(42000);
  trainOutput.reserve(42000);

  IN>>trash;
  for(int i=0;i<42000;i++) {
    IN>>trash;

    std::vector<int> v = split(trash);

    output.zero();
    output[0][v[0]] = 1.0;

    for(int j=1;j<785;j++) {
      input[0][j - 1] = v[j] / 255.0;
    }

    trainInput.push_back(input);
    trainOutput.push_back(output);
  }

  log("Training data parsed!");

  timeStamp();
}

void randomShuffle(std::vector<int> &v, RandomNumberGenerator* rng) {
  for(int i=(int)(v.size()) - 1;i>=0;i--) {
    std::swap(v[i], v[rng->next() % (i + 1)]);
  }
}

void train() {
  std::vector<int> idx;
  std::vector<Matrix> inputs;
  std::vector<Matrix> outputs;
  Matrix currOutput;

  for(int i=0;i<42000;i++) {
    idx.push_back(i);
  }

  for(int epoch=1;epoch<=1;epoch++) {
    std::cerr<<"Epoch "<<epoch<<" starting."<<std::endl;

    double error = 0.0;

    randomShuffle(idx, rng);

    for(int i=0;i<42000;i+=BATCH_SIZE) {
      inputs.clear();
      outputs.clear();

      for(int j=0;j<BATCH_SIZE;j++) {
        inputs.push_back(trainInput[idx[i + j]]);
        outputs.push_back(trainOutput[idx[i + j]]);
      }

      net.train(inputs, outputs);
    }

    for(int i=0;i<42000;i++) {
      currOutput = net.feedForward(trainInput[i]);

      for(int j=0;j<10;j++) {
        error += (currOutput[0][j] - trainOutput[i][0][j]) * (currOutput[0][j] - trainOutput[i][0][j]);
      }
    }

    error /= 10.0;
    error /= 42000.0;

    std::cerr<<"Epoch "<<epoch<<" finished."<<std::endl;
    std::cerr<<"Error: "<<error<<std::endl;
    timeStamp();

    std::cerr<<std::endl;
  }
}

void test() {
  std::ifstream IN("test.csv");
  std::ofstream OUT("ans.csv");
  std::string trash;
  Matrix input(1, 784), output;

  OUT<<"ImageId,Label"<<std::endl;

  IN>>trash;
  for(int i=0;i<28000;i++) {
    IN>>trash;
    std::vector<int> v = split(trash);

    for(int j=0;j<784;j++) {
      input[0][j] = v[j] / 255.0;
    }

    output = net.feedForward(input);

    double maxValue = -1;
    int which = 0;
    for(int j=0;j<10;j++) {
      if(output[0][j]>maxValue) {
        maxValue = output[0][j];
        which = j;
      }
    }

    OUT<<i + 1<<","<<which<<std::endl;
  }

  OUT.close();
}

int main() {
  parseTrainingData();
  train();
  test();
}
