#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "Pilha.h"
#include "Matriz.h"
#include "Fila.h"

// Alunos: John Eric Jahn && Luiz Guilherme

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Portuguese");
	
	Matriz matrizAdjacencia;
	Pilha pilha;
	FILE *file;
	int *vetorStatus, *vetorAntecessores;
	int tam, verticeInicial, verticeFinal, i, j, temp, achou;
	Fila fila;
	
	printf("           *BREADTH FIRST SEARCH*            \n");
	
	file = fopen("grafos.txt", "r");
	
	if(file == NULL) {
		printf("Arquivo nao pode ser aberto\n");
		return 0;
	}
		
	fscanf(file, "%d", &tam);
	
	if(tam < 1) {		
		printf("O TAMANHO DA MATRIZ (1ª LINHA DO ARQUIVO) DEVE SER MAIOR QUE 0");
		exit(0);
	}
	
	inicializa_matriz(&matrizAdjacencia, tam, tam);
	inicializa_fila(&fila, tam);
	
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
	
	
	fscanf(file, "%d", &verticeInicial);
	verticeInicial = verticeInicial - 1;
	
	fscanf(file,"%d", &verticeFinal);
	verticeFinal = verticeFinal - 1;
	
	vetorStatus[verticeInicial] = 1;
	inserir(&fila, verticeInicial);
	achou = 0; // Falso
			
	while(remover(&fila, &temp) != ERRO_PILHA_VAZIA) {
		if(temp == verticeFinal) {
			achou = 1;
			break;
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
	
	if(achou == 1) {
		inicializa_pilha(&pilha, tam);
		while(verticeFinal != 0) {
			empilha(&pilha, verticeFinal);
			verticeFinal = vetorAntecessores[verticeFinal];
		}
		
		printf("\n *********** CAMINHO GERADO *********** \n");
		
		while(desempilha(&pilha, &temp) != ERRO_PILHA_VAZIA) {
			printf("%d\n", temp+1);
		}
	} else {
		printf("B não é alcançável a partir de A");
	}

	
	desaloca_matriz(&matrizAdjacencia);
	desaloca_pilha(&pilha);
	desaloca_fila(&fila);
	
	return 0;
}
