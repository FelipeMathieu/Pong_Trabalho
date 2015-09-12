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
	int centro, topo, base;
	Direcao raq1;
}Raquete1;

typedef struct raquete2 {
	int centro, topo, base;
	direcao raq2;
}Raquete2;

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2);
void desenha_tela(char tela[ALTURA][LARGURA]);
void movBall_up(char tela[ALTURA][LARGURA], Bola *b);
void movBall_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right(char tela[ALTURA][LARGURA], Bola *b);
void moveBall_left(char tela[ALTURA][LARGURA], Bola *b);
void move_ball(char tela[ALTURA][LARGURA], Bola *b);
void movRaquete1_up(char tela[ALTURA][LARGURA], Raquete1 *r1);
void movRaquete1_down(char tela[ALTURA][LARGURA], Raquete1 *r1);
void dirBall(Bola *b, int direcao_bola);
void dirRaquete1(char tela[ALTURA][LARGURA], Raquete1 *r1, int dir);

int main()
{
	char tela[ALTURA][LARGURA];
	Bola b;
	int movimento_bola;
	Raquete1 r1;
	Raquete2 r2;
	int direcao_raquete1, direcao_raquete2;
	int direcao_bola;

	inicia(tela, &b, &r1, &r2);

	while (10) 
	{
		limpa_tela();
		desenha_tela(tela);
		if (_kbhit())
		{
			direcao_bola = _getch();
			dirBall(&b, direcao_bola);
			direcao_raquete1 = _getch();
			dirRaquete1(tela, &r1, direcao_raquete1);
		}
		move_ball(tela, &b);
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
	//b->n = SOBE;

	i = (ALTURA / 2);
	j = (ALTURA / 2) - 1;
	k = (ALTURA / 2) + 1;
	tela[i][LARGURA - 2] = RAQUETE;
	tela[j][LARGURA - 2] = RAQUETE;
	tela[k][LARGURA - 2] = RAQUETE;
	r1->centro = i;
	r1->topo = j;
	r1->base = k;

	i = (ALTURA / 2);
	j = (ALTURA / 2) - 1;
	k = (ALTURA / 2) + 1;
	tela[i][1] = RAQUETE;
	tela[j][1] = RAQUETE;
	tela[k][1] = RAQUETE;
	r2->centro = i;
	r2->topo = j;
	r2->base = k;
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
	b->y++;
	tela[b->x][b->y] = BOLA;
}

void movBall_left(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->y--;
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
		if (b->x < ALTURA - 2)
		{
			movBall_down(tela, b);
		}
		else
		{
			b->n = SOBE;
			movBall_up(tela, b);
		}
	}
	else if (b->n == DIREITA)
	{
		if (b->y < LARGURA - 3)
		{
			movBall_right(tela, b);
		}
		else
		{
			b->n = ESQUERDA;
			movBall_left(tela, b);
		}
	}
	else if (b->n == ESQUERDA)
	{
		if (b->y > 3)
		{
			movBall_left(tela, b);
		}
		else
		{
			b->n = DIREITA;
			movBall_right(tela, b);
		}
	}
}

void dirBall(Bola *b, int direcao_bola)
{
	if (direcao_bola == 'a')
	{
		b->n = ESQUERDA;
	}
	else if (direcao_bola == 'w')
	{
		b->n = SOBE;
	}
	else if (direcao_bola == 'd')
	{
		b->n = DIREITA;
	}
	else if (direcao_bola == 's')
	{
		b->n = DESCE;
	}
}

void movRaquete1_up(char tela[ALTURA][LARGURA], Raquete1 *r1)
{
	tela[r1->base][LARGURA - 2] = ESPACO;
	r1->topo--;
	r1->centro--;
	r1->base--;
	tela[r1->topo][LARGURA - 2] = RAQUETE;
	tela[r1->centro][LARGURA - 2] = RAQUETE;
	tela[r1->topo][LARGURA - 2] = RAQUETE;
}

void movRaquete1_down(char tela[ALTURA][LARGURA], Raquete1 *r1)
{
	
	tela[r1->topo][LARGURA - 2] = ESPACO;
	r1->topo++;
	r1->centro++;
	r1->base++;
	tela[r1->base][LARGURA - 2] = RAQUETE;
	tela[r1->centro][LARGURA - 2] = RAQUETE;
	tela[r1->base][LARGURA - 2] = RAQUETE;
}

void dirRaquete1(char tela[ALTURA][LARGURA], Raquete1 *r1, int dir)
{
	if (dir == 'k')
	{
		r1->raq1 = SOBE;
		if (tela[r1->topo][LARGURA - 2] != tela[1][LARGURA - 2])
		{
			movRaquete1_up(tela, r1);
		}
	}
	else if (dir == 'm')
	{
		r1->raq1 = DESCE;
		if (tela[r1->base][LARGURA - 2] != tela[ALTURA - 2][LARGURA - 2])
		{
			movRaquete1_down(tela, r1);
		}
	}
}