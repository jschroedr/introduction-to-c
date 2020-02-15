#include <stdio.h>
#include <stdlib.h>
int cmplong(const void * vp1, const void * vp2) {
  const long * p1 = vp1;
  const long * p2 = vp2;
  return *p1 - *p2;
}
int main(void) {
  char * line= NULL;
  size_t sz =0;
  long * array = NULL;
  size_t n = 0;
  int result;
  while((result = getline(&line, &sz, stdin)) > 1){
    n++;
    array=realloc(array, n * sizeof(*array));
    array[n-1] = strtol(line, NULL, 0);
    printf("%d\n", result);
  }
  printf("After while loop\n");
  // free(line);
  printf("After free(line)\n");
  // one additional error here: n should be n-1
  qsort(&array, n-1, sizeof(*array), cmplong);
  for (size_t i = 0; i < n; i++) {
    printf("%ld\n", array[i]);
    free(&array[i]);
  }
  return EXIT_SUCCESS;
}
