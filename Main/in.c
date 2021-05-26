#include "trad.h"

int position = 1;

Line readLine() {
	int i = 0;
	Line l;

	l.nWords = 0;
	l.n = position;

	while (scanf("%s", l.word[i]) != EOF) {
		l.nWords++;
		i++;
		if (getc(stdin) == '\n')break;
	}

	position++;
	
	return l;
}


Function newFunction(Line l) {

	Function fn;
	int i, j, iTmp, *aTmp;

	fn.stackMem = 32;

	// lendo header e parametros
	fn.id = l.word[1][1];
	printf("	fn id: %c\n", fn.id);

	for (i = 2, j = 0; i < l.nWords; ++i, ++j) {
		fn.p[j].id = l.word[i][2];
		printf("	p[%d] id: %c", (i-1), fn.p[j].id);

		fn.p[j].type = l.word[i][1];

		printf(" type: %c\n", fn.p[j].type);
	}

	// lendo variáveis locais
	readLine();
	for (l = readLine(), i = 0; strcmp(l.word[0], "enddef") != 0; l = readLine(), i++){

		fn.localVars[i].id = l.word[1][2];
		printf("	v[%d] id: %c ", (i+1), fn.localVars[i].id);

		fn.localVars[i].type = l.word[1][1];
		printf(" type: %c", fn.localVars[i].type);

		if (fn.localVars[i].type == 'a') {
			fn.localVars[i].size = 4 * atoi(&l.word[3][2]);
			printf(" size: %d", fn.localVars[i].size);
		} else {
			fn.localVars[i].size = 4;
			printf(" size: %d", fn.localVars[i].size);
		}

		fn.stackMem += fn.localVars[i].size;

		printf("\n");
	}
	

	// lendo Corpo da função
	printf("	Corpo: de f%c\n", fn.id);
	for (l = readLine(), i = 0; strcmp(l.word[0], "end") != 0; l = readLine(), i++){

		fn.body[i] = l;

		printf("	%d ", fn.body[i].n);
		for (j = 0; j < fn.body[i].nWords; ++j) {
			printf("%s ", fn.body[i].word[j]);
		}
		printf("(%d)words", fn.body[i].nWords);
		printf("\n");
	}
	if (fn.stackMem % 16)
		fn.stackMem = (fn.stackMem - (fn.stackMem % 16)) + 16;
	
	printf("stackMem : %d\n", fn.stackMem);

	return fn;
}

void readCmd(Line l){

}