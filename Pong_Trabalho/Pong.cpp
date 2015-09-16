#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

#define ALTURA 25
#define LARGURA 55

#define VERTICAL 186
#define HORIZONTAL 205
#define ESPACO ' '
#define BOLA 254
#define RAQUETE 219 
#define BORDA_SUPERIO_ESQUERDA 201
#define BORDA_SUPERIOR_DIREITA 187
#define BORDA_INFERIOR_ESQUERDA 200
#define BORDA_INFERIOR_DIREITA 188
#define ESC 27
#define ENTER 13

#define ERROU PlaySound(TEXT("errou.wav"), NULL, SND_ASYNC)
#define BOLA_RAQUETE PlaySound(TEXT("batida.wav"), NULL, SND_ASYNC)
#define INTRO PlaySound(TEXT("intro.wav"), NULL, SND_LOOP || SND_ASYNC)

#define limpa_tela() system("cls")
#define dorme(millis) Sleep(millis)

typedef enum direcao {
	DIREITA,
	ESQUERDA,
	SOBE,
	DESCE,
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

typedef struct score {
	char score1 = 48, score2 = 48;
}Score;

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2, Score *s);
void desenha_tela(char tela[ALTURA][LARGURA], Raquete1 *r1, Raquete2 *r2);
void menu(char tela[ALTURA][LARGURA]);
void movBall_up(char tela[ALTURA][LARGURA], Bola *b);
void movBall_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right(char tela[ALTURA][LARGURA], Bola *b);
void moveBall_left(char tela[ALTURA][LARGURA], Bola *b);
void movBall_left_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_left_up(char tela[ALTURA][LARGURA], Bola *b); 
void movBall_right_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right_up(char tela[ALTURA][LARGURA], Bola *b);
void move_ball(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2, Score *s);
void movRaquete1_up(char tela[ALTURA][LARGURA], Raquete1 *r1);
void movRaquete1_down(char tela[ALTURA][LARGURA], Raquete1 *r1);
void dirRaquetes(char tela[ALTURA][LARGURA], Raquete1 *r1, int dir, Raquete2 *r2);
void movRaquete2_up(char tela[ALTURA][LARGURA], Raquete2 *r2);
void movRaquete2_down(char tela[ALTURA][LARGURA], Raquete2 *r2);

int main()
{
	char tela[ALTURA][LARGURA];
	Bola b;
	Raquete1 r1;
	Raquete2 r2;
	int dir, pause = 0;
	Score s;

	PTHREAD_START_ROUTINE();

	menu(tela);
	inicia(tela, &b, &r1, &r2, &s);

	while (1)
	{
		limpa_tela();
		desenha_tela(tela, &r1, &r2);
		if (_kbhit())
		{
			dir = _getch();
			while (dir == 'p' && pause == 0)
			{
				dir = _getch();
				if (dir == 'p')
				{
					pause++;
				}
				else
				{
					dir = 'p';
				}
			}
			pause = 0;
			dirRaquetes(tela, &r1, dir, &r2);
		}
		move_ball(tela, &b, &r1, &r2, &s);
	}
	return 0;
}

void desenha_tela(char tela[ALTURA][LARGURA], Raquete1 *r1, Raquete2 *r2)
{
	int i, j;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			if (tela[i][j] == tela[r1->centro][LARGURA - 2])
			{
				SetConsoleTextAttribute(hConsole, 1);
				printf("%c", tela[i][j]);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 4);
				printf("%c", tela[i][j]);
			}
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			printf("\n");
		}
	}
}

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2, Score *s)
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
	b->n = (Direcao)(rand() % 2);

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

	tela[1][2] = 'S';
	tela[1][3] = 'c';
	tela[1][4] = 'o';
	tela[1][5] = 'r';
	tela[1][6] = 'e';
	tela[1][8] = '=';
	tela[1][10] = s->score1;
	tela[1][LARGURA - 11] = 'S';
	tela[1][LARGURA - 10] = 'c';
	tela[1][LARGURA - 9] = 'o';
	tela[1][LARGURA - 8] = 'r';
	tela[1][LARGURA - 7] = 'e';
	tela[1][LARGURA - 5] = '=';
	tela[1][LARGURA - 3] = s->score2;

	if (s->score1 == '10' || s->score2 == '10')
	{
		main();
	}
}

void menu(char tela[ALTURA][LARGURA])
{
	int i, j, m = 0;
	HANDLE hC;

	hC = GetStdHandle(STD_OUTPUT_HANDLE);

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
	
	//Desenho do 'N'.
	for (i = 9; i < 15; i++)
	{
		tela[i][27] = BOLA;
		tela[i][33] = BOLA;
	}
	tela[9][28] = BOLA;
	tela[10][29] = BOLA;
	tela[11][30] = BOLA;
	tela[12][31] = BOLA;
	tela[13][32] = BOLA;
	tela[14][33] = BOLA;
	//Desenho do 'O'.
	for (i = 10; i < 14; i++)
	{
		tela[i][25] = BOLA;
		tela[i][20] = BOLA;
	}
	for (i = 20; i < 26; i++)
	{
		tela[9][i] = BOLA;
		tela[14][i] = BOLA;
	}
	//Desenho do 'P'.
	for (i = 14; i < 19; i++)
	{
		tela[9][i] = BOLA;
		tela[12][i] = BOLA;
	}
	for (i = 10; i < 15; i++)
	{
		tela[i][14] = BOLA;
	}
	tela[11][18] = BOLA;
	tela[10][18] = BOLA;
	//Desenho do 'G'.
	for (i = 9; i < 15; i++)
	{
		tela[i][35] = BOLA;
	}
	for (i = 35; i < 41; i++)
	{
		tela[9][i] = BOLA;
		tela[14][i] = BOLA;
	}
	tela[13][40] = BOLA;
	tela[12][40] = BOLA;
	tela[12][39] = BOLA;
	tela[12][38] = BOLA;

	for (i = 13; i < 42; i++)
	{
		tela[7][i] = HORIZONTAL;
		tela[16][i] = HORIZONTAL;
	}

	for (i = 8; i < 16; i++)
	{
		tela[i][12] = VERTICAL;
		tela[i][42] = VERTICAL;
	}

	tela[7][12] = BORDA_SUPERIO_ESQUERDA;
	tela[7][42] = BORDA_SUPERIOR_DIREITA;
	tela[16][12] = BORDA_INFERIOR_ESQUERDA;
	tela[16][42] = BORDA_INFERIOR_DIREITA;

	tela[17][22] = 'P';
	tela[17][23] = 'r';
	tela[17][24] = 'e';
	tela[17][25] = 's';
	tela[17][26] = 's';

	tela[17][28] = 'E';
	tela[17][29] = 'n'; 
	tela[17][30] = 't';
	tela[17][31] = 'e';
	tela[17][32] = 'r';

	limpa_tela();
	SetConsoleTextAttribute(hC, 8);
	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			printf("%c", tela[i][j]);
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			printf("\n");
		}
	}

	INTRO;

	while (m != 13)
	{
		m = _getch();
		if (m == ESC)
		{
			exit(0);
		}
	}
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

void move_ball(char tela[ALTURA][LARGURA], Bola *b, Raquete1 *r1, Raquete2 *r2, Score *s)
{
	int x;
	if (b->n == DIREITA)
	{
		if (tela[b->x][b->y] != tela[r1->centro][LARGURA - 3])
		{
			movBall_right(tela, b);
		}
		else
		{
			b->n = ESQUERDA;
			BOLA_RAQUETE;
			movBall_left(tela, b);
		}

		if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = ESQUERDA_SOBE;
			BOLA_RAQUETE;
			movBall_left_up(tela, b);
		}

		if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA_DESCE;
			BOLA_RAQUETE;
			movBall_left_down(tela, b);
		}

		if (b->y == LARGURA)
		{
			ERROU;
			s->score1++;
			inicia(tela, b, r1, r2, s);
		}
	}
	else if (b->n == ESQUERDA)
	{
		if (tela[b->x][b->y] != tela[r2->centro][2])
		{
			movBall_left(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			b->n = DIREITA;
			BOLA_RAQUETE;
			movBall_right(tela, b);
		}
		
		if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = DIREITA_SOBE;
			BOLA_RAQUETE;
			movBall_right_up(tela, b);
		}

		if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = DIREITA_DESCE;
			BOLA_RAQUETE;
			movBall_right_down(tela, b);
		}

		if (b->y == 0)
		{
			ERROU;
			s->score2++;
			inicia(tela, b, r1, r2, s);
		}
	}
	else if (b->n == ESQUERDA_SOBE)
	{
		if (b->x > 1)
		{
			movBall_left_up(tela, b);
		}
		else
		{
			b->n = ESQUERDA_DESCE;
			BOLA_RAQUETE;
			movBall_left_down(tela, b);
		}

		if (b->y == 0 || b->x == BORDA_SUPERIO_ESQUERDA || b->x == BORDA_INFERIOR_ESQUERDA)
		{
			ERROU;
			s->score2++;
			inicia(tela, b, r1, r2, s);
		}

		if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			if (r2->centro < ALTURA / 2)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (r2->centro > ALTURA / 2)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (r2->centro == ALTURA / 2)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = DIREITA_DESCE;
			BOLA_RAQUETE;
			movBall_right_down(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = DIREITA_SOBE;
			BOLA_RAQUETE;
			movBall_right_up(tela, b);
		}
	}
	else if (b->n == ESQUERDA_DESCE)
	{
		if (b->x < ALTURA - 2)
		{
			movBall_left_down(tela, b);
		}
		else
		{
			b->n = ESQUERDA_SOBE;
			BOLA_RAQUETE;
			movBall_left_up(tela, b);
		}

		if (b->y == 0 || b->x == BORDA_SUPERIO_ESQUERDA || b->x == BORDA_INFERIOR_ESQUERDA)
		{
			ERROU;
			s->score2++;
			inicia(tela, b, r1, r2, s);
		}

		if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			if (r2->centro < ALTURA / 2)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (r2->centro > ALTURA / 2)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (r2->centro == ALTURA / 2)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = DIREITA_DESCE;
			BOLA_RAQUETE;
			movBall_right_down(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = DIREITA_SOBE;
			BOLA_RAQUETE;
			movBall_right_up(tela, b);
		}
	}
	else if (b->n == DIREITA_SOBE)
	{
		if (b->x > 1)
		{
			movBall_right_up(tela, b);
		}
		else
		{
			b->n = DIREITA_DESCE;
			BOLA_RAQUETE;
			movBall_right_down(tela, b);
		}

		if (b->y == LARGURA || b->x == BORDA_SUPERIOR_DIREITA|| b->x == BORDA_INFERIOR_DIREITA)
		{
			ERROU;
			s->score1++;
			inicia(tela, b, r1, r2, s);
		}

		if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			if (r1->centro < ALTURA / 2)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (r1->centro > ALTURA / 2)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (r1->centro == ALTURA / 2)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = ESQUERDA_SOBE;
			BOLA_RAQUETE;
			movBall_left_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA_DESCE;
			BOLA_RAQUETE;
			movBall_left_down(tela, b);
		}
	}
	else if (b->n == DIREITA_DESCE)
	{
		if (b->x < ALTURA - 2)
		{
			movBall_right_down(tela, b);
		}
		else
		{
			b->n = DIREITA_SOBE;
			BOLA_RAQUETE;
			movBall_right_up(tela, b);
		}

		if (b->y == LARGURA || b->x == BORDA_SUPERIOR_DIREITA || b->x == BORDA_INFERIOR_DIREITA)
		{
			ERROU;
			s->score1++;
			inicia(tela, b, r1, r2, s);
		}

		if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			if (r1->centro < ALTURA / 2)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (r1->centro > ALTURA / 2)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (r1->centro == ALTURA / 2)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = ESQUERDA_SOBE;
			BOLA_RAQUETE;
			movBall_left_up(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = ESQUERDA_DESCE;
			BOLA_RAQUETE;
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
	else if (dir == ESC)
	{
		exit(0);
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