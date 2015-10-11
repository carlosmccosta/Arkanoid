/**\file MusicDB.c
 * \brief Base de dados de sons que serão usados durante o jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: MusicDB.c \n
 * DESCRIÇÃO: Base de dados de sons que serão usados durante o jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "MusicDB.h"

Vector* musicasDB;

void init_musicas() {
	musicasDB = newVector(sizeof(Music), 10, 0);
}

void loadMusics() {
/*	FILE* music_db;

	musicasDB = newVector(sizeof(Music));
	music_db_file = fopen(MUSIC_DB_FILENAME, "r");

	if (music_db != NULL) {
		unsigned int num_musicas;
		fscanf(music_db_file, "%u", &num_musicas);

		Music music_temp;
		Note note_temp;
		for (unsigned int i = 0; i < num_musicas; ++i)
	}*/
}

void saveMusics() {
/*	FILE* music_db;

	music_db_file = fopen(MUSIC_DB_FILENAME, "w");

	//Guarda o número de músicas que existe no ficheiro
	fprintf(music_db_file, "%u", (unsigned int)musicasDB.sizeVector);
	for (int i = 0; i < musicasDB.sizeVector; ++i) {
		//Muda de linha
		fputc("\n", music_db_file);
		//Guarda o número de notas que
		fprintf(music_db_file, "%u", elementAtVector(musicasDB, i));

	}*/
}

void addMusicToDB(Music* music){
	push_backVector(musicasDB, music);
}


void delMusicFromDB(Music* music) {
	Music *last = get_back_element(musicasDB);

	//Swap da musica a eliminar pela ultima e "remoção" da ultima
	int i = 0;
	for (; i < sizeof(Music); ++i) {
		*music = *last;
		++music;
		++last;
	}

	pop_backVector(musicasDB);


	deleteVector(music->notes);
	free(music);

}






/*
void listMusics(){

}

Music* selMusic(){

}
*/
