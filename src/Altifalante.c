/**\file Altifalante.c
 * \brief Módulo utilizado para reproduzir sons referentes a eventos no jogo e para a música de fundo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Altifalante.c \n
 * DESCRIÇÃO: Módulo utilizado para reproduzir sons referentes a eventos no jogo e para a música de fundo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Altifalante.h"


void speaker_on() {
	char val = inportb(SPEAKER_CTRL);
	outportb(SPEAKER_CTRL, val | SPEAKER_ENABLE | TIMER2_ENABLE);
}

void speaker_off() {
	char val = inportb(SPEAKER_CTRL);
	outportb(SPEAKER_CTRL, val & ~SPEAKER_ENABLE & ~TIMER2_ENABLE);
}

void play_note(Note *nota) {
	timer_load(TIMER_2, TIMER_CLK / nota->freq);
	speaker_on();
	mili_sleep(nota->dur);
	speaker_off();
}
