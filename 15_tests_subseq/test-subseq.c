#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main()
{
  // test one-value array
  int array1[1] = {0};
  int result1 = maxSeq(array1, 1);
  if (result1 != 1)
    {
      return EXIT_FAILURE;
    }

  // test negative increasing array
  int array2[4] = {-3, -2, -1, 0};
  int result2 = maxSeq(array2, 4);
  if (result2 != 4) { return EXIT_FAILURE; }

  // test array of all equal values
  int array3[4] = {3, 3, 3, 3};
  int result3 = maxSeq(array3, 4);
  if (result3 != 1) { return EXIT_FAILURE; }

  // test overwriting the largest array length
  int array4[5] = {1, 2, 1, 2, 3};
  int result4 = maxSeq(array4, 5);
  if (result4 != 3) { return EXIT_FAILURE; }

  // test an empty array
  int array5[0] = {};
  int result5 = maxSeq(array5, 0);
  if (result5 != 0) { return EXIT_FAILURE; }


  return EXIT_SUCCESS;
}
