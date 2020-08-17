#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pilha.h"
#include "Matriz.h"
#include "Fila.h"

// Alunos: John Eric Jahn && Luiz Guilherme

int main(int argc, char *argv[]) {
	Matriz matrizAdjacencia;
	Pilha pilha;
	FILE *file;
	int *vetorStatus, *vetorAntecessores;
	int tam, verticeInicial, verticeFinal, i, j, temp, achou;
	Fila fila;
	
	printf("______________________________________________________________________\n");
	printf("				AVISO!!\n\n");
	printf("  RESPEITE O TAMANHO DEFINIDO DA MATRIZ COM A QUE ESTA NO ARQUIVO\n");
	printf("______________________________________________________________________\n\n");
	
	printf("Digite o tamanho da matriz: ");
	scanf("%d", &tam);
	
	inicializa_matriz(&matrizAdjacencia, tam, tam);
	inicializa_fila(&fila, tam);
	
	file = fopen("grafos.txt", "r");
	
	if(file == NULL) {
		printf("Arquivo nao pode ser aberto\n");
		return 0;
	}
	
	for(i=0; i<tam; i++) {
		for(j=0; j<tam; j++) {
			int valorCelula;
			fscanf(file, "%d", &valorCelula);
			if(valorCelula == 1) {
				modifica_valor_matriz(&matrizAdjacencia, i, j, valorCelula);
			}
		}
	}
	
	printf("___________________________________________\n\n");
	
	mostra_matriz(matrizAdjacencia);
	
	vetorStatus = malloc(sizeof(int) * tam);
	memset(vetorStatus, 0, sizeof(int) * tam);
	
	vetorAntecessores = malloc(sizeof(int) * tam);
	memset(vetorAntecessores, 0, sizeof(int) * tam);
	
	
	printf("\nDigite o vertice inicial de busca: ");
	scanf("%d", &verticeInicial);
	verticeInicial = verticeInicial - 1;
	
	printf("\nDigite o vertice final de busca: ");
	scanf("%d", &verticeFinal);
	verticeFinal = verticeFinal - 1;
	
	vetorStatus[verticeInicial] = 1;
	inserir(&fila, verticeInicial);
	achou = 0; // Falso
			
	while(remover(&fila, &temp) != ERRO_PILHA_VAZIA && achou == 0) {
		if(temp == verticeFinal) {
			achou = 1;
		}
		
		for(i=0; i<tam; i++) {
			int value;
			le_valor_matriz(matrizAdjacencia, temp, i, &value);
			
			if(value == 1) {
				if(vetorStatus[i] == 0) {
					vetorStatus[i] = 1;
					vetorAntecessores[i] = temp;
					inserir(&fila, i);
				}	
			}
		}
		
	}
	
	int w;
	for(w=0; w<tam; w++) {
		printf("%d\n", vetorAntecessores[w]);
	}
	
	/*
	if(achou == 1) {
		inicializa_pilha(&pilha, tam);
		while(vetorAntecessores[verticeFinal] != 0) {
		}
	}	
	*/

	
	desaloca_matriz(&matrizAdjacencia);
	desaloca_pilha(&pilha);
	desaloca_fila(&fila);
	
	return 0;
}
