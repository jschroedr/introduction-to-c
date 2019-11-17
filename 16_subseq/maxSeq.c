#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n) {

  if(n == 0) { return 0; }
  if(n == 1) { return 1; }
  int maxLength = 1;
  int thisLength = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      thisLength += 1;
      if (thisLength > maxLength) {
	maxLength = thisLength;
      }
    } else {
      // reset current length counter
      thisLength = 1;
    }
  }
  return maxLength;
}
