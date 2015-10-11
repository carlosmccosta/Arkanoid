#include "MapasDB.h"

Vector *mapa_principal;


void load_mapa_principal() {
	mapa_principal = newVector(sizeof(Bloco), 80, NULL);

	int x = 100;
	int y = 100;
	int i = 0;
	int j = 0;

	for (; i < 5; ++i) {
		for (; j < 15; ++j) {
			Bloco *block;

			if (i == 0)
				block = createBloco(barra_xpm, x, y, (int)5);

			if (i == 1)
				block = createBloco(barra1_xpm, x, y, (int)4);

			if (i == 2)
				block = createBloco(barra2_xpm, x, y, (int)3);

			if (i == 3)
				block = createBloco(barra3_xpm, x, y, (int)2);

			if (i == 4)
				block = createBloco(barra4_xpm, x, y, (int)1);

			push_backVector(mapa_principal, (void*)block);
			free((void*)block);

			x += 40;
		}

		j = 0;
		x = 100;
		y += 50;
	}

	//adição da nave para aproveitar os algoritmos de colisão com os blocos
	Bloco *block = createBloco(NaveParada_xpm, nave_pos.x, nave_pos.y, (int)0);
	block->nave = true;
	block->sprite->on_screen = true;
	push_backVector(mapa_principal, (void*)block);
	free((void*)block);

}


void load_mapa_principal_random() {
	RTC_TIME time_from_rtc;
	rtc_read_time(&time_from_rtc);

	mapa_principal = newVector(sizeof(Bloco), 80, NULL);
	
	int x = 100;
	int y = 100;
	int i = 0;
	int j = 0;
	
	//srand(time(NULL));
	int sec_rtc_rand = time_from_rtc.sec % 2;

	Bloco *block;

	for (; i < 15; ++i) {
		for (; j < 6; ++j) {
			//rand_number = rand() % 2;
			sec_rtc_rand = time_from_rtc.sec % 2;

			if ((i == 0) && (((mil_tick + sec_rtc_rand) % 2) == 1)) {
				block = createBloco(barra_xpm, x, y, (int)5);
				push_backVector(mapa_principal, (void*)block);
				free((void*)block);

				/*if ((i * (mil_tick * sec_rtc_rand)) % 3 == 1)
					mili_sleep(7);*/
			} else
			
			if ((i == 1) && (((mil_tick + sec_rtc_rand) % 2) == 1)) {
				block = createBloco(barra1_xpm, x, y, (int)4);
				push_backVector(mapa_principal, (void*)block);
				free((void*)block);

				/*if ((j + (mil_tick - sec_rtc_rand)) % 2 == 1)
					mili_sleep(3);*/
			} else

			if ((i == 2) && ((((mil_tick + sec_rtc_rand) + sec_rtc_rand) % 2) == 1)) {
				block = createBloco(barra2_xpm, x, y, (int)3);
				push_backVector(mapa_principal, (void*)block);
				free((void*)block);

				/*if ((i * j - (mil_tick + sec_rtc_rand)) % 2 == 1)
					mili_sleep(5);*/
			} else
				
			if ((i == 3) && (((mil_tick * sec_rtc_rand) % 2) == 1)) {
				block = createBloco(barra3_xpm, x, y, (int)2);
				push_backVector(mapa_principal, (void*)block);
				free((void*)block);

				/*if ((i * j * (mil_tick + sec_rtc_rand)) % 2 == 1)
					mili_sleep(9);*/
			} else
				
			if ((i == 4) && (((mil_tick + sec_rtc_rand) % 2) == 1)) {
				block = createBloco(barra4_xpm, x, y, (int)1);
				push_backVector(mapa_principal, (void*)block);
				free((void*)block);

				/*if ((i * j * (mil_tick - sec_rtc_rand)) % 2 == 1)
					mili_sleep(1);*/
			}
				
			
			y += 50;
		}
	
		j = 0;
		x += 40;
		y = 100;
	}
	
	//adição da nave para aproveitar os algoritmos de colisão com os blocos
	Bloco *block_nave = createBloco(NaveParada_xpm, nave_pos.x, nave_pos.y, (int)0);
	block_nave->nave = true;
	block_nave->sprite->on_screen = true;
	push_backVector(mapa_principal, (void*)block_nave);
	free((void*)block_nave);


	if (sizeVector(mapa_principal) < 10) {
		clearVector(mapa_principal);
		load_mapa_principal_random();
	}

}

void draw_mapa_principal() {
	unsigned int i = 0;
	unsigned int size = sizeVector(mapa_principal);
	
	for (; i < size; ++i) {
	Bloco* block = (Bloco*)elementAtVector(mapa_principal, i);
		draw_sprite(block->sprite, VIDEO_BASE_ADDRESS);
	}
}


void del_mapa_principal() {
	unsigned int i = 0;
	unsigned int size = sizeVector(mapa_principal);
	
	for (; i < size; ++i) {
		Bloco* block = (Bloco*)elementAtVector(mapa_principal, i);
		destroy_sprite(block->sprite);
	}

	deleteVector(mapa_principal);
}

/*
void loadMapa(Mapa *mapa){

}

void saveMapa(Mapa *mapa){

}

void addMapa(Mapa *mapa){

}

void delMapa(Mapa *mapa){

}
*/
