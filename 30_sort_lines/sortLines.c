#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}


void printSortResult(char ** data, size_t count) {
  for (int i = 0; i < (int)count; i ++) {
    printf("%s\n", data[i]);
  }
}


void freeLineArray(char ** data, size_t count) {
  for (int i = 0; i < (int)count; i ++) {
    free(data[i]);
  }
  free(data);
}


int main(int argc, char ** argv) {
  size_t len = 0;
  ssize_t nread;
  char * line = NULL;
  char ** lineArray = NULL;
  size_t lineCount;
  if (argc == 1) {
    lineCount = 1;
    while ((nread = getline(&line, &len, stdin)) != -1) {
      lineArray = realloc(lineArray, (lineCount * sizeof(lineArray)));
      lineArray[lineCount - 1] = malloc(((strlen(line) + 1) * sizeof(lineArray[lineCount - 1])));
      strcpy(lineArray[lineCount - 1], line);
      lineCount ++;
    }
    free(line);
    // sort the array of strings
    sortData(lineArray, (lineCount - 1));
    // print the array of strings
    printSortResult(lineArray, (lineCount - 1));
    // free the array of strings
    freeLineArray(lineArray, (lineCount - 1));
    return EXIT_SUCCESS;
  } else {  // argc > 1
    for (int i = 1; i < argc; i ++) {
      // treat each argument as an input file name
      // open the file
      FILE * targetFile = fopen(argv[i], "r");
      if (targetFile == NULL) {
	fprintf(stderr, "File not found");
	return EXIT_FAILURE;
      }
      lineCount = 1;
      // read all the lines of data in it
      while ((nread = getline(&line, &len, targetFile)) != -1) {
	lineArray = realloc(lineArray, (lineCount * sizeof(lineArray)));
	lineArray[lineCount - 1] = malloc((strlen(line) + 1) * sizeof(lineArray[lineCount - 1]));
	strcpy(lineArray[lineCount - 1], line);
	lineCount ++;
      }
      free(line);
      // sort the lines
      sortData(lineArray, (lineCount - 1));
      // print the results (TODO)
      printSortResult(lineArray, (lineCount - 1));
      // free the memory
      freeLineArray(lineArray, (lineCount - 1));
      // close the file
      if (fclose(targetFile) != 0) {
	perror("Unable to close input file");
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
