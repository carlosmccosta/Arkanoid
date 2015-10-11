/**\file Nave.h
 * \brief M�dulo com as subrotinas necess�rias para o uso da nave do jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Naves.h \n
 * DESCRI��O: M�dulo com as subrotinas necess�rias para o uso da nave do jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef NAVE_H_
#define NAVE_H_

#include "Sprite.h"
#include "Teclado.h"
#include "Rato.h"
#include "GraficaVideo.h"

#include "xpm\NaveParada.xpm"
#include "xpm\NaveEsquerda.xpm"
#include "xpm\NaveDireita.xpm"

#define MOVEMENTS_OFFSET_NAVE 15

#define NAVE_LEFT_OFFSET_IN_XPM 48
#define NAVE_RIGHT_OFFSET_IN_XPM 52

typedef struct {
	int x;
	int y;
} NavePos;


extern volatile NavePos nave_pos;

extern Sprite* nave_parada;
extern Sprite* nave_esquerda;
extern Sprite* nave_direita;

///Fun�ao que inicializa a nave
void init_naves();

///fun�ao que apaga a sprite do Jogo
void del_naves_screen();

///Fun�ao que destroy todos as naves(parada,esquerda,direita)
void destroy_naves();

///fun�ao que actualiza a posi�ao da nave
void sync_naves_pos();

///Fun�ao que controla a nave com o rato
void moveNaveMouse(int dx, int dy);

///Fun�ao que controla a nave com o teclado
void moveNaveKbd(unsigned char SC);


#endif
