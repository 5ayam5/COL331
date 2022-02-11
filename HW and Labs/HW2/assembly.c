#include "stdint.h"

int32_t global;

int32_t foo(int32_t a, int32_t *b) {
  int32_t c;

  c = global + a;

  return *(b + c);
}
