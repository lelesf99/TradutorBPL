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

	// Escopo global
	l.scope = NULL;
	
	position++;
	
	return l;
}


void setPar(char word[MAXWORDLEN], Var * par) {

	char rReg[3][5] = {"%rdi\0", "%rsi\0", "%rdx\0"};
	char eReg[3][5] = {"%edi\0", "%esi\0", "%edx\0"};

	strcpy(par->id, word);

	// lendo tipo dos parametros
	par->type = word[1];

	if (par->type == 'i')
		strcpy(par->cReg, eReg[par->id[2] - '0' - 1]);
	else{
		strcpy(par->cReg, rReg[par->id[2] - '0' - 1]);
	}
}

void setLVar(Line l, Var * var) {

	// lendo id da var
	strcpy(var->id, l.word[1]);
	
	// lendo tipo da var
	var->type = l.word[1][1];
	
	// lendo o tamanho da var
	// Se o tipo é array multiplica o tamanho do array por 4
	// Se o tipo é int o tamanho é 4 
	if (var->type == 'a')
		var->size = 4 * atoi(&l.word[3][2]);
	else {
		var->size = 4;
	}	
}

void newFunction(Line l, Function * fn) {

	int i, j;

	// Toda fila começa com 32 bytes para salvar os registradores caller saved
	fn->stackMem = 32;
	fn->nLV = 0;
	fn->nP = 0;
	fn->size = 0;

	// lendo header e parametros
	// lendo id da função
	strcpy(fn->id, l.word[1]);

	for (i = 2, j = 0; i < l.nWords; ++i, ++j) {
		setPar(l.word[i], &fn->p[j]);
		fn->nP++;
	}

	// lendo variáveis locais
	readLine();
	for (l = readLine(), i = 0, j = -32; strcmp(l.word[0], "enddef") != 0; l = readLine(), i++){
		
		setLVar(l, &fn->localVars[i]);
		fn->nLV++;

		// Settando a posição de memória da var[i]
		j-=fn->localVars[i].size;
		sprintf(fn->localVars[i].cReg, "%d(%%rbp)", j);

		// somando o tamanho das variáveis locais no tamanho da Fila
		fn->stackMem += fn->localVars[i].size;
	}
	

	// lendo Corpo da função
	// Guardamos o corpo da função como um vetor de Lines 
	//para facilitar a integração com o restante do programa.

	for (l = readLine(), i = 0; strcmp(l.word[0], "end") != 0; l = readLine(), i++){
		fn->body[i] = l;
		// Escopo da função
		fn->body[i].scope = fn;
		fn->size++;
	}

	// Tornando a fila alinhada à 16 caso já não esteja
	if (fn->stackMem % 16)
		fn->stackMem = (fn->stackMem - (fn->stackMem % 16)) + 16;
}