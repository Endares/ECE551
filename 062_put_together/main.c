#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

/*
Parameters:
** filename: an input file containing lines of names (keys)
** kvPairs: a result of previous work, the mapping from keys to values;
Return Value:
** the counting result of the values of input keys.
countFile function:
** read the keys in <filename>, mapping each key to a value using <kvPairs>, counting how many times each value occurs in <countFile>. 
*/
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  // read the keys in file one by one, calculate counts_t
  char * currKey = NULL;
  size_t linecap = 0;
  while (getline(&currKey, &linecap, f) >= 0) {
    char * findNewlineSymbol = strchr(currKey, '\n');
    *findNewlineSymbol = '\0';
    char * currValue = lookupValue(kvPairs, currKey);
    addCount(c, currValue);
  }
  free(currKey);
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return c;
}

/*
Parameters:
** argv[1]:
** The first type of input file (which your program will read one of)
** will have the format:
** key1=value1
** key2=value2
** ....
** keyN=valueN

** argv[2~n]:
** The second type of input file will contain a list of lines (which 
** will typically match the keys from the first input file). 
** Your program will read one or more of this type of file.
*/
int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(
        stderr,
        "Wrong number of arguments!\n Usage: %s <filename1> <filename2> <filename3> ...",
        argv[0]);
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvArrays = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; ++i) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * currCount = countFile(argv[i], kvArrays);
    //compute the output file name from argv[i] (call this outName)
    char * outputFileName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(currCount, outputFile);
    //close f
    if (fclose(outputFile) != 0) {
      fprintf(stderr, "Error closing file: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    freeCounts(currCount);
  }
  //free the memory for kv
  freeKVs(kvArrays);
  return EXIT_SUCCESS;
}
