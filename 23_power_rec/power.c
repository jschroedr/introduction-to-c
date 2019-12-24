#include <stdio.h>
#include <stdlib.h>

unsigned powerHelper(unsigned x, unsigned y);
unsigned power(unsigned x, unsigned y) {
  // while 0 to 0 is undefined in math, we will return 1
  if ((x == 0) && (y == 0)) {
    return 1;
  } else if (y == 1) {
    return x;
  }
  return x * powerHelper(x, (y - 1));
}

unsigned powerHelper(unsigned x, unsigned y) {
  if (y == 1) {
    return x;
  }
  return x * power(x, (y - 1));
}
