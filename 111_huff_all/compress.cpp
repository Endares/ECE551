#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream f(inFile);
  if (!f) {
    std::cerr << "fail to open file " << inFile << std::endl;
    exit(EXIT_FAILURE);
  }
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  char c;
  while (f.get(c)) {  // read character by character
    // const_iterator for const & theMap
    std::map<unsigned, BitString>::const_iterator it =
        theMap.find((unsigned char)c);  // must have type convert, or will not find
    if (it == theMap.end()) {
      std::cerr << "Character " << c << " not visited" << std::endl;
      exit(EXIT_FAILURE);
    }
    //    std::cout << "yes\n" << std::endl;
    bfw.writeBitString(it->second);
  }

  //dont forget to lookup 256 for the EOF marker, and write it out.
  std::map<unsigned, BitString>::const_iterator it = theMap.find(256);
  if (it == theMap.end()) {
    std::cerr << "Character not visited" << std::endl;
    exit(EXIT_FAILURE);
  }
  bfw.writeBitString(it->second);
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  f.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * freqArray = readFrequencies(argv[1]);
  Node * root = buildTree(freqArray);

  std::map<unsigned, BitString> theMap;
  // BitString for root is empty
  root->buildMap(BitString(), theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete[] freqArray;
  // need to deallocate root by hand, because root was created by new in buildTree.cpp
  delete root;
  // destructor of root will recursively destroy the whole tree
  return EXIT_SUCCESS;
}
