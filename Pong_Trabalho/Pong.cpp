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

#define limpa_tela() system("cls")
#define dorme(millis) Sleep(millis)

typedef enum direcao {
	SOBE,
	DESCE,
	DIREITA,
	ESQUERDA
}Direcao;

typedef struct bola {
	int x, y;
	int d;
	Direcao n;
}Bola;

typedef struct raquete1 {
	int x, y, z;
	Direcao raq1;
}Raquete1;

typedef struct raquete2 {
	int x, y, z;
	direcao raq2;
}Raquete2;

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2);
void desenha_tela(char tela[ALTURA][LARGURA]);
void movBall_up(char tela[ALTURA][LARGURA], Bola *b);
void movBall_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right(char tela[ALTURA][LARGURA], Bola *b);
void moveBall_left(char tela[ALTURA][LARGURA], Bola *b);
void move_ball(char tela[ALTURA][LARGURA], Bola *b);
void movRaquete1(char tela[ALTURA][LARGURA], Raquete1 *r1, int direcao_raquete1);

int main()
{
	char tela[ALTURA][LARGURA];
	Bola b;
	int movimento_bola;
	Raquete1 r1;
	Raquete2 r2;
	int direcao_raquete1, direcao_raquete2;

	inicia(tela, &b, &r1, &r2);

	while (1) 
	{
		limpa_tela();
		desenha_tela(tela);
		if (_kbhit())
		{
			direcao_raquete1 = _getch();
			movRaquete1(tela, &r1, direcao_raquete1);
		}
		dorme(1);
	}

	return 0;
}

void desenha_tela(char tela[ALTURA][LARGURA])
{
	int i, j;

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			printf("%c", tela[i][j]);
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

void movBall_up(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->x--;
	tela[b->x][b->y] = BOLA;
}

void movBall_down(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->x++;
	tela[b->x][b->y] = BOLA;
}

void movBall_right(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->y--;
	tela[b->x][b->y] = BOLA;
}

void movBall_left(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->y++;
	tela[b->x][b->y] = BOLA;
}

void move_ball(char tela[ALTURA][LARGURA], Bola *b)
{
	
	if (b->n == SOBE)
	{
		if (b->x > 1)
		{
			movBall_up(tela, b);
		}
		else
		{
			b->n = DESCE;
			movBall_down(tela, b);
		}
	}
	else if (b->n == DESCE)
	{
		if (b->x < ALTURA - 1)
		{
			movBall_down(tela, b);
		}
		else
		{
			b->n = SOBE;
			movBall_up(tela, b);
		}
	}
}

void movRaquete1 (char tela[ALTURA][LARGURA],Raquete1 *r1, int direcao_raquete1)
{
	if (direcao_raquete1 = 'a')
	{
		tela[r1->x][r1->z] = ESPACO;
		tela[r1->y + 1][1] = RAQUETE;
	}
}