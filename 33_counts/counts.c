#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  // allocate memory for a counts_t structure
  // initialize it to represent that nothing has been counted yet
  counts_t * c =  malloc(sizeof(*c));
  c->length = 0;
  c->countUnknown = 0;
  c->counts = NULL;
  return c;
}


void addCountsValidName(counts_t * c, const char * name) {
  for(int i = 0; i < c->length; i ++) {
    if(strcmp(c->counts[i].key, name) == 0) {
      c->counts[i].total ++;
      return;
    }
  }
  one_count_t newCount;
  newCount.total = 1;
  newCount.key = malloc(sizeof(name));
  strcpy(newCount.key, name);
  c->length ++;
  c->counts = realloc(c->counts, sizeof(*c->counts) * (c->length));
  c->counts[(c->length - 1)] = newCount;
}


void addCount(counts_t * c, const char * name) {
  // increment the count for the corresponding name
  // handle if the input name is NULL
  if (name == NULL) {
    c->countUnknown ++;
  } else {
    addCountsValidName(c, name);
  } 
  return;
}

/**
 * Print to the outFile in the format
 *
 * Captain: 1
 * ...
 * <unknown> : 1
 *
 */
void printCounts(counts_t * c, FILE * outFile) {
  for (int i = 0; i < c->length; i ++) {
    printf("%s: %d\n", c->counts[i].key, c->counts[i].total);
  }
  if (c->countUnknown > 0) {
    printf("<unknown> : %d\n", c->countUnknown);
  }
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->length; i ++) {
    free(c->counts[i].key);
  }
  free(c->counts);
  free(c);
}
