#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>

#define ALTURA 25
#define LARGURA 71

#define VERTICAL 186
#define HORIZONTAL 205
#define ESPACO ' '
#define BOLA 254
#define RAQUETE 219

typedef enum direcao {
	SOBE,
	DESCE,
	DIREITA,
	ESQUERDA
}Direcao;

typedef struct bola {
	int x, y;
	int d;
}Bola;

typedef struct raquete1 {
	int x, y, z;
}Raquete1;

typedef struct raquete2 {
	int x, y, z;
}Raquete2;

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2);
void desenha_tela(char tela[ALTURA][LARGURA]);

int main()
{
	char tela[ALTURA][LARGURA];
	Bola b;
	int movimento_bola;
	Raquete1 r1;
	Raquete2 r2;

	inicia(tela, &b, &r1, &r2);
	desenha_tela(tela);

	printf("\n");
	system("pause");
	return 0;
}

void desenha_tela(char tela[ALTURA][LARGURA])
{
	int i, j;

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			/*if (tela[i][j] == 'o')
			{
				printf(" ");
			}
			else
			{*/
				printf("%c", tela[i][j]);
			//}
		}
		printf("\n");
	}
}

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2)
{
	int i, j, k;

	for (i = 0; i < ALTURA; i += (ALTURA - 1))
	{
		for (j = 0; j < LARGURA; j++)
		{
			tela[i][j] = HORIZONTAL;
		}
	}
	for (i = 0; i < ALTURA - 1; i++)
	{
		for (j = 0; j < LARGURA; j += (LARGURA - 1))
		{
			tela[i][j] = VERTICAL;
		}
	}
	for (i = 1; i < ALTURA - 1; i++)
	{
		for (j = 1; j < LARGURA - 1; j++)
		{
			tela[i][j] = ESPACO;
		}
	}

	tela[0][0] = 201;
	tela[0][LARGURA - 1] = 187;
	tela[ALTURA - 1][0] = 200;
	tela[ALTURA - 1][LARGURA - 1] = 188;

	i = ALTURA / 2;
	j = LARGURA / 2;
	tela[i][j] = BOLA;
	b->x = i;
	b->y = j;
	srand(time(NULL));
		b->d = rand() % ESQUERDA;

	i = (ALTURA / 2);
	j = (ALTURA / 2) - 1;
	k = (ALTURA / 2) + 1;
	tela[i][LARGURA - 2] = RAQUETE;
	tela[j][LARGURA - 2] = RAQUETE;
	tela[k][LARGURA - 2] = RAQUETE;
	r1->x = i;
	r1->y = j;
	r1->z = k;

	i = (ALTURA / 2);
	j = (ALTURA / 2) - 1;
	k = (ALTURA / 2) + 1;
	tela[i][1] = RAQUETE;
	tela[j][1] = RAQUETE;
	tela[k][1] = RAQUETE;
	r2->x = i;
	r2->y = j;
	r2->z = k;
}