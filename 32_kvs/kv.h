#ifndef __KV_H__
#define __KV_H__


/**
 * Key-Value pair struct definition
 */
struct _kvpair_t { 
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;

/**
 * An array of key-value pairs
 */
struct _kvarray_t { 
  size_t length;
  kvpair_t * array;  // TODO(jschroeder): This may not work
};
typedef struct _kvarray_t kvarray_t;


kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
