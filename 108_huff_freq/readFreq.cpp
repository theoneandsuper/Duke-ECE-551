#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
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
	uint64_t * freq = new uint64_t[257]();
	//open
	FILE * f = fopen(fname, "r");
	if (f == NULL) {
		perror("Could not open!\n");
		exit(EXIT_FAILURE);
	}

	int c = fgetc(f);
	while (c != EOF) {
		assert(c >= 0 && c < 256);
		freq[c]++;
		c = fgetc(f);
	}

	freq[256] = 1;

	//close file
	fclose(f);
	return freq;
}
