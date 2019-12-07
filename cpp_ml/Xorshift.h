#ifndef XORSHIFT_H
#define XORSHIFT_H

#include "RandomNumberGenerator.h"

class Xorshift: public RandomNumberGenerator {
  unsigned x, y, z, w;

  public:
    Xorshift();
    unsigned next();
};

#endif
