#include "Pong.h"

void desenha_tela(char tela[ALTURA][LARGURA], Raquete *r1, Raquete *r2, Score *s)
{
	int i, j;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (tela[1][2] == ESPACO || tela[1][3] == ESPACO || tela[1][4] == ESPACO || tela[1][5] == ESPACO || tela[1][6] == ESPACO || tela[1][8] == ESPACO || tela[1][10] == ESPACO || tela[1][LARGURA - 11] == ESPACO || tela[1][LARGURA - 10] == ESPACO || tela[1][LARGURA - 9] == ESPACO || tela[1][LARGURA - 8] == ESPACO || tela[1][LARGURA - 7] == ESPACO || tela[1][LARGURA - 5] == ESPACO || tela[1][LARGURA - 3] == ESPACO)
	{
		score(s->score1, s->score2);
	}

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			if (tela[i][j] == tela[r1->centro][LARGURA - 2])
			{
				SetConsoleTextAttribute(hConsole, 1);
				putchar(tela[i][j]);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 4);
				putchar(tela[i][j]);
			}
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			putchar('\n');
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

void move_ball(char tela[ALTURA][LARGURA], Bola *b, Raquete *r1, Raquete *r2, Score *s)
{
	int h = 1;
	if (b->n == DIREITA)
	{
		if (tela[b->x][b->y] != tela[r1->centro][LARGURA - 3])
		{
			movBall_right(tela, b);
		}
		else if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		if (b->y == LARGURA)
		{
			ERROU;
			s->score1++;
			if (s->score1 == '9' + 1)
			{
				h = 0;
			}
			else
			{
				h = 1;
			}
			inicia(tela, b, r1, r2, s, h);
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
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		if (b->y == 0)
		{
			ERROU;
			s->score2++;
			if (s->score2 == '9' + 1)
			{
				h = 0;
			}
			else
			{
				h = 1;
			}
			inicia(tela, b, r1, r2, s, h);
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
			if (s->score2 == '9' + 1)
			{
				h = 0;
			}
			else
			{
				h = 1;
			}
			inicia(tela, b, r1, r2, s, h);
		}
		if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			if (r2->centro != ALTURA / 2)
			{
				b->n = (Direcao)(rand() % 6);
				if (b->n == 4 || b->n == 5)
				{
					b->n = DIREITA_DESCE;
					BOLA_RAQUETE;
					movBall_right_down(tela, b);
				}
				else if (b->n == 2 || b->n == 3)
				{
					b->n = DIREITA_SOBE;
					BOLA_RAQUETE;
					movBall_right_up(tela, b);
				}
				else if (b->n == 0 || b->n == 1)
				{
					b->n = DIREITA;
					BOLA_RAQUETE;
					movBall_right(tela, b);
				}
			}
			else
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
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
			if (s->score2 == '9' + 1)
			{
				h = 0;
			}
			else
			{
				h = 1;
			}
			inicia(tela, b, r1, r2, s, h);
		}
		if (tela[b->x][b->y] == tela[r2->centro][2])
		{
			if (r2->centro != ALTURA / 2)
			{
				b->n = (Direcao)(rand() % 6);
				if (b->n == 4 || b->n == 5)
				{
					b->n = DIREITA_DESCE;
					BOLA_RAQUETE;
					movBall_right_down(tela, b);
				}
				else if (b->n == 2 || b->n == 3)
				{
					b->n = DIREITA_SOBE;
					BOLA_RAQUETE;
					movBall_right_up(tela, b);
				}
				else if (b->n == 0 || b->n == 1)
				{
					b->n = DIREITA;
					BOLA_RAQUETE;
					movBall_right(tela, b);
				}
			}
			else
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r2->base][2])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r2->topo][2])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = DIREITA_DESCE;
				BOLA_RAQUETE;
				movBall_right_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = DIREITA_SOBE;
				BOLA_RAQUETE;
				movBall_right_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = DIREITA;
				BOLA_RAQUETE;
				movBall_right(tela, b);
			}
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
		if (b->y == LARGURA || b->x == BORDA_SUPERIOR_DIREITA || b->x == BORDA_INFERIOR_DIREITA)
		{
			ERROU;
			s->score1++;
			if (s->score1 == '9' + 1)
			{
				h = 0;
			}
			else
			{
				h = 1;
			}
			inicia(tela, b, r1, r2, s, h);
		}
		if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			if (r1->centro != ALTURA / 2)
			{
				b->n = (Direcao)(rand() % 6);
				if (b->n == 4 || b->n == 5)
				{
					b->n = ESQUERDA_DESCE;
					BOLA_RAQUETE;
					movBall_left_down(tela, b);
				}
				else if (b->n == 2 || b->n == 3)
				{
					b->n = ESQUERDA_SOBE;
					BOLA_RAQUETE;
					movBall_left_up(tela, b);
				}
				else if (b->n == 0 || b->n == 1)
				{
					b->n = ESQUERDA;
					BOLA_RAQUETE;
					movBall_left(tela, b);
				}
			}
			else
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
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
			if (s->score1 == '9' + 1)
			{
				h = 0;
			}
			else
			{
				h = 1;
			}
			inicia(tela, b, r1, r2, s, h);
		}
		if (tela[b->x][b->y] == tela[r1->centro][LARGURA - 3])
		{
			if (r1->centro != ALTURA / 2)
			{
				b->n = (Direcao)(rand() % 6);
				if (b->n == 4 || b->n == 5)
				{
					b->n = ESQUERDA_DESCE;
					BOLA_RAQUETE;
					movBall_left_down(tela, b);
				}
				else if (b->n == 2 || b->n == 3)
				{
					b->n = ESQUERDA_SOBE;
					BOLA_RAQUETE;
					movBall_left_up(tela, b);
				}
				else if (b->n == 0 || b->n == 1)
				{
					b->n = ESQUERDA;
					BOLA_RAQUETE;
					movBall_left(tela, b);
				}
			}
			else
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r1->topo][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
		else if (tela[b->x][b->y] == tela[r1->base][LARGURA - 3])
		{
			b->n = (Direcao)(rand() % 6);
			if (b->n == 4 || b->n == 5)
			{
				b->n = ESQUERDA_DESCE;
				BOLA_RAQUETE;
				movBall_left_down(tela, b);
			}
			else if (b->n == 2 || b->n == 3)
			{
				b->n = ESQUERDA_SOBE;
				BOLA_RAQUETE;
				movBall_left_up(tela, b);
			}
			else if (b->n == 0 || b->n == 1)
			{
				b->n = ESQUERDA;
				BOLA_RAQUETE;
				movBall_left(tela, b);
			}
		}
	}
}

void movRaquete1_up(char tela[ALTURA][LARGURA], Raquete *r1)
{
	if (r1->centro == ALTURA / 2 || r1->topo == ALTURA / 2 || r1->base == ALTURA / 2)
	{
		tela[r1->base][LARGURA - 2] = ESPACO;
		r1->topo--;
		r1->centro--;
		r1->base--;
		tela[r1->topo][LARGURA - 2] = RAQUETE;
		tela[r1->centro][LARGURA - 2] = RAQUETE;
		tela[r1->topo][LARGURA - 2] = RAQUETE;
	}
	else
	{
		tela[r1->centro][LARGURA - 2] = ESPACO;
		tela[r1->base][LARGURA - 2] = ESPACO;
		r1->topo = r1->topo - 2;
		r1->centro = r1->centro - 2;
		r1->base = r1->base - 2;
		tela[r1->topo][LARGURA - 2] = RAQUETE;
		tela[r1->centro][LARGURA - 2] = RAQUETE;
		tela[r1->topo][LARGURA - 2] = RAQUETE;
	}
}

void movRaquete1_down(char tela[ALTURA][LARGURA], Raquete *r1)
{
	if (r1->centro == ALTURA / 2 || r1->topo == ALTURA / 2 || r1->base == ALTURA / 2)
	{
		tela[r1->topo][LARGURA - 2] = ESPACO;
		r1->topo++;
		r1->centro++;
		r1->base++;
		tela[r1->base][LARGURA - 2] = RAQUETE;
		tela[r1->centro][LARGURA - 2] = RAQUETE;
		tela[r1->base][LARGURA - 2] = RAQUETE;
	}
	else
	{
		tela[r1->centro][LARGURA - 2] = ESPACO;
		tela[r1->topo][LARGURA - 2] = ESPACO;
		r1->topo = r1->topo + 2;
		r1->centro = r1->centro + 2;
		r1->base = r1->base + 2;
		tela[r1->base][LARGURA - 2] = RAQUETE;
		tela[r1->centro][LARGURA - 2] = RAQUETE;
		tela[r1->base][LARGURA - 2] = RAQUETE;
	}
}

void dirRaquetes(char tela[ALTURA][LARGURA], Raquete *r1, int dir, Raquete *r2)
{
	if (dir == 'k')
	{
		r1->raq = SOBE;
		if (tela[r1->topo][LARGURA - 2] != tela[1][LARGURA - 2])
		{
			movRaquete1_up(tela, r1);
		}
	}
	else if (dir == 'm')
	{
		r1->raq = DESCE;
		if (tela[r1->base][LARGURA - 2] != tela[ALTURA - 2][LARGURA - 2])
		{
			movRaquete1_down(tela, r1);
		}
	}
	else if (dir == 'a')
	{
		r2->raq = SOBE;
		if (tela[r2->topo][1] != tela[1][1])
		{
			movRaquete2_up(tela, r2);
		}
	}
	else if (dir == 'z')
	{
		r2->raq = DESCE;
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

void movRaquete2_up(char tela[ALTURA][LARGURA], Raquete *r2)
{
	if (r2->centro == ALTURA / 2 || r2->topo == ALTURA / 2 || r2->base == ALTURA / 2)
	{
		tela[r2->base][1] = ESPACO;
		r2->topo--;
		r2->centro--;
		r2->base--;
		tela[r2->topo][1] = RAQUETE;
		tela[r2->centro][1] = RAQUETE;
		tela[r2->topo][1] = RAQUETE;
	}
	else
	{
		tela[r2->centro][1] = ESPACO;
		tela[r2->base][1] = ESPACO;
		r2->topo = r2->topo - 2;
		r2->centro = r2->centro - 2;
		r2->base = r2->base - 2;
		tela[r2->topo][1] = RAQUETE;
		tela[r2->centro][1] = RAQUETE;
		tela[r2->topo][1] = RAQUETE;
	}
}

void movRaquete2_down(char tela[ALTURA][LARGURA], Raquete *r2)
{
	if (r2->centro == ALTURA / 2 || r2->topo == ALTURA / 2 || r2->base == ALTURA / 2)
	{
		tela[r2->topo][1] = ESPACO;
		r2->topo++;
		r2->centro++;
		r2->base++;
		tela[r2->base][1] = RAQUETE;
		tela[r2->centro][1] = RAQUETE;
		tela[r2->base][1] = RAQUETE;
	}
	else
	{
		tela[r2->centro][1] = ESPACO;
		tela[r2->topo][1] = ESPACO;
		r2->topo = r2->topo + 2;
		r2->centro = r2->centro + 2;
		r2->base = r2->base + 2;
		tela[r2->base][1] = RAQUETE;
		tela[r2->centro][1] = RAQUETE;
		tela[r2->base][1] = RAQUETE;
	}
}

void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete *r1, Raquete *r2, Score *s, int h)
{
	int i, j, k;

	if (h == 0)
	{
		menu(tela);
	}

	else
	{
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

	tela[1][1] = 'E';
	tela[1][2] = 'S';
	tela[1][3] = 'C';

	limpa_tela();
	INTRO;
	SetConsoleTextAttribute(hC, 8);
	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			putchar(tela[i][j]);
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			putchar('\n');
		}
	}

	while (m != 13)
	{
		m = _getch();
		if (m == ESC)
		{
			exit(0);
		}
		continue;
	}

	if (m == 13)
	{
		playerMenu(tela);
	}
}

void playerMenu(char tela[ALTURA][LARGURA])
{
	int i, j, m = 0;
	Seta s;
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

	for (i = 13; i < 42; i++)
	{
		tela[7][i] = HORIZONTAL;
		tela[15][i] = HORIZONTAL;
	}

	for (i = 8; i < 15; i++)
	{
		tela[i][12] = VERTICAL;
		tela[i][42] = VERTICAL;
	}

	tela[7][12] = BORDA_SUPERIO_ESQUERDA;
	tela[7][42] = BORDA_SUPERIOR_DIREITA;
	tela[15][12] = BORDA_INFERIOR_ESQUERDA;
	tela[15][42] = BORDA_INFERIOR_DIREITA;

	tela[9][21] = SETA;
	tela[9][23] = '1';
	tela[9][24] = ' ';
	tela[9][25] = 'P';
	tela[9][26] = 'L';
	tela[9][27] = 'A';
	tela[9][28] = 'Y';
	tela[9][29] = 'E';
	tela[9][30] = 'R';
	s.x = 9;

	tela[11][23] = '2';
	tela[11][24] = ' ';
	tela[11][25] = 'P';
	tela[11][26] = 'L';
	tela[11][27] = 'A';
	tela[11][28] = 'Y';
	tela[11][29] = 'E';
	tela[11][30] = 'R';
	tela[11][31] = 'S';

	tela[13][23] = 'I';
	tela[13][24] = '.';
	tela[13][25] = 'A';
	tela[13][26] = '.';
	tela[13][28] = 'V';
	tela[13][29] = 'S';
	tela[13][31] = 'I';
	tela[13][32] = '.';
	tela[13][33] = 'A';
	tela[13][34] = '.';

	tela[16][22] = 'P';
	tela[16][23] = 'r';
	tela[16][24] = 'e';
	tela[16][25] = 's';
	tela[16][26] = 's';

	tela[16][28] = 'E';
	tela[16][29] = 'n';
	tela[16][30] = 't';
	tela[16][31] = 'e';
	tela[16][32] = 'r';

	tela[1][1] = 'E';
	tela[1][2] = 'S';
	tela[1][3] = 'C';

	limpa_tela();
	INTRO;
	SetConsoleTextAttribute(hC, 8);
	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			putchar(tela[i][j]);
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			putchar('\n');
		}
	}

	i = 0;
	j = 0;

	do
	{
		COORD cord;
		cord.X = 0;
		cord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		desenha_playerMenu(tela);
		m = _getch();
		if (m == ESC)
		{
			exit(0);
		}
		else if (m == BAIXO && s.x<13)
		{
				tela[s.x][21] = ESPACO;
				s.x = s.x + 2;
				tela[s.x][21] = SETA;
		}
		else if (m == CIMA && s.x>9)
		{
				tela[s.x][21] = ESPACO;
				s.x = s.x - 2;
				tela[s.x][21] = SETA;
		}

		if (m == ENTER)
		{
			if (tela[9][21] != ESPACO)
			{
				j = 1;
				i++;
			}
			else if (tela[11][21] != ESPACO)
			{
				j = 2;
				i++;
			}
			else if (tela[13][21] != ESPACO)
			{
				j = 3;
				i++;
			}
		}

		continue;
	} while (i != 1 && i != 2);

	if (j == 2 || j == 3)
	{
		main(j, 1, 0);
	}
	else
	{
		menu_dificuldade(tela, j, 1);
	}
}

void desenha_menu_dificuldade(char tela[ALTURA][LARGURA])
{

	int i, j;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			putchar(tela[i][j]);
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			putchar('\n');
		}
	}
}

void menu_dificuldade(char tela[ALTURA][LARGURA], int player, int n)
{
	int i, j, m = 0;
	Seta s;
	HANDLE hC;
	int dificuldade = 0;

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

	tela[10][21] = SETA;
	tela[10][23] = 'H';
	tela[10][24] = 'A';
	tela[10][25] = 'R';
	tela[10][26] = 'D';
	s.x = 10;

	tela[12][23] = 'M';
	tela[12][24] = 'E';
	tela[12][25] = 'D';
	tela[12][26] = 'I';
	tela[12][27] = 'U';
	tela[12][28] = 'M';

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

	tela[1][1] = 'E';
	tela[1][2] = 'S';
	tela[1][3] = 'C';

	limpa_tela();
	INTRO;
	SetConsoleTextAttribute(hC, 8);
	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			putchar(tela[i][j]);
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			putchar('\n');
		}
	}

	i = 0;
	j = 0;

	do
	{
		COORD cord;
		cord.X = 0;
		cord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		desenha_menu_dificuldade(tela);
		while (1)
		{
			if (_kbhit())
			{
				m = _getch();
				if (m == ESC)
				{
					exit(0);
				}
				else if (m == BAIXO && s.x < 12)
					{
						tela[s.x][21] = ESPACO;
						s.x = s.x + 2;
						tela[s.x][21] = SETA;
					}
				else if (m == CIMA && s.x > 10)
					{
						tela[s.x][21] = ESPACO;
						s.x = s.x - 2;
						tela[s.x][21] = SETA;
					}
				else if (m == ENTER)
				{
					if (tela[10][21] != ESPACO)
					{
						dificuldade = 2;
						i++;
					}
					else if (tela[12][21] != ESPACO)
					{
						dificuldade = 1;
						i++;
					}
				}
				break;
			}
		}
		continue;
	} while (i != 1 && i != 2);

	main(player, 1, dificuldade);
}

void movRaquete1Player_up(char tela[ALTURA][LARGURA], Raquete *r1)
{
	tela[r1->base][LARGURA - 2] = ESPACO;
	r1->topo--;
	r1->centro--;
	r1->base--;
	tela[r1->topo][LARGURA - 2] = RAQUETE;
	tela[r1->centro][LARGURA - 2] = RAQUETE;
	tela[r1->topo][LARGURA - 2] = RAQUETE;
}

void movRaquete1Player_down(char tela[ALTURA][LARGURA], Raquete *r1)
{
	tela[r1->topo][LARGURA - 2] = ESPACO;
	r1->topo++;
	r1->centro++;
	r1->base++;
	tela[r1->base][LARGURA - 2] = RAQUETE;
	tela[r1->centro][LARGURA - 2] = RAQUETE;
	tela[r1->base][LARGURA - 2] = RAQUETE;
}

void dirRaquetes_1Player(char tela[ALTURA][LARGURA], Raquete *r1, int dir)
{
	if (dir == 'k')
	{
		r1->raq = SOBE;
		if (tela[r1->topo][LARGURA - 2] != tela[1][LARGURA - 2])
		{
			movRaquete1Player_up(tela, r1);
		}
	}
	else if (dir == 'm')
	{
		r1->raq = DESCE;
		if (tela[r1->base][LARGURA - 2] != tela[ALTURA - 2][LARGURA - 2])
		{
			movRaquete1Player_down(tela, r1);
		}
	}
	else if (dir == ESC)
	{
		exit(0);
	}
}

void movRaquete2PC_up(char tela[ALTURA][LARGURA], Raquete *r, int i)
{
	tela[r->base][i] = ESPACO;
	tela[r->centro][i] = ESPACO;
	tela[r->topo][i] = ESPACO;
	r->topo--;
	r->centro--;
	r->base--;
	tela[r->base][i] = RAQUETE;
	tela[r->centro][i] = RAQUETE;
	tela[r->topo][i] = RAQUETE;
}

void movRaquete2PC_down(char tela[ALTURA][LARGURA], Raquete *r, int i)
{
	tela[r->base][i] = ESPACO;
	tela[r->centro][i] = ESPACO;
	tela[r->topo][i] = ESPACO;
	r->topo++;
	r->centro++;
	r->base++;
	tela[r->base][i] = RAQUETE;
	tela[r->centro][i] = RAQUETE;
	tela[r->topo][i] = RAQUETE;
}

void move_raquetePC(char tela[ALTURA][LARGURA], Bola *b, Raquete *r2, Raquete *r1, int dificuldade)
{
	int i;

	if (dificuldade == 1)
	{
		if (rand() % 10 != 1)
		{
			i = 1;
			if (b->x > r2->centro && r2->base != ALTURA - 2 && (b->n == ESQUERDA || b->n == ESQUERDA_DESCE || b->n == ESQUERDA_SOBE))
			{
				movRaquete2PC_down(tela, r2, i);
			}
			else if (b->x < r2->centro && r2->topo != 1 && (b->n == ESQUERDA || b->n == ESQUERDA_DESCE || b->n == ESQUERDA_SOBE))
			{
				movRaquete2PC_up(tela, r2, i);
			}
		}
	}
	else if (dificuldade == 2)
	{
		if (rand() % 100 != 1)
		{
			i = 1;
			if (b->x > r2->centro && r2->base != ALTURA - 2 && (b->n == ESQUERDA || b->n == ESQUERDA_DESCE || b->n == ESQUERDA_SOBE))
			{
				movRaquete2PC_down(tela, r2, i);
			}
			else if (b->x < r2->centro && r2->topo != 1 && (b->n == ESQUERDA || b->n == ESQUERDA_DESCE || b->n == ESQUERDA_SOBE))
			{
				movRaquete2PC_up(tela, r2, i);
			}
		}
	}
	else if (dificuldade == 0)
	{
		if (b->x > r2->centro && r2->base != ALTURA - 2 && (b->n == ESQUERDA || b->n == ESQUERDA_DESCE || b->n == ESQUERDA_SOBE))
		{
			i = 1;
			movRaquete2PC_down(tela, r2, i);
		}
		else if (b->x < r2->centro && r2->topo != 1 && (b->n == ESQUERDA || b->n == ESQUERDA_DESCE || b->n == ESQUERDA_SOBE))
		{
			i = 1;
			movRaquete2PC_up(tela, r2, i);
		}



		else if (b->x > r1->centro && r1->base != ALTURA - 2 && (b->n == DIREITA || b->n == DIREITA_DESCE || b->n == DIREITA_SOBE))
		{
			i = LARGURA - 2;
			movRaquete2PC_down(tela, r1, i);
		}
		else if (b->x < r1->centro && r1->topo != 1 && (b->n == DIREITA || b->n == DIREITA_DESCE || b->n == DIREITA_SOBE))
		{
			i = LARGURA - 2;
			movRaquete2PC_up(tela, r1, i);
		}
	}
}

void desenha_playerMenu(char tela[ALTURA][LARGURA])
{
	int i, j;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			putchar(tela[i][j]);
		}

		if (i != ALTURA - 1 && j != LARGURA - 1)
		{
			putchar('\n');
		}
	}
}