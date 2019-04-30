#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define S 9

double comparacao;

typedef struct {
	
	double cpu;
	
	int size;
	
	int type;
	
}time_cpu;


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

void grava_comparacao(int tamanho, int tipo) {
	
	FILE * comp;//arquivo para gravar os resultados de comparacao
	
	char path[50]; //caminho para o arquivo
	char type[5]; //para guardar o ".txt"
	char arquivo[10]; //para guardar o nome do arquivo
	char ordem[15];
	
	//./resultados/bubble_sort/comparacao
	strcpy(path, "./resultados/merge_sort/comparacao/");
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
	
	comp = fopen (path, "wt");

	if (comp == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}
	
	fprintf(comp, "%.0lf\n", comparacao);
	fclose(comp);
}

void grava_tempo(time_cpu cpu_time_used) {
	
	FILE * tempo;//arquivo para gravar os resultados de tempo
	
	char path[50]; //caminho para o arquivo
	char type[5]; //para guardar o ".txt"
	char arquivo[10]; //para guardar o nome do arquivo
	char ordem[15];
	
	//./resultados/bubble_sort/tempo
	strcpy(path, "./resultados/merge_sort/tempo/");
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

void get_vector(int tamanho, int * vector) {

	//Função que imprime o vetor

	int i;

	for (i = 0; i < tamanho; i++)
		printf("%d ", vector[i]);
	printf("\n");

}

void merge(int vector[], int p, int q, int r) {
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	int L[n1 + 1];
	int R[n2 + 1];

	for(i = 0; i < n1; i++) {
		comparacao++;
		L[i] = vector[p + i];
	}
	comparacao++;
	
	for(j = 0; j < n2; j++) {
		comparacao++;
		R[j] = vector[q + j + 1];
	}
	comparacao++;

	L[n1] = 123456798;
	R[n2] = 123456798;
	i = 0;
	j = 0;

	for(k = p; k <= r; k++) {
		comparacao++;//FOR
		comparacao++;//IF
		if(L[i] <= R[j]) {
			vector[k] = L[i];
			i = i + 1;
		} else {
			vector[k] = R[j];
			j = j + 1;
		}
	}
	comparacao++;//FOR
}

void merge_sort(int vector[], int p, int r) {
	
	comparacao++;//IF
	if(p < r) {
		int q = (p + r) / 2;
		merge_sort(vector, p, q);
		merge_sort(vector, q + 1, r);
		merge(vector, p, q, r);
	}
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
	
	clock_t start, end;// para medir o tempo, vem da time.h
	time_cpu cpu_time_used;

	int i, t;

	for (i = 0; i < S; i++) {

		//Vai iterar todos os arquivos

		tamanho = sizes[i]; //aqui ele pega o tamanho no vetor de tamanhos

		for(t = 0; t < 3; t++) {
			tipo = ordem[t];

			int * vector = abre_arquivo(tamanho, tipo);

			comparacao = 0;
			start = clock();
			//passa tamanho - 1 para acesso correto
			merge_sort(vector, 0, tamanho - 1);
			
			end = clock();

			cpu_time_used.cpu = ((double) (end - start)) / CLOCKS_PER_SEC;
			cpu_time_used.size = tamanho;
			cpu_time_used.type = tipo;

			grava_tempo(cpu_time_used);
			
			grava_comparacao(tamanho, tipo);

		}

	}

	return 0;

}
