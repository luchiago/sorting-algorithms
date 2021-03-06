/********************************************
 * Universidade Federal do Piau�			*
 * Centro de Ci�ncias da Natureza			*
 * Bacharelado em Ci�ncia da Computa��o		*
 * Projeto e An�lise de Algoritmos			*
 * Docente: Guilherme Amaral Avelino		*
 * Discentes:								*
 *		Ana Paula da Silva Mendes			*
 * 		Lucas Hiago de Moura Vilela			*
 * 											*
 * Implementa��o do Algoritmo de Ordena��o: *
 * Hibrido								 	*
 * Intro Sort								*
 * 											*
 ********************************************/

#include <stdio.h> //biblioteca padr�o de C
#include <stdlib.h> //biblioteca padr�o de C
#include <string.h> //fun��es para manipula��o de strings
#include <time.h> //para testes de tempo
#include <math.h>

#define S 9 //define o tamanho do vetor de tamanhos

double comparacao; //variavel global devido o uso de fun��es recursivas e para medir as compara��es

void abre_arquivo(int vector[], int tamanho, int tipo) {

	//Fun��o para abertura dos arquivos com os n�meros

	FILE * arq; //vari�vel para guardar o ponteiro pro arquivo

	char path[30]; //caminho para o arquivo
	char tam[10]; //para guardar o nome do arquivo
	char caso[15]; //para guardar o caso (crescente, decrescente, aleat�rio)
	char ext[5]; //para guardar o ".txt"

	strcpy(path, "./vetores/");

	if (tipo == 1)
		strcpy(caso, "crescente/");
	else if (tipo == 2)
		strcpy(caso, "decrescente/");
	else
		strcpy(caso, "random/");

	strcpy(ext, ".txt");

	sprintf(tam, "%d", tamanho); //converte o tamanho do vetor para char

	//concatena as strings
	strcat(path, caso);
	strcat(path, tam);
	strcat(path, ext);

	arq = fopen(path, "rt");

	if (arq == NULL) {
		printf("Problema de leitura\n");
		exit(1);
	}

	int result, i;

	for (i = 0; i < tamanho; i++) {
		fscanf(arq, "%d", & result);
		vector[i] = result;
	}

	fclose(arq);
}

void grava_comparacao(double c, int tamanho, int tipo) {

	//Fun��o para grava��o do n�mero de compara��es

	FILE * comparacao; //arquivo para gravar os valores de quantidades de compara��es

	char path[50]; //caminho para o arquivo
	char tam[10]; //para guardar o nome do arquivo
	char caso[15]; //para guardar o caso (crescente, decrescente, aleat�rio)
	char ext[5]; //para guardar o ".txt"

	strcpy(path, "./resultados/intro_sort/comparacao/");

	if (tipo == 1)
		strcpy(caso, "crescente_");
	else if (tipo == 2)
		strcpy(caso, "decrescente_");
	else
		strcpy(caso, "random_");

	strcpy(ext, ".txt");

	sprintf(tam, "%d", tamanho); //converte o tamanho do vetor para char

	//concatena as strings
	strcat(path, caso);
	strcat(path, tam);
	strcat(path, ext);

	comparacao = fopen (path, "wt");

	if (comparacao == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fprintf(comparacao, "%.0lf\n", c);
	fclose(comparacao);
}

void grava_tempo(double tempo, int tamanho, int tipo) {

	//Fun��o para grava��o do tempo

	FILE * temp; //arquivo para gravar os resultados de tempo

	char path[50]; //caminho para o arquivo
	char tam[10]; //para guardar o nome do arquivo
	char caso[15]; //para guardar o caso (crescente, decrescente, aleat�rio)
	char ext[5]; //para guardar o ".txt"

	//./resultados/bubble_sort/tempo
	strcpy(path, "./resultados/intro_sort/tempo/");

	if (tipo == 1)
		strcpy(caso, "crescente_");
	else if (tipo == 2)
		strcpy(caso, "decrescente_");
	else
		strcpy(caso, "random_");

	strcpy(ext, ".txt");

	sprintf(tam, "%d", tamanho); //converte o tamanho do vetor para char

	//concatena as strings
	strcat(path, caso);
	strcat(path, tam);
	strcat(path, ext);

	temp = fopen (path, "wt");

	if (temp == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fprintf(temp, "%.10lf\n", tempo);
	fclose(temp);

}

void get_vector(int vector[], int tamanho) {

	//Fun��o que imprime o vetor
	int i;

	for (i = 0; i < tamanho; i++)
		printf("%d ", vector[i]);
	printf("\n");
}

void swap(int vector[], int i, int j) {
	int aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

int parent(flag) {
	return (flag - 1) / 2;
}

int left(flag) {
	return 2 * flag + 1;
}
int right(flag) {
	return 2 * flag + 2;
}

void maxHeapify(int vector[], int index, int start, int end) {
	int size = end - start;
	int l = left(index);
	int r = right(index);
	int largest;
	comparacao++; //IF
	if (l < size && vector[start + l] > vector[start + index]) {
		largest = l;
	} else {
		largest = index;
	}
	comparacao++; //IF
	if (r < size && vector[start + r] > vector[start + largest]) {
		largest = r;
	}
	comparacao++; //IF
	if (largest != index) {
		swap(vector, start + largest, start + index);
		maxHeapify(vector, largest, start, end);
	}
}


void buildMaxHeap(int vector[], int start, int end) {
	int length = end - start;
	int index = parent(length - 1);
	while (index >= 0) {
		comparacao++; //WHILE
		maxHeapify(vector, index, start, end);
		index -= 1;
	}
	comparacao++; //WHILE
}

void heapSort(int vector[], int start, int end) {
	int i;
	buildMaxHeap(vector, start, end);
	for (i = end - 1; i > start; i--) {
		comparacao++; //FOR
		swap(vector, start, i);
		maxHeapify(vector, 0, start, i);
	}
	comparacao++; //FOR
}

int partition(int vector[], int start, int end) {
	int pivo = vector[start];
	int i = start - 1;
	int j = end;

	while (1) {
		comparacao++; //WHILE
		i += 1;
		while (vector[i] < pivo) {
			i += 1;
			comparacao++; //WHILE
		}
		comparacao++; //WHILE
		j -= 1;
		while (vector[j] > pivo) {
			j -= 1;
			comparacao++; //WHILE
		}
		comparacao++; //WHILE
		
		comparacao++; //IF
		if (i >= j) {
			return j;
		}
		swap(vector, i, j);
	}
	comparacao++; //WHILE
}

void introSortHelper(int vector[], int start, int end, int maxdepth) {
	
	comparacao++; //IF
	if (end - start <= 1) {
		return;
	} else if (maxdepth == 0) {
		comparacao++; //ELSE IF
		heapSort(vector, start, end);
	} else {
		int p = partition(vector, start, end);
		introSortHelper(vector, start, p + 1, maxdepth - 1);
		introSortHelper(vector, p + 1, end, maxdepth - 1);
	}
}

void introSort(int vector[], int n) {
	int maxdepth = 2 * log(n);
	introSortHelper(vector, 0, n, maxdepth);
}


int main() {

	int tamanho; //vari�vel para guardar o tamanho corrente do vetor
	int sizes[S] = {100, 500, 1000, 5000, 30000, 80000, 100000, 150000, 200000};
	//vetor que guarda os tamanhos de vetores a serem testados

	int ordem[3] = {1, 2, 3};
	//vetor que guarda o tipo do arquivo
	//1 - crescente (Melhor caso)
	//2 - decrescente (Pior caso)
	//3 - aleat�rio
	int tipo;

	int i, t;

	double tempo_processamento;
	clock_t start, end;// para medir o tempo, vem da time.h

	for (i = 0; i < S; i++) {

		//Vai iterar todos os arquivos

		tamanho = sizes[i]; //aqui ele pega o tamanho no vetor de tamanhos

		int vector[tamanho];

		for(t = 0; t < 3; t++) {
			tipo = ordem[t];
			abre_arquivo(vector, tamanho, tipo);
			//get_vector(vector, tamanho);
			//system("pause");

			comparacao = 0; //inicializa a variavel global

			start = clock();
			introSort(vector, tamanho);
			end = clock();

			//get_vector(vector, tamanho);
			//system("pause");

			tempo_processamento = ((double) (end - start)) / CLOCKS_PER_SEC;

			grava_tempo(tempo_processamento, tamanho, tipo);
			grava_comparacao(comparacao, tamanho, tipo);

		}

	}

	return 0;

}
