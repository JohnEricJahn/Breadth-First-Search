#include <stdio.h>
#include <stdlib.h>
#include "Matriz.h"

int inicializa_matriz(Matriz *p, int l, int c) {
	int i, j;
		
	p->m = malloc(l * sizeof(int*));
	if(p->m == NULL) {
		return 0;
	}
	for(i=0; i<l; i++) {
		p->m[i] = malloc(c * sizeof(int));
		if(p->m[i] == NULL) {
			return 0;
		}
	}
	
	p->lin = l;
	p->col = c;
	
	for(i=0; i<l; i++) {
		for(j=0; j<c; j++){
			p->m[i][j] = 0;
		}
	}
	
	return 1; // Sucesso
}

void desaloca_matriz(Matriz *p) {
	int i;
	for(i=0; i<p->lin; i++){
		free(p->m[i]);
	}
	free(p->m);
}

void mostra_matriz(Matriz x){
	int i, j;
	for(i=0; i<x.lin; i++) {
		for(j=0; j<x.col; j++) {
			printf("%4d", x.m[i][j]);
		}
		printf("\n");
	}
	printf("___________________________________________\n");
}

int modifica_valor_matriz(Matriz *p, int i, int j, int valor) {
	if(i >= p->lin || j >= p->col) {
		return ERRO_COORDENADA_INVALIDA;
	}
	
	p->m[i][j] = valor;
	return 1; // Sucesso
}

int le_valor_matriz(Matriz x, int i, int j, int *pValor) {
	if(i >= x.lin || j>= x.col) {
		return ERRO_COORDENADA_INVALIDA;
	}
	
	*pValor = x.m[i][j];
	return 1; // Sucesso
}

int compara_matrizes(Matriz x, Matriz y) {
	if(x.lin != y.lin || x.col != y.col) {
		return 0;
	}
	
	int i, j;
	for(i=0; i<x.lin; i++) {
		for(j=0; j<x.col; j++) {
			if(x.m[i][j] != y.m[i][j]) {
				return 0;
			}
		}
	}
	
	return 1; // Sucesso
}

int soma_matrizes(Matriz x, Matriz y, Matriz *p) {
	if(x.lin != y.lin || x.col != y.col) {
		return ERRO_MATRIZES_INCOMPATIVEIS;
	}
	
	inicializa_matriz(p, x.lin, x.col);
	int i, j;
	for(i=0; i<x.lin; i++) {
		for(j=0; j<x.lin; j++) {
			p->m[i][j] = x.m[i][j] + y.m[i][j];
		}
	}
	
	return 1; // Sucesso
}

int multiplica_matrizes(Matriz x, Matriz y, Matriz *p) {
	if(x.col != y.lin) {
		return ERRO_MATRIZES_INCOMPATIVEIS;
	}
	
	inicializa_matriz(p, x.lin, y.col);
	int i, j, k;
	for(i=0; i<x.lin; i++) {
		for(j=0; j<x.col; j++) {
			int soma = 0;
			for(k=0; k<x.col; k++) {
				soma += x.m[i][k] * y.m[k][j];
			}
			p->m[i][j] = soma;
		}
	}
	
	return 1; // Sucesso
	
}

