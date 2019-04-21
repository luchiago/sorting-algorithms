#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 9

int * abre_arquivo(int tamanho, int tipo) {

	//Função para abertura dos arquivos com os numeros aleatorios

	FILE * arq; //variável para guardar o ponteiro pro arquivo
	char path[30]; //caminho para o arquivo
	char type[5]; //para guardar o ".txt"
	char arquivo[10]; //para guardar o nome do arquivo
	char ordem[15];

	strcpy(path, "./vetores/"); //copia para a variavel
	if (tipo == 1)
		strcpy(ordem, "crescente/");
	else if (tipo == 2)
		strcpy(ordem, "decrescente/");
	else
		strcpy(ordem, "random/");

	strcpy(type, ".txt");

	sprintf(arquivo, "%d", tamanho); //converte o tamanho para char

	//concatena as strings
	strcat(path, ordem);
	strcat(path, arquivo);
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
		fscanf(arq, "%d", & result);
		vector[i] = result;
	}

	fclose(arq);

	return vector;
}

void get_vector(int tamanho, int * vector) {

	//Função que imprime o vetor

	int i;

	for (i = 0; i < tamanho; i++)
		printf("%d ", vector[i]);
	printf("\n");

}

int * quick_sort(int * vector, int p, int r) {

	//Quick sort - algoritmo de ordenação
	//Uso do quick sort alternativo

	int i = p;
	int j = r;
	int x = vector[(p + r) / 2];
	int aux;

	while(i <= j) {
		while(vector[i] < x) {
			i++;
		}
		while(vector[j] > x) {
			j--;
		}
		if(i <= j){
			aux = vector[i];
			vector[i] = vector[j];
			vector[j] = aux;
			i++;
			j--;
		}
	}
	
	if(p < j){
		quick_sort(vector, p, j);
	}
	if(r > i){
		quick_sort(vector, i, r);
	}

	return vector;

}

int main() {

	int tamanho; //variável para guardar o tamanho corrente do vetor
	int sizes[S] = {100, 500, 1000, 5000, 30000, 80000, 100000, 150000, 200000};
	//vetor que guarda os tamanhos de vetores a serem testados

	int ordem[3] = {1, 2, 3};
	//vetor que guarda o tipo do arquivo
	//1 - crescente (Melhor caso)
	//2 - decrescente (Pior caso)
	//3 - aleatório
	int tipo;

	printf("Insertion Sort\n");

	int i, t;

	for (i = 0; i < S; i++) {

		//Vai iterar todos os arquivos

		printf("\n----------------------------------------\n");
		printf("Tamanho do vetor: %d\n", sizes[i]);

		tamanho = sizes[i]; //aqui ele pega o tamanho no vetor de tamanhos

		for(t = 0; t < 3; t++) {
			tipo = ordem[t];

			if (tipo == 1)
				printf("\nCrescente\n");
			else if (tipo == 2)
				printf("\nDecrescente\n");
			else
				printf("\nRandom\n");

			int * vector = abre_arquivo(tamanho, tipo);

			get_vector(tamanho, vector);

			//system("pause");

			//passa tamanho - 1 para acesso correto
			vector = quick_sort(vector, 0, tamanho - 1);

			get_vector(tamanho, vector);

			//system("pause");
		}

	}

	return 0;

}
