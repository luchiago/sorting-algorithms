#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 10

int* abre_arquivo(int tamanho) {
	FILE * arq; //variável para guardar o ponteiro pro arquivo
	char path[15]; //caminho para o arquivo
	char type[5];
	char arquivo[10];

	strcpy(path, "./vetores/");
	strcpy(type, ".txt");

	sprintf(arquivo, "%d", tamanho); //converte o tamanho para char

	strcat(path, arquivo);//concatena as strings
	strcat(path, type);

	arq = fopen(path, "rt");

	int * vector = malloc(tamanho * sizeof(int));
	//uso de malloc para alocar espaço para o vetor na memória e poder ser acessada em outro escopo

	if (arq == NULL) {
		printf("Problema de leitura\n");
		return 0;
	}

	int result, i;

	for (i = 0; i < tamanho; i++) {
		fscanf(arq, "%d", &result);
		vector[i] = result;
	}
	
	fclose(arq);
	
	return vector;
}

void get_vector(int tamanho, int * vector) {
	int i;

	for (i = 0; i < tamanho; i++)
		printf("%d ", vector[i]);
	printf("\n");

}

void bubble_sort(int tamanho, int * vector) {

	//Bubble Sort
	int i, j, aux;
	for (i = 0; i < tamanho; i++) {
		for (j = 0; j < tamanho - 1; j++) {
			if(vector[j] > vector[j + 1]) {
				aux = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = aux;
			}
		}
	}
	
	printf("\nVetor ordenado por bubble sort de tamanho %d\n", tamanho);
	get_vector(tamanho, vector);

}

int main() {

	int tamanho; //variável para guardar o tamanho corrente do vetor
	int sizes[S] = {100, 500, 1000, 5000, 30000, 80000, 100000, 150000, 200000};
	//vetor que guarda os tamanhos de vetores a serem testados

	printf("Bubble Sort\n");

	int i;

	for (i = 0; i < S; i++) {
		printf("\n----------------------------------------\n");
		printf("Tamanho do vetor: %d\n", sizes[i]);

		tamanho = sizes[i];

		int * vector = abre_arquivo(tamanho);

		printf("\nVetor desordenado de tamanho %d\n", tamanho);
		get_vector(tamanho, vector);

		bubble_sort(tamanho, vector);

	}

	return 0;

}
