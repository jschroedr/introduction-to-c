#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"


char * sanitizeNewLine(char * line) {
  int len = strlen(line);
  for (int i = 0; i < len; i ++) {
    if(line[i] == '\n') {
      line[i] = '\0';
    }
  }
  return line;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  // create counts
  counts_t * counts = createCounts();
  // read each line in filename
  FILE * targetFile = fopen(filename, "r");
  if (targetFile == NULL) {
    perror("Cannot open targetFile in countFile");
    return NULL;  // add error handling to caller
  }
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while((len = getline(&line, &sz, targetFile)) >= 0) {
    // if not EOF
    // sanitize line
    line = sanitizeNewLine(line);
    // read the whole string (line)
    // and lookup the value in kvPairs
    char * result = lookupValue(kvPairs, line);
    // if not null add count for key
    // and if null add count for unknown
    addCount(counts, result);
  }
  fclose(targetFile);
  free(line);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc < 2) {
    perror("Expecting at least three arguments");
    EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for(int i = 2; i < argc; i ++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      perror("countFile returned NULL");
      EXIT_FAILURE;
    }
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]); 
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if(fclose(f) == EOF) {
      perror("Unable to close file");
      EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
