#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define T 200000

int main() {

	//Programa que gera os numeros crescentes

	FILE * arq;

	int i;

	char sizes[9][6] = {"100", "500", "1000", "5000", "30000", "80000", "100000", "150000", "200000"};


	arq = fopen("200000.txt", "wt");

	if (arq == NULL) {
		printf("Problema de leitura\n");
		return 0;
	}

	int j, num;

	for (j = T; j >= 1; j--) {

		num = j;

		fprintf(arq, "%d ", num);

	}
	
	fclose(arq);
	printf("Acabou\n");



	return 0;

}
