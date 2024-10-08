#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) +
                 1;  // one space for '\0' because strlen() doesn't count for '\0'
  char * outputName = malloc(len * sizeof(*outputName));  // malloc space of 8 chars
  //fill in a string with the outputName
  snprintf(outputName, len, "%s%s", inputName, suffix);
  return outputName;
}
