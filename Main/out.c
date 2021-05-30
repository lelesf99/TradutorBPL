#include "trad.h"

void initAssembly() {
	FILE * fp;
	fp = fopen("IO/trad.S", "w+");

	fprintf(fp, "# TRADUÇÂO:\n");
	fprintf(fp, ".section .rodata\n");
	fprintf(fp, ".data\n");
	fprintf(fp, ".text\n");

	fclose(fp);
}

char * id2Reg(Function * scope, char word[MAXWORDLEN]) {
	
	if (word[0] == 'p') {
		for (int i = 0; i < 3; ++i) {
			if (strcmp(scope->p[i].id, word) == 0) {
				return scope->p[i].cReg;	
			}
		}
	} else {
		for (int i = 0; i < 5; ++i) {
			if (strcmp(scope->localVars[i].id, word) == 0) {
				return scope->localVars[i].cReg;
			}
		}
	}
}

void wCmd(FILE * fp, Line l) {
	int i, j;
	char rReg[3][5] = {"%rdi\0", "%rsi\0", "%rdx\0"};
	char eReg[3][5] = {"%edi\0", "%esi\0", "%edx\0"};

	fprintf(fp,"#	%d ", l.n);
	for (i = 0; i < l.nWords; ++i) {
		fprintf(fp,"%s ", l.word[i]);
	}
	fprintf(fp,"\n");

	if (l.word[1][0] == '=') {
		if (l.nWords == 3) {
			// Atribuição simples
			if (l.word[2][0] == 'c') {
				fprintf(fp, "	movl $%d, %s\n", atoi(&l.word[2][2]), id2Reg(l.scope, l.word[0]));
			} else {
				fprintf(fp, "	movl %s, %%r8d\n", id2Reg(l.scope, l.word[2]));
				fprintf(fp, "	movl %%r8d, %s\n", id2Reg(l.scope, l.word[0]));
			}
		} else if(strcmp(l.word[2], "call") == 0) {
			// Atribuição retorno de Fn
			for (i = 4, j = 0; i < l.nWords; ++i) {
				if (l.word[i][0] == 'v') {
					// passar variável
					if (l.word[i][1] == 'i') {
						fprintf(fp, "	movl %s, %s\n", id2Reg(l.scope, l.word[i]), eReg[j]);
						j++;
					} else {
						fprintf(fp, "	leaq %s, %s\n", id2Reg(l.scope, l.word[i]), rReg[j]);
						j++;
					}
				} else if(l.word[i][0] == 'p'){
					// passar parametro
					if (l.word[i][1] == 'i') {
						fprintf(fp, "	movl %s, %s\n", id2Reg(l.scope, l.word[i]), eReg[j]);
						j++;
					} else {
						fprintf(fp, "	movq %s, %s\n", id2Reg(l.scope, l.word[i]), rReg[j]);
						j++;
					}
				} else {
					// passar const
					fprintf(fp, "	movl $%d, %s\n", atoi(&l.word[i][2]), eReg[j]);
					j++;
				}
			}
			fprintf(fp, "	call %s\n", l.word[3]);
			fprintf(fp, "	movl %%eax, %s\n", id2Reg(l.scope, l.word[0]));
		} else {
			// Atribuição exp
			if (l.word[2][0] == 'v') {
				fprintf(fp, "	movl %s, %%r8d\n", id2Reg(l.scope, l.word[2]));
			} else {
				fprintf(fp, "	movl $%d, %%r8d\n", atoi(&l.word[2][2]));
			}
			if (l.word[4][0] == 'v') {
				fprintf(fp, "	movl %s, %%r9d\n", id2Reg(l.scope, l.word[4]));
			} else {
				fprintf(fp, "	movl $%d, %%r8d\n", atoi(&l.word[4][2]));
			}

			if (l.word[3][0] == '+') fprintf(fp, "	addl %%r9d, %%r8d\n");
			else if (l.word[3][0] == '-') fprintf(fp, "	subl %%r9d, %%r8d\n");
			else if (l.word[3][0] == '*') fprintf(fp, "	imull %%r9d, %%r8d\n");
			else if (l.word[3][0] == '/') {
				fprintf(fp, "	movl %%r8d, %%ebx\n");
				fprintf(fp, "	movl %%r9d, %%ecx\n");
				fprintf(fp, "	movl %%ebx, %%eax\n");
				fprintf(fp, "	cltd\n");
				fprintf(fp, "	idivl %%ecx\n");
				fprintf(fp, "	movl %%eax, %%r8d\n");
			}
			fprintf(fp, "	movl %%r8d, %s\n", id2Reg(l.scope, l.word[0]));
		}
	} else if (strcmp(l.word[0], "get") == 0) {
		// Comando get
		if (l.word[1][0] == 'v'){
			fprintf(fp, "	leaq %s, %%r9\n", id2Reg(l.scope, l.word[1]));
		} else {
			fprintf(fp, "	movq %s, %%r9\n", id2Reg(l.scope, l.word[1]));
		}
		fprintf(fp, "	movq $%d, %%r8\n", atoi(&l.word[3][2]));
		fprintf(fp, "	imulq $4, %%r8\n");
		fprintf(fp, "	addq %%r9, %%r8\n");
		fprintf(fp, "	movl (%%r8), %%r9d\n");
		fprintf(fp, "	movl %%r9d, %s\n", id2Reg(l.scope, l.word[5]));
	} else if (strcmp(l.word[0], "set") == 0) {
		// Comando set
		if (l.word[1][0] == 'v'){
			fprintf(fp, "	leaq %s, %%r9\n", id2Reg(l.scope, l.word[1]));
		} else {
		 	fprintf(fp, "	movq %s, %%r9\n", id2Reg(l.scope, l.word[1]));
		}

		fprintf(fp, "	movq $%d, %%r8\n", atoi(&l.word[3][2]));
		fprintf(fp, "	imulq $4, %%r8\n");
		fprintf(fp, "	addq %%r9, %%r8\n");

		if (l.word[5][0] == 'c') {
			fprintf(fp, "	movq $%d, (%%r8)\n", atoi(&l.word[5][2]));
		} else {
			fprintf(fp, "	movl %s, %%r9d\n", id2Reg(l.scope, l.word[5]));
			fprintf(fp, "	movl %%r9d, (%%r8)\n");
		}
	} else if (strcmp(l.word[0], "if") == 0) {
		if (l.word[1][0] == 'v') {
			fprintf(fp, "	cmpl $0, %s\n", id2Reg(l.scope, l.word[1]));
			fprintf(fp, "	je endif%d\n", l.n);
		} else {
			fprintf(fp, "	cmpl $0, $%d\n", atoi(&l.word[5][2]));
			fprintf(fp, "	je endif%d\n", l.n);
		}
	} else if (strcmp(l.word[0], "endif") == 0) {
		fprintf(fp, "endif%d:\n", l.n - 2);
	} else if (strcmp(l.word[0], "return") == 0) {
		fprintf(fp, "	movq %%r12, -8(%%rbp)\n");
		fprintf(fp, "	movq %%r13, -16(%%rbp)\n");
		fprintf(fp, "	movq %%r14, -24(%%rbp)\n");
		fprintf(fp, "	movq %%r15, -32(%%rbp)\n\n");
		if (l.word[1][0] == 'c') {
			fprintf(fp, "	movl $%d, %%eax\n\n", atoi(&l.word[1][2]));
		} else {
			fprintf(fp, "	movl %s, %%eax\n\n", id2Reg(l.scope, l.word[1]));
		}
		
		fprintf(fp, "	leave\n");
		fprintf(fp, "	ret\n");
	}
	fprintf(fp, "\n");
}

void wFn(Function * fn) {
	FILE * fp;
	int i, j;
	char str[MAXSTRSIZE] = "nada";

	fp = fopen("IO/trad.S", "a+");

	fprintf(fp, ".globl %s\n%s:\n", fn->id, fn->id);
	fprintf(fp, "	pushq %%rbp\n");
	fprintf(fp, "	movq %%rsp, %%rbp\n");
	fprintf(fp, "	subq $%d, %%rsp\n", fn->stackMem);
	fprintf(fp, "	movq %%r12, -8(%%rbp)\n");
	fprintf(fp, "	movq %%r13, -16(%%rbp)\n");
	fprintf(fp, "	movq %%r14, -24(%%rbp)\n");
	fprintf(fp, "	movq %%r15, -32(%%rbp)\n");

	for (i = 0; i < fn->nLV; ++i) {
		fprintf(fp, "#	%s = %s\n", fn->localVars[i].id, fn->localVars[i].cReg);
	}
	fprintf(fp, "\n");


	for (i = 0; i < fn->nP; ++i) {
		if(fn->p[i].type == 'i') {
			fprintf(fp, "	movl %s, %%r%dd\n", fn->p[i].cReg, 12 + i);
			sprintf(fn->p[i].cReg, "%%r%dd", 12 + i);
		}
		else if(fn->p[i].type == 'a'){
			fprintf(fp, "	movq %s, %%r%d\n", fn->p[i].cReg, 12 + i);
			sprintf(fn->p[i].cReg, "%%r%d", 12 + i);
		}
	}
	fprintf(fp, "\n");

	for (i = 0; i < fn->size;i++) {
		wCmd(fp, fn->body[i]);
	}

	fclose(fp);
}