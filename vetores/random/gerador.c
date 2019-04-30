#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {

	//Programa que gera os numeros aleatorios

	FILE * arq;

	int sizes[9] = {100, 500, 1000, 5000, 30000, 80000, 100000, 150000, 200000};

	srand(time(NULL));

	int i;

	for(i = 0; i < 9; i++) {
		char path[20];
		char arquivo[7];
		char t[20];
		
		sprintf(arquivo, "%d", sizes[i]);

		strcpy(t, arquivo);
		strcat(t, ".txt");
		
		strcpy(path, t);

		arq = fopen(path, "wt");

		if (arq == NULL) {
			printf("Problema de leitura\n");
			return 0;
		}

		int j, num;

		for (j = 0; j < sizes[i]; j ++) {

			num = rand() % sizes[i];

			fprintf(arq, "%d ", num);

		}
		fclose(arq);
	}

	printf("Acabou\n");
	return 0;
}
