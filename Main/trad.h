#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXFUNCSIZE 256
#define MAXWORDLEN 32
#define MAXWORDS 8
#define MAXLVARS 5
#define MAXPARAMS 3

typedef struct L {
	int n;
	char word[MAXWORDS][MAXWORDLEN];
	int nWords;
}Line;

typedef struct V {
	char id;
	char type;
	int size;
}Var;

typedef struct F {
	char id;
	Var p[MAXPARAMS];
	Var localVars[MAXLVARS];
	Line body[MAXFUNCSIZE];
	Var ret;
	int stackMem;
}Function;

Line readLine();

Function newFunction(Line l);

void initAssembly();

void writeFn(Function fn);