#include "RandomNumberGenerator.h"

double RandomNumberGenerator::rand_01() {
  return (next() % 1000000001) / 1000000000.0;
}
