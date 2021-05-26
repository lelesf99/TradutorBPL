#include "trad.h"

FILE * fp;

void initAssembly() {
	fp = fopen("IO/trad.S", "w+");

	fprintf(fp, "# TRADUÇÂO:\n");
	fprintf(fp, ".section .rodata\n");
	fprintf(fp, ".data\n");
	fprintf(fp, ".text\n");

	fclose(fp);
}

void writeFn(Function fn) {
	int i, j;

	fp = fopen("IO/trad.S", "a+");

	fprintf(fp, ".globl f%c\nf%c:\n", fn.id, fn.id);
	fprintf(fp, "	pushq %%rbp\n");
	fprintf(fp, "	movq %%rsp, %%rbp\n");
	fprintf(fp, "	subq $%d, %%rsp\n", fn.stackMem);
	fprintf(fp, "	movq %%r12, -8(%%rbp)\n");
	fprintf(fp, "	movq %%r13, -16(%%rbp)\n");
	fprintf(fp, "	movq %%r14, -24(%%rbp)\n");
	fprintf(fp, "	movq %%r15, -32(%%rbp)\n");



	fprintf(fp, "	movq %%r12, -8(%%rbp)\n");
	fprintf(fp, "	movq %%r13, -16(%%rbp)\n");
	fprintf(fp, "	movq %%r14, -24(%%rbp)\n");
	fprintf(fp, "	movq %%r15, -32(%%rbp)\n");
	fprintf(fp, "	leave\n");
	fprintf(fp, "	ret\n");

	fclose(fp);
}