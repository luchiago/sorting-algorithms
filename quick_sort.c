/********************************************
 * Universidade Federal do Piauí			*
 * Centro de Ciências da Natureza			*
 * Bacharelado em Ciência da Computação		*
 * Projeto e Análise de Algoritmos			*
 * Docente: Guilherme Amaral Avelino		*
 * Discentes:								*
 *		Ana Paula da Silva Mendes			*
 * 		Lucas Hiago de Moura Vilela			*
 * 											*
 * Implementação do Algoritmo de Ordenação: *
 * Quick Sort								*
 * 											*
 ********************************************/

#include <stdio.h> //biblioteca padrão de C
#include <stdlib.h> //biblioteca padrão de C
#include <string.h> //funções para manipulação de strings
#include <time.h> //para testes de tempo

#define S 9 //define o tamanho do vetor de tamanhos

double comparacao; //variavel global devido o uso de funções recursivas e para medir as comparações

void abre_arquivo(int vector[], int tamanho, int tipo) {

	//Função para abertura dos arquivos com os números

	FILE * arq; //variável para guardar o ponteiro pro arquivo

	char path[30]; //caminho para o arquivo
	char tam[10]; //para guardar o nome do arquivo
	char caso[15]; //para guardar o caso (crescente, decrescente, aleatório)
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

	//Função para gravação do número de comparações

	FILE * comparacao; //arquivo para gravar os valores de quantidades de comparações

	char path[50]; //caminho para o arquivo
	char tam[10]; //para guardar o nome do arquivo
	char caso[15]; //para guardar o caso (crescente, decrescente, aleatório)
	char ext[5]; //para guardar o ".txt"

	strcpy(path, "./resultados/quick_sort/comparacao/");

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

	//Função para gravação do tempo

	FILE * temp; //arquivo para gravar os resultados de tempo

	char path[50]; //caminho para o arquivo
	char tam[10]; //para guardar o nome do arquivo
	char caso[15]; //para guardar o caso (crescente, decrescente, aleatório)
	char ext[5]; //para guardar o ".txt"

	//./resultados/bubble_sort/tempo
	strcpy(path, "./resultados/quick_sort/tempo/");

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

	//Função que imprime o vetor
	int i;

	for (i = 0; i < tamanho; i++)
		printf("%d ", vector[i]);
	printf("\n");
}

void quick_sort(int * vector, int p, int r) {

	//Quick sort - algoritmo de ordenação
	//Uso do quick sort alternativo
	int i = p;
	int j = r;
	int x = vector[(p + r) / 2];
	int aux;

	while(i <= j) {
		comparacao++;//While
		while(vector[i] < x) {
			comparacao++;//While
			i++;
		}
		comparacao++;//While
		
		while(vector[j] > x) {
			comparacao++;//While
			j--;
		}
		comparacao++;//While
		
		comparacao++;//If
		if(i <= j){
			aux = vector[i];
			vector[i] = vector[j];
			vector[j] = aux;
			i++;
			j--;
		}
	}
	comparacao++;//While
	
	comparacao++;//if
	if(p < j){
		quick_sort(vector, p, j);
	}
	
	comparacao++;//if
	if(r > i){
		quick_sort(vector, i, r);
	}
	
	//return vector;

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
			quick_sort(vector, 0, tamanho - 1);
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
