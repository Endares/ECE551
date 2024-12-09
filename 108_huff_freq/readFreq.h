#ifndef __READ_FREQ_H__
#define __READ_FREQ_H__
#include <assert.h>
#include <stdint.h>

#include <iostream>

// ASCII: 256 characters, and an extra one for eof
#define NUMCHARS 257

uint64_t * readFrequencies(const char * fname);
void printSym(std::ostream & s, unsigned sym);
#endif
