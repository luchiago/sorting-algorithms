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
 * Insertion Sort							*
 * 											*
 ********************************************/

#include <stdio.h> //biblioteca padr�o de C
#include <stdlib.h> //biblioteca padr�o de C
#include <string.h> //fun��es para manipula��o de strings
#include <time.h> //para testes de tempo

#define S 9 //define o tamanho do vetor de tamanhos

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

	strcpy(path, "./resultados/insertion_sort/comparacao/");

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
	strcpy(path, "./resultados/insertion_sort/tempo/");

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

void insertion_sort(int vector[], int tamanho, int tipo) {

	//Insertion Sort - algoritmo de ordena��o
	
	clock_t start, end;// para medir o tempo, vem da time.h
	double tempo_processamento;

	double comparacao = 0; //conta as compara��es feitas

	int i, j, chave;

	start = clock();
	
	for (i = 1; i < tamanho; i++) {
		comparacao++; //FOR
		chave = vector[i];
		j = i - 1;

		while(j >= 0 && vector[j] > chave) {
			comparacao++; //IF
			vector[j + 1] = vector[j];
			j--;
		}
		comparacao++; //FOR
		vector[j + 1] = chave;

	}
	comparacao++; //FOR

	end = clock();

	tempo_processamento = ((double) (end - start)) / CLOCKS_PER_SEC;

	grava_tempo(tempo_processamento, tamanho, tipo);
	grava_comparacao(comparacao, tamanho, tipo);

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

	for (i = 0; i < S; i++) {

		//Vai iterar todos os arquivos

		tamanho = sizes[i]; //aqui ele pega o tamanho no vetor de tamanhos
		
		int vector[tamanho];

		for(t = 0; t < 3; t++) {
			tipo = ordem[t];
			abre_arquivo(vector, tamanho, tipo);
			//get_vector(vector, tamanho);
			//system("pause");
			insertion_sort(vector, tamanho, tipo);
			//get_vector(vector, tamanho);
			//system("pause");
		}

	}

	return 0;

}
