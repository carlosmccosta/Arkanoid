/**\file Jogador.c
 * \brief M�dulo que cont�m informa��o acerca do jogador do jogo)
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Jogador.c \n
 * DESCRI��O: M�dulo que cont�m informa��o acerca do jogador do jogo) \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Jogador.h"

Jogador* createJogador() {
	Jogador* jog = (Jogador*) malloc(sizeof(Jogador));
	jog->pontuacao = 0;
	return jog;
}

void updateJogador(Jogador *jogador, unsigned int pontuacao, Mapa *novo_mapa) {
	jogador->pontuacao = pontuacao;
	jogador->mapa_actual = novo_mapa;
}
