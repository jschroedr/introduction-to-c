#include <stdlib.h>
#include <stdio.h>

// prototype for power - takes x to the y power
unsigned power(unsigned x, unsigned y);

void runCheck(unsigned x, unsigned y, unsigned expectedAns) {
  unsigned result = power(x, y);
  if (result != expectedAns) {
    printf("%d %d != %d. Returned %d", x, y, expectedAns, result);
    exit(EXIT_FAILURE);
  }
}

int main() {
  // the one that is likely to be the most tricky arises due to the
  // programmer using a variable of an incorrect type somewhere... (hint)
  
  // broken implementation 10
  runCheck(2, 2, 4);
  
  // broken implementation 11
  runCheck(9, 9, 387420489);

  // broken implementation 2
  runCheck('a', 1, 97);

  // broken implementation 3
  runCheck(0, 0, 1);
  
  exit(EXIT_SUCCESS);
}
