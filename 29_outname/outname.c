#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * fileExt = ".counts";
  char * outFileName = malloc((strlen(inputName) + strlen(fileExt) + 1) * sizeof(*outFileName));
  strcpy(outFileName, inputName);
  strcat(outFileName, fileExt);
  return outFileName;
}
