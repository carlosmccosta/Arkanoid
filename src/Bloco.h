/**\file Bloco.h
 * \brief Modulo que implementa os blocos a serem usados no jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Bloco.h \n
 * DESCRI��O: Modulo que implementa os blocos a serem usados no jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 
 
#ifndef BLOCO_H_
#define BLOCO_H_

#include "Sprite.h"
#include "GraficaVideo.h"
#include "utypes.h"
#include <stdlib.h>


typedef struct {
	Sprite *sprite;
	int pontuation;
	Bool nave;
} Bloco;

///Fun�ao que cria um dado bloco numa certa posicao
Bloco *createBloco(char *img[], int x, int y, int pontuation);

///Funcao que elimina um determinado bloco
void delBloco(Bloco *bloco);

///Fun�ao que visualiza um determinado bloco
void showBloco(Bloco *bloco);

///Fun�ao que elimina do ecra um determinado bloco
void remove_from_screen(Bloco *bloco);

#endif
