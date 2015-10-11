/**\file Nave.h
 * \brief Módulo com as subrotinas necessárias para o uso da nave do jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Naves.h \n
 * DESCRIÇÃO: Módulo com as subrotinas necessárias para o uso da nave do jogo \n
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

///Funçao que inicializa a nave
void init_naves();

///funçao que apaga a sprite do Jogo
void del_naves_screen();

///Funçao que destroy todos as naves(parada,esquerda,direita)
void destroy_naves();

///funçao que actualiza a posiçao da nave
void sync_naves_pos();

///Funçao que controla a nave com o rato
void moveNaveMouse(int dx, int dy);

///Funçao que controla a nave com o teclado
void moveNaveKbd(unsigned char SC);


#endif
