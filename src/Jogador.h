/**\file Jogador.h
 * \brief M�dulo que cont�m informa��o acerca do jogador do jogo)
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Jogador.h \n
 * DESCRI��O: M�dulo que cont�m informa��o acerca do jogador do jogo) \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 
#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Mapa.h"
#include <stdlib.h>

typedef struct {
	unsigned int pontuacao;
	Mapa *mapa_actual;
	char nome[];
} Jogador;


///Fun�ao que cria um Jogador com a devida pontuacao,  o mapa e  o seu nome
Jogador* createJogador();

///Fun�ao actualiza os dados do jogador
void updateJogador();

#endif
