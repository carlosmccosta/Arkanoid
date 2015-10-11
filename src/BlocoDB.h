/**\file BlocoDB.h
 * \brief Base de dados de blocos
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: BlocoDB.h \n
 * DESCRIÇÃO: Base de dados de blocos
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#ifndef BLOCODB_H_
#define BLOCODB_H_

#include "Bloco.h"
#include "Vector.h"

extern Vector *blocos_jogo;

///Funçao que adiciona um determinado bloco ao vector de blocos
void addBlock(Bloco *bloco);

void addBlockDB(Bloco *bloco);
void delBloco(Bloco *bloco);


#endif

