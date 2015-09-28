#ifndef Header_h
#define Header_h

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
#define SETA 16
#define CIMA 72
#define BAIXO 80

#define ERROU PlaySound(TEXT("errou.wav"), NULL, SND_ASYNC)
#define BOLA_RAQUETE PlaySound(TEXT("batida.wav"), NULL, SND_ASYNC)
#define INTRO PlaySound(TEXT("intro.wav"), NULL, SND_LOOP | SND_ASYNC)

#define limpa_tela() system("cls")
#define dorme(millis) Sleep(millis)
#define contalargura() for(i = 0; tela[r->centro][i] == RAQUETE; i++)
#define score(x, y) tela[1][2] = 'S';\
					tela[1][3] = 'c';\
					tela[1][4] = 'o';\
					tela[1][5] = 'r';\
					tela[1][6] = 'e';\
					tela[1][8] = '=';\
					tela[1][10] = x;\
					tela[1][LARGURA - 11] = 'S';\
					tela[1][LARGURA - 10] = 'c';\
					tela[1][LARGURA - 9] = 'o';\
					tela[1][LARGURA - 8] = 'r';\
					tela[1][LARGURA - 7] = 'e';\
					tela[1][LARGURA - 5] = '=';\
					tela[1][LARGURA - 3] = y;

#define pause() tela[3][24] = 'P';\
				tela[3][25] = 'A';\
				tela[3][26] = 'U';\
				tela[3][27] = 'S';\
				tela[3][28] = 'E';

#define unpause() tela[3][24] = ' ';\
				  tela[3][25] = ' ';\
				  tela[3][26] = ' ';\
				  tela[3][27] = ' ';\
				  tela[3][28] = ' ';

typedef enum direcao {
	DIREITA,
	ESQUERDA,
	DIREITA_SOBE,
	ESQUERDA_SOBE,
	DIREITA_DESCE,
	ESQUERDA_DESCE,
	SOBE,
	DESCE
}Direcao;

typedef struct bola {
	int x, y;
	struct velocidade {
		int x = 1, y = 1;
	}velocidadeBola;
	Direcao n;
}Bola;

typedef struct raquete {
	int centro, topo, base;
	Direcao raq;
}Raquete;

typedef struct score {
	char score1 = 48, score2 = 48;
}Score;

typedef struct seta {
	int x;
}Seta;

void desenha_tela(char tela[ALTURA][LARGURA], Raquete *r1, Raquete *r2, Score *s);
void menu(char tela[ALTURA][LARGURA]);
void desenha_playerMenu(char tela[ALTURA][LARGURA]);
void playerMenu(char tela[ALTURA][LARGURA]);
void movBall_up(char tela[ALTURA][LARGURA], Bola *b);
void movBall_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right(char tela[ALTURA][LARGURA], Bola *b);
void moveBall_left(char tela[ALTURA][LARGURA], Bola *b);
void movBall_left_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_left_up(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right_down(char tela[ALTURA][LARGURA], Bola *b);
void movBall_right_up(char tela[ALTURA][LARGURA], Bola *b);
void move_ball(char tela[ALTURA][LARGURA], Bola *b, Raquete *r1, Raquete *r2, Score *s);
void movRaquete1_up(char tela[ALTURA][LARGURA], Raquete *r1);
void movRaquete1_down(char tela[ALTURA][LARGURA], Raquete *r1);
void dirRaquetes(char tela[ALTURA][LARGURA], Raquete *r1, int dir, Raquete *r2);
void movRaquete2_up(char tela[ALTURA][LARGURA], Raquete *r2);
void movRaquete2_down(char tela[ALTURA][LARGURA], Raquete *r2);
void movRaquete2_down(char tela[ALTURA][LARGURA], Raquete *r2);
void inicia(char tela[ALTURA][LARGURA], Bola *b, Raquete *r1, Raquete *r2, Score *s, int h);
void dirRaquetes_1Player(char tela[ALTURA][LARGURA], Raquete *r1, int dir);
void move_raquetePC(char tela[ALTURA][LARGURA], Bola *b, Raquete *r1, Raquete *r2, int dificuldade);
void movRaquete2PC_up(char tela[ALTURA][LARGURA], Raquete *r2, int i);
void movRaquete2PC_down(char tela[ALTURA][LARGURA], Raquete *r2, int i);
void movRaquete1Player_up(char tela[ALTURA][LARGURA], Raquete *r1);
void movRaquete1Player_down(char tela[ALTURA][LARGURA], Raquete *r1);
void menu_dificuldade(char tela[ALTURA][LARGURA], int player, int n);
void desenha_menu_dificuldade(char tela[ALTURA][LARGURA]);
int main(int player, int n, int dificuldade);

#endif