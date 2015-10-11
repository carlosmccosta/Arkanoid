/**\file Bola.c
 * \brief Módulo com as subrotinas necessárias para o uso da Bola do jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Bola.c \n
 * DESCRIÇÃO: Módulo com as subrotinas necessárias para o uso da Bola do jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#include "Bola.h"

int pontuation = 0;
int lives = 5;
int speed = 0;
unsigned int blocos_destruidos = 0;

Note wall_hit = { 450, 20 };
Note nave_hit = { 650, 20 };
Note block_hit = { 850, 20 };
Note ground_hit = { 250, 500 };

int move_ball(Sprite *bola, Vector *vec_blocos) {

	//>>>>>>>>>>>>>>>>>>>>>>  actualiza o bloco que simula a nave como um bloco para as colisões
	Bloco *nave_block = (Bloco*)get_back_element(vec_blocos);
	nave_block->sprite->x = nave_pos.x;
	nave_block->sprite->y = nave_pos.y;
	
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   infos
	speed = sqrt(bola->xspeed * bola->xspeed + bola->yspeed * bola->yspeed);
	drawIntAt(pontuation, SCORE_X_POS, SCORE_Y_POS, NUMBER_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt(speed , SPEED_X_POS, SPEED_Y_POS, NUMBER_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt(lives, LIFES_X_POS, LIFES_Y_POS, NUMBER_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   colisão com as paredes

	Bool first_hit = true;
	//lado direito
	while ((bola->x + bola->width + COLLISION_DETECTION_OFFSET) > MAX_GAME_WINDOWS_X) {
		int new_xspeed = -abs(bola->xspeed);
		bola->xspeed = new_xspeed;
		animate_sprite(bola, VIDEO_BASE_ADDRESS);

		if (first_hit == true)
			play_note(&wall_hit);

		//mili_sleep(5000);
	}

	first_hit = true;
	//lado esquerdo
	while ((bola->x - COLLISION_DETECTION_OFFSET) < MIN_GAME_WINDOWS_X) {
		int new_xspeed = abs(bola->xspeed);
		bola->xspeed = new_xspeed;
		animate_sprite(bola, VIDEO_BASE_ADDRESS);

		if (first_hit == true)
			play_note(&wall_hit);

		//mili_sleep(5000);
		first_hit = false;
	}
	
	first_hit = true;
	//baixo
	while ((bola->y + bola->height + COLLISION_DETECTION_OFFSET) > MAX_GAME_WINDOWS_Y) {
		int new_yspeed = -abs(bola->yspeed);
		bola->yspeed = new_yspeed;

		animate_sprite(bola, VIDEO_BASE_ADDRESS);

		if (first_hit == true)
			play_note(&ground_hit);

		--lives;
		mili_sleep(10);

		delete_sprite(bola, VIDEO_BASE_ADDRESS);
		bola->x = (nave_pos.x + nave_parada->width / 2);
		bola->y = VRES * 0.82;
		bola->xspeed = 1;
		bola->yspeed = -2;

		first_hit = false;
	}

	first_hit = true;
	//cima
	while ((bola->y - COLLISION_DETECTION_OFFSET) < MIN_GAME_WINDOWS_Y) {
		int new_yspeed = abs(bola->yspeed);
		bola->yspeed = new_yspeed;
		animate_sprite(bola, VIDEO_BASE_ADDRESS);

		if (first_hit == true)
			play_note(&wall_hit);

		//mili_sleep(5000);
		first_hit = false;
	}
	
	

	
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   Tipos de movimentos da bola para saber como calcular a colisao com os blocos
	unsigned int collision_type;
	if ((bola->xspeed >= 0) && (bola->yspeed <= 0))
		collision_type = 0;

	if ((bola->xspeed <= 0) && (bola->yspeed < 0))
		collision_type = 1;
		
	if ((bola->xspeed < 0) && (bola->yspeed >= 0))
		collision_type = 2;
		
	if ((bola->xspeed > 0) && (bola->yspeed > 0))
		collision_type = 3;

	
	
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   Calcula se ocorre colisão
	unsigned int size_vec_blocos = sizeVector(vec_blocos);
	unsigned int i;
	
	
	switch(collision_type) {
		case 0: { // bola a mover-se para NE (nordeste)
			for (i = 0; i < size_vec_blocos; ++i) {
				Bloco* block = (Bloco*)elementAtVector(vec_blocos, i);
				//verifica se houve colisão (+-COLLISION_DETECTION_OFFSET para evitar sobreposição da bola com os blocos)
				if( (block->sprite->on_screen == true) &&
					(abs(bola->x + bola->width) > (block->sprite->x - COLLISION_DETECTION_OFFSET)) &&
					(abs(bola->x) < (block->sprite->x + block->sprite->width)) &&
					(((bola->y + bola->height) > block->sprite->y)) &&
					((bola->y < (block->sprite->y + block->sprite->height + COLLISION_DETECTION_OFFSET))) )
				{
					//determina o lado em que bateu a bola
					int dx = abs(bola->x + bola->width - block->sprite->x);
					int dy = abs(bola->y - (block->sprite->y + block->sprite->height));
					
					
					//actualiza a velocidade da bola
					//Caso embata na nave considera apenas a parte da xpm que tem a nave
					if (block->nave == true) {
						if ((block->sprite->x < (block->sprite->width - NAVE_LEFT_OFFSET_IN_XPM - NAVE_RIGHT_OFFSET_IN_XPM)) //caso em que a nave esta do lado esquerdo
								|| ((dx > NAVE_LEFT_OFFSET_IN_XPM) && (abs(block->sprite->x + block->sprite->width - bola->x) > NAVE_RIGHT_OFFSET_IN_XPM))) {
							if (dx > dy) { //bateu da parte de baixo do bloco
								int new_yspeed = -bola->yspeed;
								bola->yspeed = new_yspeed;
							} else { //bateu do lado esquerdo do bloco
								int new_xspeed = -bola->xspeed;
								bola->xspeed = new_xspeed;
							}
							play_note(&nave_hit);
						}

					} else {
						if (dx > dy) { //bateu da parte de baixo do bloco
							int new_yspeed = -bola->yspeed;
							bola->yspeed = new_yspeed;
						} else { //bateu do lado esquerdo do bloco
							int new_xspeed = -bola->xspeed;
							bola->xspeed = new_xspeed;
						}
						play_note(&block_hit);
					}

					animate_sprite(bola, VIDEO_BASE_ADDRESS);
					
					//apaga bloco se não for a nave
					if (block->nave == false) {
						//mili_sleep(5000);
						block->sprite->on_screen = false;
						delete_sprite(block->sprite, VIDEO_BASE_ADDRESS);
						
						//acrescenta à pontuação o valor do bloco
						pontuation += block->pontuation;
						//actualiza o numeros de blocos que já foram destruidos
						++blocos_destruidos;
					}
					
					return 0;
				}
			}
			break;
		}

		case 1: { // bola a mover-se para NO (noroeste)
			for (i = 0; i < size_vec_blocos; ++i) {
				Bloco* block = (Bloco*)elementAtVector(vec_blocos, i);
				//verifica se houve colisão (+-COLLISION_DETECTION_OFFSET para evitar sobreposição da bola com os blocos)
				if( (block->sprite->on_screen == true) &&
					(abs(bola->x + bola->width) > block->sprite->x) &&
					(abs(bola->x) < (block->sprite->x + block->sprite->width + COLLISION_DETECTION_OFFSET)) &&
					((bola->y + bola->height) > block->sprite->y) &&
					((bola->y < (block->sprite->y + block->sprite->height + COLLISION_DETECTION_OFFSET))) )
				{
					//determina o lado em que bateu a bola
					int dx = abs(block->sprite->x + block->sprite->width - bola->x);
					int dy = abs(block->sprite->y + block->sprite->height - bola->y);


					//actualiza a velocidade da bola
					//Caso embata na nave considera apenas a parte da xpm que tem a nave
					if (block->nave == true) {
						if ((block->sprite->x < (block->sprite->width - NAVE_LEFT_OFFSET_IN_XPM - NAVE_RIGHT_OFFSET_IN_XPM)) //caso em que a nave esta do lado esquerdo
								|| ((dx > NAVE_RIGHT_OFFSET_IN_XPM) && (abs(bola->x + bola->width - block->sprite->x) > NAVE_LEFT_OFFSET_IN_XPM))) {
							if (dx > dy) { //bateu da parte de baixo do bloco
								int new_yspeed = -bola->yspeed;
								bola->yspeed = new_yspeed;
							} else { //bateu do lado direito do bloco
								int new_xspeed = -bola->xspeed;
								bola->xspeed = new_xspeed;
							}
							play_note(&nave_hit);
						}

					} else {
						if (dx > dy) { //bateu da parte de baixo do bloco
							int new_yspeed = -bola->yspeed;
							bola->yspeed = new_yspeed;
						} else { //bateu do lado direito do bloco
							int new_xspeed = -bola->xspeed;
							bola->xspeed = new_xspeed;
						}
						play_note(&block_hit);
					}


					animate_sprite(bola, VIDEO_BASE_ADDRESS);
					
					//apaga bloco se não for a nave
					if (block->nave == false) {
						//mili_sleep(5000);
						block->sprite->on_screen = false;
						delete_sprite(block->sprite, VIDEO_BASE_ADDRESS);

						//acrescenta à pontuação o valor do bloco
						pontuation += block->pontuation;
						//actualiza o numeros de blocos que já foram destruidos
						++blocos_destruidos;
					}

					return 0;
				}
			}
			break;
		}

		case 2: { // bola a mover-se para SO (sudueste)
			for (i = 0; i < size_vec_blocos; ++i) {
				Bloco* block = (Bloco*)elementAtVector(vec_blocos, i);
				//verifica se houve colisão (+-COLLISION_DETECTION_OFFSET para evitar sobreposição da bola com os blocos)
				if( (block->sprite->on_screen == true) &&
					(abs(bola->x + bola->width) > block->sprite->x) &&
					(abs(bola->x) < (block->sprite->x + block->sprite->width + COLLISION_DETECTION_OFFSET)) &&
					((bola->y + bola->height) > (block->sprite->y - COLLISION_DETECTION_OFFSET)) &&
					(bola->y < (block->sprite->y + block->sprite->height)) )
				{
					//determina o lado em que bateu a bola
					int dx = abs(block->sprite->x + block->sprite->width - bola->x);
					int dy = abs(bola->y + bola->height - block->sprite->y);


					//actualiza a velocidade da bola
					//Caso embata na nave considera apenas a parte da xpm que tem a nave
					if (block->nave == true) {
						if ((block->sprite->x < (block->sprite->width - NAVE_LEFT_OFFSET_IN_XPM - NAVE_RIGHT_OFFSET_IN_XPM)) //caso em que a nave esta do lado esquerdo
								|| ((dx > NAVE_RIGHT_OFFSET_IN_XPM) && (abs(bola->x + bola->width - block->sprite->x)) > NAVE_LEFT_OFFSET_IN_XPM)) {
							if (dx > dy) { //bateu da parte de cima do bloco
								int new_yspeed = -bola->yspeed;
								bola->yspeed = new_yspeed;
							} else { //bateu do lado direito do bloco
								int new_xspeed = -bola->xspeed;
								bola->xspeed = new_xspeed;
							}
							play_note(&nave_hit);
						}

					} else {
						if (dx > dy) { //bateu da parte de cima do bloco
							int new_yspeed = -bola->yspeed;
							bola->yspeed = new_yspeed;
						} else { //bateu do lado direito do bloco
							int new_xspeed = -bola->xspeed;
							bola->xspeed = new_xspeed;
						}
						play_note(&block_hit);
					}


					animate_sprite(bola, VIDEO_BASE_ADDRESS);
					
					//apaga bloco se não for a nave
					if (block->nave == false) {
						//mili_sleep(5000);
						block->sprite->on_screen = false;
						delete_sprite(block->sprite, VIDEO_BASE_ADDRESS);

						//acrescenta à pontuação o valor do bloco
						pontuation += block->pontuation;
						//actualiza o numeros de blocos que já foram destruidos
						++blocos_destruidos;
					}

					return 0;
				}
			}
			break;
		}

		case 3: { // bola a mover-se para SE (sodeste)
			for (i = 0; i < size_vec_blocos; ++i) {
				Bloco* block = (Bloco*)elementAtVector(vec_blocos, i);
				//verifica se houve colisão (+-COLLISION_DETECTION_OFFSET para evitar sobreposição da bola com os blocos)
				if( (block->sprite->on_screen == true) &&
					(abs(bola->x + bola->width) > (block->sprite->x - COLLISION_DETECTION_OFFSET)) &&
					(abs(bola->x) < (block->sprite->x + block->sprite->width)) &&
					((bola->y + bola->height) > (block->sprite->y - COLLISION_DETECTION_OFFSET)) &&
					(bola->y < (block->sprite->y + block->sprite->height)) )
				{
					//determina o lado em que bateu a bola
					int dx = abs(bola->x + bola->width - block->sprite->x);
					int dy = abs(bola->y + bola->height - block->sprite->y);


					//actualiza a velocidade da bola
					if (block->nave == true) {
						if ((block->sprite->x < (block->sprite->width - NAVE_LEFT_OFFSET_IN_XPM - NAVE_RIGHT_OFFSET_IN_XPM)) //caso em que a nave esta do lado esquerdo
								|| ((dx > NAVE_LEFT_OFFSET_IN_XPM) && (abs(block->sprite->x + block->sprite->width - bola->x)) > NAVE_RIGHT_OFFSET_IN_XPM)) {
							if (dx > dy) { //bateu da parte de cima do bloco
								int new_yspeed = -bola->yspeed;
								bola->yspeed = new_yspeed;
							} else { //bateu do lado esquerdo do bloco
								int new_xspeed = -bola->xspeed;
								bola->xspeed = new_xspeed;
							}
							play_note(&nave_hit);
						}

					} else {
						if (dx > dy) { //bateu da parte de cima do bloco
							int new_yspeed = -bola->yspeed;
							bola->yspeed = new_yspeed;
						} else { //bateu do lado esquerdo do bloco
							int new_xspeed = -bola->xspeed;
							bola->xspeed = new_xspeed;
						}
						play_note(&block_hit);
					}


					animate_sprite(bola, VIDEO_BASE_ADDRESS);
					
					//apaga bloco se não for a nave
					if (block->nave == false) {
						//mili_sleep(5000);
						block->sprite->on_screen = false;
						delete_sprite(block->sprite, VIDEO_BASE_ADDRESS);

						//acrescenta à pontuação o valor do bloco
						pontuation += block->pontuation;
						//actualiza o numeros de blocos que já foram destruidos
						++blocos_destruidos;
					}

					return 0;
				}
			}
			break;
		}
	}
	
	
	
	animate_sprite(bola, VIDEO_BASE_ADDRESS);
	
	if (blocos_destruidos == (sizeVector(vec_blocos) - 1))
		return 1;
	else if (lives < 0)
		return 2;
	else
		return 0;
}

