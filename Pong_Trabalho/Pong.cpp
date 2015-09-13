#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>

#define ALTURA 25
#define LARGURA 71

#define VERTICAL 186
#define HORIZONTAL 205
#define ESPACO ' '
#define BOLA 254
#define RAQUETE 219
#define BORDA_SUPERIO_ESQUERDA 201
#define BORDA_SUPERIOR_DIREITA 187
#define BORDA_INFERIOR_ESQUERDA 200
#define BORDA_INFERIOR_DIREITA 188

#define limpa_tela() system("cls")
#define dorme(millis) Sleep(millis)

typedef enum direcao {
	SOBE,
	DESCE,
	DIREITA,
	ESQUERDA,
	DIREITA_SOBE,
	DIREITA_DESCE,
	ESQUERDA_SOBE,
	ESQUERDA_DESCE
}Direcao;

typedef struct bola {
	int x, y;
	struct velocidade {
		int x = 1, y = 1;
	}velocidadeBola;
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
void movBall_left_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_left_up(char tela[ALTURA][LARGURA], Bola *b); 
void movBall_right_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right_up(char tela[ALTURA][LARGURA], Bola *b);
void move_ball(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2);
void movRaquete1_up(char tela[ALTURA][LARGURA], Raquete1 *r1);
void movRaquete1_down(char tela[ALTURA][LARGURA], Raquete1 *r1);
void dirRaquetes(char tela[ALTURA][LARGURA], Raquete1 *r1, int dir, Raquete2 *r2);
void movRaquete2_up(char tela[ALTURA][LARGURA], Raquete2 *r2);
void movRaquete2_down(char tela[ALTURA][LARGURA], Raquete2 *r2);

int main(void)
{
	char tela[ALTURA][LARGURA];
	Bola b;
	Raquete1 r1;
	Raquete2 r2;
	int dir;

	inicia(tela, &b, &r1, &r2);
	
	while (1) 
	{
		limpa_tela();
		desenha_tela(tela);
		if (_kbhit())
		{
			dir = _getch();
			dirRaquetes(tela, &r1, dir, &r2);
		}
		move_ball(tela, &b, &r1, &r2);
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

	tela[0][0] = BORDA_SUPERIO_ESQUERDA;
	tela[0][LARGURA - 1] = BORDA_SUPERIOR_DIREITA;
	tela[ALTURA - 1][0] = BORDA_INFERIOR_ESQUERDA;
	tela[ALTURA - 1][LARGURA - 1] = BORDA_INFERIOR_DIREITA;

	i = ALTURA / 2;
	j = LARGURA / 2;
	tela[i][j] = BOLA;
	b->x = i;
	b->y = j;
	b->n = DIREITA;

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

void movBall_left_down(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->x += b->velocidadeBola.x;
	b->y -= b->velocidadeBola.y;
	tela[b->x][b->y] = BOLA;
}

void movBall_left_up(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->x -= b->velocidadeBola.x;
	b->y -= b->velocidadeBola.y;
	tela[b->x][b->y] = BOLA;
}

void movBall_right_down(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->x += b->velocidadeBola.x;
	b->y += b->velocidadeBola.y;
	tela[b->x][b->y] = BOLA;
}

void movBall_right_up(char tela[ALTURA][LARGURA], Bola *b)
{
	tela[b->x][b->y] = ESPACO;
	b->x -= b->velocidadeBola.x;
	b->y += b->velocidadeBola.y;
	tela[b->x][b->y] = BOLA;
}

void move_ball(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2)
{
	
	if (b->n == DIREITA)
	{
		movBall_right(tela, b);
		if (b->y == LARGURA - 1)
		{
			main();
		}
		else if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			b->n = ESQUERDA;
			movBall_left(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = ESQUERDA_SOBE;
			movBall_left_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA_DESCE;
			movBall_left_down(tela, b);
		}
	}
	else if (b->n == ESQUERDA)
	{
		
		movBall_left(tela, b);
		if (b->y == 1)
		{
			main();
		}
		else if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			b->n = DIREITA;
			movBall_right(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = DIREITA_SOBE;
			movBall_right_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = DIREITA_DESCE;
			movBall_right_down(tela, b);
		}
	}
	else if (b->n == ESQUERDA_SOBE)
	{
		if (tela[b->x][b->y] == tela[0][ALTURA])
		{
			main();
		}
		else if (b->x > 1)
		{
			movBall_left_up(tela, b);
		}
		else if (b->x == 1)
		{
			b->n = ESQUERDA_DESCE;
			movBall_left_down(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			b->n = DIREITA;
			movBall_right(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = DIREITA_SOBE;
			movBall_right_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = DIREITA_DESCE;
			movBall_right_down(tela, b);
		}
	}
	else if (b->n == ESQUERDA_DESCE)
	{
		if (b->y == 0)
		{
			main();
		}
		else if (b->x < ALTURA - 2)
		{
			movBall_left_down(tela, b);
		}
		else if(b->x == ALTURA - 2)
		{
			b->n = ESQUERDA_SOBE;
			movBall_left_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			b->n = DIREITA;
			movBall_right(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = DIREITA_DESCE;
			movBall_right_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = DIREITA_SOBE;
			movBall_right_down(tela, b);
		}
	}
	else if (b->n == DIREITA_SOBE)
	{
		if (b->y == LARGURA)
		{
			main();
		}
		else if (b->x > 1)
		{
			movBall_right_up(tela, b);
		}
		else if (b->x == 1)
		{
			b->n = DIREITA_DESCE;
			movBall_right_down(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA;
			movBall_left(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = ESQUERDA_SOBE;
			movBall_left_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA_DESCE;
			movBall_left_down(tela, b);
		}
	}
	else if (b->n == DIREITA_DESCE)
	{
		if (b->y == LARGURA)
		{
		main();
		}
		else if (b->x < ALTURA - 2)
		{
			movBall_right_down(tela, b);
		}
		else if (b->x == ALTURA - 2)
		{
			b->n = DIREITA_SOBE;
			movBall_right_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			b->n = ESQUERDA;
			movBall_left(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = ESQUERDA_SOBE;
			movBall_left_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA_DESCE;
			movBall_left_down(tela, b);
		}
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

void dirRaquetes(char tela[ALTURA][LARGURA], Raquete1 *r1, int dir, Raquete2 *r2)
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
	else if (dir == 'a')
	{
		r2->raq2 = SOBE;
		if (tela[r2->topo][1] != tela[1][1])
		{
			movRaquete2_up(tela, r2);
		}
	}
	else if (dir == 'z')
	{
		r2->raq2 = DESCE;
		if (tela[r2->base][1] != tela[ALTURA - 2][1])
		{
			movRaquete2_down(tela, r2);
		}
	}
}

void movRaquete2_up(char tela[ALTURA][LARGURA], Raquete2 *r2)
{
	tela[r2->base][1] = ESPACO;
	r2->topo--;
	r2->centro--;
	r2->base--;
	tela[r2->topo][1] = RAQUETE;
	tela[r2->centro][1] = RAQUETE;
	tela[r2->topo][1] = RAQUETE;
}

void movRaquete2_down(char tela[ALTURA][LARGURA], Raquete2 *r2)
{

	tela[r2->topo][1] = ESPACO;
	r2->topo++;
	r2->centro++;
	r2->base++;
	tela[r2->base][1] = RAQUETE;
	tela[r2->centro][1] = RAQUETE;
	tela[r2->base][1] = RAQUETE;
}