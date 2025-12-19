#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "readFreq.h"
#include "node.h"
#include <fstream>


void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){
  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading

  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.

	std::ifstream fin(inFile);
	if (!fin) {
		fprintf(stderr, "Cannot open input file\n");
		exit(EXIT_FAILURE);
	}

	int c;
	while ((c = fin.get()) != EOF) {
		std::map<unsigned, BitString>::const_iterator it = theMap.find((unsigned char)c);
		if (it == theMap.end()) {
			fprintf(stderr, "Character not in map\n");
			exit(EXIT_FAILURE);
		}
		bfw.writeBitString(it->second);
	}
	std::map<unsigned, BitString>::const_iterator it = theMap.find(256);
	if (it == theMap.end()) {
		fprintf(stderr, "EOF symbol missing\n");
		exit(EXIT_FAILURE);
	}
	bfw.writeBitString(it->second);
	fin.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done. 
  //hint 2: you can look at the main from the previous tester for 90% of this
	uint64_t * counts = readFrequencies(argv[1]);
	Node * root = buildTree(counts);

	std::map<unsigned, BitString> theMap;
	BitString empty;
	if (root != NULL) {
		root->buildMap(empty, theMap);
	}

	writeCompressedOutput(argv[1], argv[2], theMap);
	delete root;
	delete[] counts;

	return EXIT_SUCCESS;
}
