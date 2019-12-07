#include <bits/stdc++.h>
#include "../../cpp_ml/cpp_ml.h"

using namespace std;

const int BATCH_SIZE = 20;

ActivationFunction* activation = new Sigmoid();
RandomNumberGenerator* rng = new Xorshift();
NeuralNetwork net({784, 20, 10}, 1.0, rng, activation);
vector<Matrix> trainInput, trainOutput;

vector<int> split(string s) {
  int curr = 0;
  vector<int> ans;

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
  cerr<<"Time: "<<(int)(clock() * 1000.0 / CLOCKS_PER_SEC)<<" ms."<<endl;
}

void parseTrainingData() {
  ifstream IN("train.csv");
  Matrix input(1, 784), output(1, 10);
  string trash;

  trainInput.reserve(42000);
  trainOutput.reserve(42000);

  IN>>trash;
  for(int i=0;i<42000;i++) {
    IN>>trash;

    vector<int> v = split(trash);

    output.zero();
    output[0][v[0]] = 1.0;

    for(int j=1;j<785;j++) {
      input[0][j - 1] = v[j] / 255.0;
    }

    trainInput.push_back(input);
    trainOutput.push_back(output);
  }

  cerr<<"Training data loaded!"<<endl;
  timeStamp();
}

void randomShuffle(vector<int> &v, RandomNumberGenerator* rng) {
  for(int i=(int)(v.size()) - 1;i>=0;i--) {
    swap(v[i], v[rng->next() % (i + 1)]);
  }
}

void train() {
  vector<int> idx;
  vector<Matrix> inputs;
  vector<Matrix> outputs;
  Matrix currOutput;

  for(int i=0;i<42000;i++) {
    idx.push_back(i);
  }

  for(int epoch=1;epoch<=1;epoch++) {
    cerr<<"Epoch "<<epoch<<" starting."<<endl;

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

    cerr<<"Epoch "<<epoch<<" finished."<<endl;
    cerr<<"Error: "<<error<<endl;
    timeStamp();

    cerr<<endl;
  }
}

void test() {
  ifstream IN("test.csv");
  ofstream OUT("ans.csv");
  string trash;
  Matrix input(1, 784), output;

  OUT<<"ImageId,Label"<<endl;

  IN>>trash;
  for(int i=0;i<28000;i++) {
    IN>>trash;
    vector<int> v = split(trash);

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

    OUT<<i + 1<<","<<which<<endl;
  }

  OUT.close();
}

int main() {
  parseTrainingData();
  train();
  test();
}
