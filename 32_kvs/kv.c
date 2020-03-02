#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



/**
 * Open the file, read the lines of text
 * 
 * Split them into key/value pairs
 *
 * Add the resulting pairs to an array (hint: realloc it to make it larger each time)
 *
 * Close the file, and return the kvarray_t * that has your array
 * 
 */
kvarray_t * readKVs(const char * fname) {
  // open the file
  FILE * targetFile = fopen(fname, "r");
  if (targetFile == NULL) {
    perror("Target file not found");
    return NULL;
  }
  char * curline = NULL;
  kvarray_t * kvArray = malloc(sizeof(*kvArray));
  kvArray->length = 0;
  kvArray->array = NULL;
  size_t size;
  while (getline(&curline, &size, targetFile) >= 0) {
    char * key = NULL;
    int keyLen = 0;
    char * value = NULL;
    int valueLen = 0;
    int useKey = 1;  // assign characters to the key until we hit a =
    int skipIndex = -1;
    for(int i = 0; i < strlen(curline); i ++) {
      // quit on the null terminator or a new line
      if((curline[i] == '\0') || curline[i] == '\n') {
	break;
      }
      // start using the value at the first equals sign
      if(curline[i] == '=') {
	if(useKey == 1) {
	  // useKey should be true at the first instance of an equals sign
	  // so that is our check to set the index to skip
	  // we do not want to include the separator in the value!
	  skipIndex = i;
	}
	useKey = 0;
      }
      if(useKey == 1) {
	key = realloc(key, (keyLen + 1) * sizeof(*key));
	key[keyLen] = curline[keyLen];
	keyLen ++;
      } else {
	if (i != skipIndex) {
	  value = realloc(value, (valueLen + 1) * sizeof(*value));
	  value[valueLen] = curline[(skipIndex + 1) + valueLen];
	  valueLen ++;
	}
      }
    }
    // ensure both key and value are null terminated, valid strings
    key = realloc(key, (keyLen + 1) * sizeof(*key));
    key[keyLen] = '\0';
    value = realloc(value, (valueLen + 1) * sizeof(*value));
    value[valueLen] = '\0';
    kvpair_t keyValue;
    keyValue.key = key;
    keyValue.value = value;
    kvArray->array = realloc(kvArray->array, (kvArray->length + 1) * sizeof(*kvArray->array));
    kvArray->array[kvArray->length] = keyValue;
    kvArray->length = (kvArray->length + 1);
  }
  if(fclose(targetFile) == EOF) {
    perror("Unable to close file");
    return NULL;
  }
  // TODO: refactor to get key, value from curline in separate function
  return kvArray;
}


void freeKVs(kvarray_t * pairs) {
  // TODO: free all memory (each key and value in the array)
  for(int i = 0; i < pairs->length; i++) {
    free(pairs->array[i].key);
    free(pairs->array[i].value);
  }
}

void printKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->length; i ++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i].key, pairs->array[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for(int i = 0; i < pairs->length; i ++) {
    if(strcmp(pairs->array[i].key, key) == 0) {
      return pairs->array[i].value;
    }
  }
  return NULL;
}
