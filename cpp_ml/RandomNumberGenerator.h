#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

class RandomNumberGenerator {
  public:
    virtual unsigned next() = 0;
    double rand_01();
};

#endif
