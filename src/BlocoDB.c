/**\file BlocoDB.c
 * \brief Base de dados de blocos
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: BlocoDB.c \n
 * DESCRIÇÃO: Base de dados de blocos
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#include "BlocoDB.h"

Bloco *bloco_2_pontos;
Bloco *bloco_bomba;
Bloco *blco_azul;
Bloco *bloco_riscas;

Vector *blocos_jogo;

void addBlock(Bloco *bloco) {
	push_backVector(blocos_jogo, bloco);
}

void delBlocoDB(Bloco *bloco) {
	unsigned int i = 0;
	unsigned int j = sizeVector(blocos_jogo);
	for (; i < j; ++i) {
		void *pos_vec = elementAtVector(blocos_jogo, i);
		if (*(Bloco**)pos_vec == bloco) {
			delBloco(bloco);
			pos_vec = get_back_element(blocos_jogo);
			pop_backVector(blocos_jogo);
		}
	}
}


void loadBlocks() {
	blocos_jogo = newVector(sizeof(Bloco*), 64, 0);
}
