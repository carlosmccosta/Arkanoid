/**\file Bloco.c
 * \brief Modulo que implementa os blocos a serem usados no jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Bloco.c \n
 * DESCRIÇÃO: Modulo que implementa os blocos a serem usados no jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 

#include "Bloco.h"

Bloco *createBloco(char *img[], int x, int y, int pontuation) {
	Sprite* sprt = create_sprite(img);
	sprt->x = x;
	sprt->y = y;
	Bloco *blk = (Bloco*)malloc(sizeof(Bloco*));
	blk->sprite = sprt;
	blk->pontuation = pontuation;
	blk->nave = false;
	
	return blk;
}

void delBloco (Bloco *bloco) {
	destroy_sprite(bloco->sprite);
	free(bloco);
}

void showBloco(Bloco *bloco) {
	draw_sprite(bloco->sprite, VIDEO_BASE_ADDRESS);
}

void remove_from_screen(Bloco *bloco) {
	delete_sprite(bloco->sprite, VIDEO_BASE_ADDRESS);
}

