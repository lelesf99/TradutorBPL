#include "trad.h"

int main() {

	int i = 0, j;
	Line line;
	Function tmpFn;

	initAssembly();

	for (line = readLine(); line.nWords != 0; line = readLine()){
		if (strcmp(line.word[0], "function") == 0 || strcmp(line.word[0], "call") == 0) {
			printf("\nfunção %s na linha %d\n", line.word[1], line.n);
			tmpFn = newFunction(line);
			writeFn(tmpFn);
		}
	}
	
	return 0;
}