#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define T 200000

int main() {
	
	//Programa que gera os numeros aleatorios
	
	FILE * arq;

	char sizes[9][6] = {"100", "500", "1000", "5000", "30000", "80000", "100000", "150000", "200000"};

	srand(time(NULL));

	arq = fopen("200000.txt", "wt");

	if (arq == NULL) {
		printf("Problema de leitura\n");
		return 0;
	}

	int j, num;

	for (j = 0; j < T; j ++) {

		num = rand() % T;

		fprintf(arq, " % d ", num);

	}
	fclose(arq);
	printf("Acabou\n");
	return 0;
}
