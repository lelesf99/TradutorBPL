#include <stdio.h>

int f3(int * pa1);

int main(int argc, char const *argv[]) {
	int teste;
	int va1[5] = {0,0,0,0,0};
	int va2[5] = {1,2,3,4,5};
	teste = f3(va1);
	printf("%d\n", teste);
	teste = f3(va2);
	printf("%d\n", teste);
	return 0;
}