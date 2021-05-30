#include "trad.h"

int main() {

	int i, j;
	char l[256];
	Line line;
	Function tmpFn[10];

	// Leitura/salvamento
	for (line = readLine(), i = 0; line.nWords != 0; line = readLine()){
		if (strcmp(line.word[0], "function") == 0 || strcmp(line.word[0], "call") == 0) {
			newFunction(line, &tmpFn[i]);
			i++;
		}
	}
	// Tradução/escrita em arquivo
	initAssembly();
	j = i;
	for (i = 0; i < j; ++i) {
		wFn(&tmpFn[i]);
	}
	// Tradução/escrita no stdout
	FILE * trad;
	trad = fopen("IO/trad.S", "r");
	while(fscanf(trad, "%s", l) != EOF) {
		printf("%s ", l);
		if (getc(trad) == '\n')printf("\n");
	}
	return 0;
}