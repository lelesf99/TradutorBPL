#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRSIZE 32768
#define MAXFUNCSIZE 256
#define MAXWORDLEN 32
#define MAXWORDS 8
#define MAXLVARS 5
#define MAXPARAMS 3

typedef struct LINE {
	int n;
	char word[MAXWORDS][MAXWORDLEN];
	int nWords;
	struct FUNCTION *scope;
}Line;

typedef struct VAR {
	char id[MAXWORDLEN];
	char type;
	int size;
	char cReg[MAXWORDLEN];
	int val;
}Var;

typedef struct FUNCTION {
	char id[MAXWORDLEN];
	Var p[MAXPARAMS];
	Var localVars[MAXLVARS];
	Line body[MAXFUNCSIZE];
	int nLV;
	int nP;
	int size;
	int stackMem;
}Function;
// *******************************************
// in.c
Line readLine();

void setPar(char word[MAXWORDLEN], Var * par);

void setLVar(Line l, Var * var);

void newFunction(Line l, Function * fn);

// ********************************************
// out.c
void initAssembly();

void wFn(Function * fn);

void wCmd(FILE * fp, Line l);

char * id2Reg(Function * scope, char word[MAXWORDLEN]);