/**\file Altifalante.h
 * \brief Módulo utilizado para reproduzir sons referentes a eventos no jogo e para a música de fundo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Altifalante.h \n
 * DESCRIÇÃO: Módulo utilizado para reproduzir sons referentes a eventos no jogo e para a música de fundo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef ALTIFALANTE_H_
#define ALTIFALANTE_H_

#include <stdio.h>

#include "Timer.h"
#include "Vector.h"

#define PAUSE_BETWEEN_NOTES 10

/** Note definition
 */
typedef struct {
	int freq; 	/**< note frequency */
	int dur;	/**< note duration in miliseconds */
} Note;

/** Music definition
 */
typedef struct {
	int num_notes;	/**< number of notes */
	int pause;	/**< pause between notes (ms) */
	Vector* notes; /**< Vector of notes*/
} Music;

/**Function that turns the speeker on
 */
void speaker_on();

/**Function that turns the speeker off
 */
void speaker_off();

/** Function that plays a single note
 */
void play_note(Note *note);

#endif
