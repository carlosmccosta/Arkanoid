/**\file Music.c
 * \brief M�dulo com a estrutura de uma m�sica
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Music.c \n
 * DESCRI��O: M�dulo com a estrutura de uma m�sica \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Music.h"


Music* createMusic(int num_notes, int pause, Vector *notes) {
	Music* music = (Music*) malloc(sizeof(Music));
	music->num_notes = num_notes;
	music->pause = pause;
	music->notes = notes;

	return music;
}

void delMusic(Music *music) {
	deleteVector(music->notes);
	free(music);
}

Music* addNote(Music* music, Note *note) {
	push_backVector(music->notes, (void*) note);
	return music;
}


void play_music(Music *music) {
	unsigned int i = 0;
	for(; i < music->notes->count; i++) {
		Note *note = (Note*) elementAtVector(music->notes, i);
		play_note(note);
		mili_sleep(music->pause);
	}
}

void play_array_notes(Note notes[]) {
	if (notes == NULL)
	return;
	
	while(notes->freq != 0) {
		play_note(notes);
		mili_sleep(50);
		++notes;
	}
}

void play_array_notes_enum(Note notes[]) {
	if (notes == NULL)
	return;

	while(notes->freq != 0) {
		play_note(notes);
		mili_sleep(50);
		notes += sizeof(Note);
	}
}


float notes_frequency[] = { 16.35, 17.32, 18.35, 19.45, 20.6, 21.83, 23.12, 24.5, 25.96, 27.5, 29.14, 30.87,
	32.7, 34.65, 36.71, 38.89, 41.2, 43.65, 46.25, 49, 51.91, 55, 58.27, 61.74,
	65.41, 69.3, 73.42, 77.78, 82.41, 87.31, 92.5, 98, 103.83, 110, 116.54, 123.47,
	130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185, 196, 207.65, 220, 233.08, 246.94,
	261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466.16, 493.88,
	523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880, 932.33, 987.77,
	1046.5, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760, 1864.66, 1975.53,
	2093, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520, 3729.31, 3951.07,
	4186.01, 4434.92, 4698.64, 4978.03};
