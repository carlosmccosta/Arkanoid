/**\file Nave.c
 * \brief Módulo com as subrotinas necessárias para o uso da nave do jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Naves.c \n
 * DESCRIÇÃO: Módulo com as subrotinas necessárias para o uso da nave do jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#include "Nave.h"

volatile NavePos nave_pos = { (NAVE_MAX_X) * 0.4, (NAVE_MAX_Y) * 0.8 };
 
Sprite *nave_parada;
Sprite *nave_esquerda;
Sprite *nave_direita;


void init_naves() {
	_go32_dpmi_lock_data((void *)&nave_pos, sizeof(NavePos));
	nave_pos.x = (HRES) * 0.3;
	nave_pos.y = (VRES) * 0.86;
	nave_parada = create_sprite(NaveParada_xpm);
	nave_esquerda = create_sprite(NaveEsquerda_xpm);
	nave_direita = create_sprite(NaveDireita_xpm);
}

void del_naves_screen() {
	if (nave_parada->on_screen == true)
		delete_sprite(nave_parada, VIDEO_BASE_ADDRESS);
		
	if (nave_esquerda->on_screen == true)
		delete_sprite(nave_esquerda, VIDEO_BASE_ADDRESS);
	
	if (nave_direita->on_screen == true)
		delete_sprite(nave_direita, VIDEO_BASE_ADDRESS);
}

void destroy_naves() {
	destroy_sprite(nave_parada);
	destroy_sprite(nave_esquerda);
	destroy_sprite(nave_direita);
}

void sync_naves_pos() {
	nave_parada->x = nave_pos.x;
	nave_parada->y = nave_pos.y;

	nave_esquerda->x = nave_pos.x;
	nave_esquerda->y = nave_pos.y;

	nave_direita->x = nave_pos.x;
	nave_direita->y = nave_pos.y;
}

void moveNaveMouse(int dx, int dy) {
	if (mouse_state.mouse_move == false)
		return;

	int new_x = nave_pos.x + dx;
	int new_y = nave_pos.y + dy;

	if ((new_x > (NAVE_MIN_X)) && (new_x < (NAVE_MAX_X)) && (new_y > (NAVE_MIN_Y)) && (new_y < (NAVE_MAX_Y))) {
		nave_pos.x = new_x;
		nave_pos.y = new_y;
	} else
		return;

	//del_naves_screen();
	//sync_naves_pos();
/*
	if (dx > 0)
		draw_sprite(nave_direita, VIDEO_BASE_ADDRESS);
	else if (dx < 0)
		draw_sprite(nave_esquerda, VIDEO_BASE_ADDRESS);
	else
		draw_sprite(nave_parada, VIDEO_BASE_ADDRESS);
*/

	nave_parada->x = new_x;
	nave_parada->y = new_y;
	move_sprite(nave_parada, new_x, new_y, VIDEO_BASE_ADDRESS);
}


char direction = 'U';

void moveNaveKbd(unsigned char SC) {
	if ((SC == SC_LEFT) && ((nave_pos.x - MOVEMENTS_OFFSET_NAVE) < (NAVE_MAX_X)) && ((nave_pos.x - MOVEMENTS_OFFSET_NAVE) > (NAVE_MIN_X))) {
		nave_pos.x -= MOVEMENTS_OFFSET_NAVE;
		if (direction != 'L') {
			del_naves_screen();
			sync_naves_pos();
			direction = 'L';
			draw_sprite(nave_esquerda, VIDEO_BASE_ADDRESS);
		} else
			move_sprite(nave_esquerda, nave_esquerda->x - MOVEMENTS_OFFSET_NAVE, nave_esquerda->y, VIDEO_BASE_ADDRESS);
	
	} else
	
	if ((SC == SC_RIGHT) && ((nave_pos.x + MOVEMENTS_OFFSET_NAVE) < (NAVE_MAX_X)) && ((nave_pos.x + MOVEMENTS_OFFSET_NAVE) > (NAVE_MIN_X))) {
		nave_pos.x += MOVEMENTS_OFFSET_NAVE;
		if (direction != 'R') {
			del_naves_screen();
			sync_naves_pos();
			direction = 'R';
			draw_sprite(nave_direita, VIDEO_BASE_ADDRESS);
		} else
			move_sprite(nave_direita, nave_direita->x + MOVEMENTS_OFFSET_NAVE, nave_direita->y, VIDEO_BASE_ADDRESS);

	} else
	
	if ((SC == SC_UP) && (nave_pos.y - MOVEMENTS_OFFSET_NAVE < (NAVE_MAX_Y)) && (nave_pos.y - MOVEMENTS_OFFSET_NAVE > (NAVE_MIN_Y))) {
		nave_pos.y -= MOVEMENTS_OFFSET_NAVE;
		if (direction != 'U') {
			del_naves_screen();
			sync_naves_pos();
			direction = 'U';
			draw_sprite(nave_parada, VIDEO_BASE_ADDRESS);
		} else
			move_sprite(nave_parada, nave_parada->x, nave_parada->y - MOVEMENTS_OFFSET_NAVE, VIDEO_BASE_ADDRESS);
		
	} else
	
	if ((SC == SC_DOWN) && (nave_pos.y + MOVEMENTS_OFFSET_NAVE < (NAVE_MAX_Y)) && (nave_pos.y + MOVEMENTS_OFFSET_NAVE > (NAVE_MIN_Y))) {
		if (direction != 'D') {
			nave_pos.y += MOVEMENTS_OFFSET_NAVE;
			del_naves_screen();
			sync_naves_pos();
			direction = 'D';
			draw_sprite(nave_parada, VIDEO_BASE_ADDRESS);
		} else
			move_sprite(nave_parada, nave_parada->x, nave_parada->y + MOVEMENTS_OFFSET_NAVE, VIDEO_BASE_ADDRESS);
	}
	else {
		if (direction != 'U') {
			del_naves_screen();
			sync_naves_pos();
			direction = 'U';
			draw_sprite(nave_parada, VIDEO_BASE_ADDRESS);
		}
		
	}
}
