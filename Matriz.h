#define MAX 10
#define ERRO_COORDENADA_INVALIDA -1
#define ERRO_MATRIZES_INCOMPATIVEIS -2

typedef struct {
	int **m;
	int lin, col;
} Matriz;

int inicializa_matriz(Matriz *p, int l, int c);
void desaloca_matriz(Matriz *p);
void mostra_matriz(Matriz x);
int modifica_valor_matriz(Matriz *p, int i, int j, int valor);
int le_valor_matriz(Matriz x, int i, int j, int *pValor);
int compara_matrizes(Matriz x, Matriz y);
int soma_matrizes(Matriz x, Matriz y, Matriz *p);
int multiplica_matrizes(Matriz x, Matriz y, Matriz *p);


