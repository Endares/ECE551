#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f(fname);
  if (!f) {
    std::cerr << "Failed to open the file " << fname << std::endl;
    exit(EXIT_FAILURE);
  }

  // dynamic allocation, initialize to 0 by using Value Initialization.
  // default initialization: uint64_t* freqArray = new uint64_t[NUMCHARS], will lead to undefined values.
  uint64_t * freqArray = new uint64_t[NUMCHARS]();

  char c;
  while (f.get(c)) {  // read character by character
    freqArray[static_cast<unsigned char>(c)]++;
  }

  // eof
  if (f.eof()) {
    ++freqArray[256];
  }
  else if (f.fail()) {
    std::cout << "File reading failed (not EOF)." << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    std::cout << "Unknown error occurred." << std::endl;
    exit(EXIT_FAILURE);
  }
  f.close();
  return freqArray;
}
