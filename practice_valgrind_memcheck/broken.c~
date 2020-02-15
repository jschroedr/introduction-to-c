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
  while(getline(&line, &sz, stdin) > 0){
    n++;
    array=realloc(array, n * sizeof(*array));
    array[n] = strtol(line, NULL, 0);
  }
  free(line);
  qsort(&array, n, sizeof(*array), cmplong);
  for (size_t i = 0; i < n; i++) {
    printf("%ld\n", array[i]);
    free(&array[i]);
  }
  return EXIT_SUCCESS;
}
