#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define S 9

typedef struct {

	double cpu;

	int size;

	int type;

} time_cpu;

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

void grava_comparacao(double c, int tamanho, int tipo) {

	FILE * comparacao;//arquivo para gravar os resultados de comparacao

	char path[50]; //caminho para o arquivo
	char type[5]; //para guardar o ".txt"
	char arquivo[10]; //para guardar o nome do arquivo
	char ordem[15];

	//./resultados/bubble_sort/comparacao
	strcpy(path, "./resultados/insertion_sort/comparacao/");
	if (tipo == 1)
		strcpy(ordem, "crescente_");
	else if (tipo == 2)
		strcpy(ordem, "decrescente_");
	else
		strcpy(ordem, "random_");

	sprintf(arquivo, "%d", tamanho);
	strcpy(type, ".txt");

	strcat(path, ordem);
	strcat(path, arquivo);
	strcat(path, type);

	comparacao = fopen (path, "wt");

	if (comparacao == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fprintf(comparacao, "%.0lf\n", c);
	fclose(comparacao);
}

void grava_tempo(time_cpu cpu_time_used) {

	FILE * tempo;//arquivo para gravar os resultados de tempo

	char path[50]; //caminho para o arquivo
	char type[5]; //para guardar o ".txt"
	char arquivo[10]; //para guardar o nome do arquivo
	char ordem[15];

	//./resultados/bubble_sort/tempo
	strcpy(path, "./resultados/insertion_sort/tempo/");
	if (cpu_time_used.type == 1)
		strcpy(ordem, "crescente_");
	else if (cpu_time_used.type == 2)
		strcpy(ordem, "decrescente_");
	else
		strcpy(ordem, "random_");

	sprintf(arquivo, "%d", cpu_time_used.size);
	strcpy(type, ".txt");

	strcat(path, ordem);
	strcat(path, arquivo);
	strcat(path, type);

	tempo = fopen (path, "wt");

	if (tempo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fprintf(tempo, "%.5lf %d %d\n", cpu_time_used.cpu, cpu_time_used.size, cpu_time_used.type);
	fclose(tempo);

}

void insertion_sort(int tamanho, int * vector, int tipo) {

	//Insertion Sort - algoritmo de ordenação
	
	clock_t start, end;// para medir o tempo, vem da time.h
	time_cpu cpu_time_used;
	
	start = clock();
	int i, j, chave;

	double comparacao = 0;

	for (i = 1; i < tamanho; i++) {
		comparacao++;
		chave = vector[i];
		j = i - 1;

		while(j >= 0 && vector[j] > chave) {
			comparacao++;
			vector[j + 1] = vector[j];
			j--;
		}
		comparacao++;
		vector[j + 1] = chave;

	}
	comparacao++;

	end = clock();

	cpu_time_used.cpu = ((double) (end - start)) / CLOCKS_PER_SEC;
	cpu_time_used.size = tamanho;
	cpu_time_used.type = tipo;

	grava_tempo(cpu_time_used);
	grava_comparacao(comparacao, tamanho, tipo);

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

	for (i = 0; i < S; i++) {

		//Vai iterar todos os arquivos

		tamanho = sizes[i]; //aqui ele pega o tamanho no vetor de tamanhos

		for(t = 0; t < 3; t++) {
			tipo = ordem[t];

			int * vector = abre_arquivo(tamanho, tipo);

			insertion_sort(tamanho, vector, tipo);

		}

	}

	return 0;

}
