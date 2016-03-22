/*Nome: Felipe Vignoli Mathieu
  Nome: Vinicios Coelho
  Ciências da computação, 2º Período, matutino
  Game Pong
  
  MANUAL:
  Player 1:
'a' -> SOBE
'z' -> DESCE

Player 2:
'k' -> SOBE
'm' -> DESCE

Comando no jogo:
'p' -> PAUSE e UNPAUSE
ESC -> EXIT

SOBRE O JOGO:
De acordo com o que foi pedido pelo professor, tudo foi implementado corretamente. Mas
por conversar tidas com o mesmo em sala de aula, foi dada a ideia, para deixar o jogo 
mais dinâmico, que a direção que a bola pega-se ao colidir com a raquete fosse aleatória, 
então isso foi feito.*/

#include "Pong.h"

int main(int player, int n, int dificuldade)
{
	char tela[ALTURA][LARGURA];
	Bola b;
	Raquete r1, r2;
	int dir, pause = 0;
	Score s;
	int i, j;

	if (n != 1)
	{
		inicia(tela, &b, &r1, &r2, &s, 0);
	}
	else if (player == 2 && dificuldade == 0)
	{
		inicia(tela, &b, &r1, &r2, &s, player);

		while (1)
		{
			COORD cord;
			cord.X = 0;
			cord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
			desenha_tela(tela, &r1, &r2, &s);
			if (_kbhit())
			{
				dir = _getch();
				while (dir == 'p' && pause == 0)
				{
					pause();

					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
					desenha_tela(tela, &r1, &r2, &s);

					dir = _getch();
					if (dir == 'p')
					{
						unpause();
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
	else if (player == 1 && (dificuldade == 1 || dificuldade == 2))
	{
		inicia(tela, &b, &r1, &r2, &s, player);

		while (1)
		{
			COORD cord;
			cord.X = 0;
			cord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
			desenha_tela(tela, &r1, &r2, &s);
			if (_kbhit())
			{
				dir = _getch();
				while (dir == 'p' && pause == 0)
				{
					pause();

					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
					desenha_tela(tela, &r1, &r2, &s);

					dir = _getch();
					if (dir == 'p')
					{
						unpause();
						pause++;
					}
					else
					{
						dir = 'p';
					}
				}
				pause = 0;
				dirRaquetes_1Player(tela, &r1, dir);
			}
			move_ball(tela, &b, &r1, &r2, &s);
			move_raquetePC(tela, &b, &r2, &r1, dificuldade);
		}
		return 0;
	}
	else if (player == 3 && dificuldade == 0)
	{
		inicia(tela, &b, &r1, &r2, &s, player);

		while (1)
		{
			COORD cord;
			cord.X = 0;
			cord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
			desenha_tela(tela, &r1, &r2, &s);
			if (_kbhit())
			{
				dir = _getch();
				if (dir == ESC)
				{
					exit(0);
				}
				while (dir == 'p' && pause == 0)
				{
					pause();

					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
					desenha_tela(tela, &r1, &r2, &s);

					dir = _getch();
					if (dir == 'p')
					{
						unpause();
						pause++;
					}
					else
					{
						dir = 'p';
					}
				}
				pause = 0;
			}
			move_ball(tela, &b, &r1, &r2, &s);
			move_raquetePC(tela, &b, &r2, &r1, dificuldade);
		}
		return 0;
	}
}