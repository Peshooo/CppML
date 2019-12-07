#include "Xorshift.h"

Xorshift::Xorshift() {
  x = 123456789;
  y = 38012123;
  z = 7777777;
  w = 8392032;
}

unsigned Xorshift::next() {
  unsigned t = x ^ (x<<11);

  x = y; y = z; z = w;

  return w = w ^ (w>>19) ^ t ^ (t>>8);
}
