/**\file MusicDB.h
 * \brief Base de dados de sons que serão usados durante o jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: MusicDB.h \n
 * DESCRIÇÃO: Base de dados de sons que serão usados durante o jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef MUSICDB_H_
#define MUSICDB_H_

#include <stdio.h>
#include <stdlib.h>

#include "Altifalante.h"
#include "Music.h"
#include "Songs.h"

#define MUSIC_DB_FILENAME "musicDB.txt"

///Base de dados de musicas
extern Vector* musicasDB;

/** Aloca memoria para a musica s e carrega-a com o
conteudo do ficheiro 'filename' formatado adequadamente)
*/
void loadMusics();

/* Guarda a musica s no ficheiro 'filename', com um formato
especifico
*/

void saveMusics();

///Adiciona a musica passada como parametro ao vector Music
void addMusicToDB(Music* music);

///Liberta o espaco alocado para a musica 

void delMusicFromDB(Music* music);

///Funçao com a lista de musicas
void listMusics();

///Funçao que seleccion uma musica da lista de musicas
Music* selMusic();

#endif
