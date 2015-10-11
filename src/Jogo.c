#include "Jogo.h"

void drawGameFrame(char *VIDEO_BASE_ADDRESS, char *codepage) {
	//Area de jogo
	draw_rectangle(0, 0, HRES * 0.8, VRES, 10, COR_DE_TIJOLO, BLACK, VIDEO_BASE_ADDRESS);
	
	//Nome do mapa
	draw_rectangle(HRES * 0.8, 0, HRES, VRES * 0.2, 10, COR_DE_TIJOLO, BLACK, VIDEO_BASE_ADDRESS);
	drawStringAt("Mapa", HRES * 0.85, VRES * 0.05, YELLOW, BLACK, 2, VIDEO_BASE_ADDRESS, codepage);
	
	//Tempo
	draw_rectangle(HRES * 0.8, VRES * 0.2, HRES, VRES * 0.4, 10, COR_DE_TIJOLO, BLACK, VIDEO_BASE_ADDRESS);
	drawStringAt("Tempo", HRES * 0.86, VRES * 0.25, YELLOW, BLACK, 2, VIDEO_BASE_ADDRESS, codepage);
	
	//Pontuação
	draw_rectangle(HRES * 0.8, VRES * 0.4, HRES, VRES * 0.6, 10, COR_DE_TIJOLO, BLACK, VIDEO_BASE_ADDRESS);
	drawStringAt("Pontuacao", HRES * 0.825, VRES * 0.45, YELLOW, BLACK, 2, VIDEO_BASE_ADDRESS, codepage);
	
	//Bolas restantes
	draw_rectangle(HRES * 0.8, VRES * 0.6, HRES, VRES * 0.8, 10, COR_DE_TIJOLO, BLACK, VIDEO_BASE_ADDRESS);
	drawStringAt("Bolas restantes", HRES * 0.82, VRES * 0.65, YELLOW, BLACK, 1, VIDEO_BASE_ADDRESS, codepage);
	
	//Velocidade da bola
	draw_rectangle(HRES * 0.8, VRES * 0.8, HRES, VRES, 10, COR_DE_TIJOLO, BLACK, VIDEO_BASE_ADDRESS);
	drawStringAt("Velocidade da bola", HRES * 0.815, VRES * 0.85, YELLOW, BLACK, 1, VIDEO_BASE_ADDRESS, codepage);
}


void startJogo(int modo_carregamento_mapa) {
	//>>>>>>>>>>  enter graphics mode  <<<<<<<<<
	__dpmi_meminfo map;
	VIDEO_BASE_ADDRESS = enter_graphics(MODE_1024x768, &map);
	clear_screen(0, VIDEO_BASE_ADDRESS);

	
	//>>>>>>>>>>  frame  <<<<<<<<<<
	Sprite *gameframe = create_sprite(GameFrame_xpm);
	draw_sprite(gameframe, VIDEO_BASE_ADDRESS);
	
	//>>>>>>>>>>  nave  <<<<<<<<<<
	init_naves();
	sync_naves_pos();
	//desenha nave
	draw_sprite(nave_parada, VIDEO_BASE_ADDRESS);

	
	//>>>>>>>>>>  blocos  <<<<<<<<<<

	if (modo_carregamento_mapa == 0)
		load_mapa_principal();
	else
		load_mapa_principal_random();

	draw_mapa_principal();
	
	play_array_notes(main_song);
	
	//>>>>>  bola  <<<<<
	Sprite* bola = create_sprite(Bola_xpm);
	bola->x = (nave_pos.x + nave_parada->width / 2);
	bola->y = VRES * 0.82;
	bola->xspeed = 1;
	bola->yspeed = -2;
	draw_sprite(bola, VIDEO_BASE_ADDRESS);
		
	
	drawDate();
	drawTime();
	drawCounter();
	startCounterVsTime();
	int continuar = true;
	
	unsigned char SC;
	do {
		drawTime();
		updateCounterVsTime();
		//updateCounter();
		drawCounter();
		
		mili_sleep(10);
		continuar = move_ball(bola, mapa_principal);
		//move_ball(bola, VIDEO_BASE_ADDRESS);
		
		while (queueEmpty(&keys_queue) == false) {
			SC = queueGet(&keys_queue);
			if (SC == 0xFF) //não há elementos na queue
				continue;
			else { moveNaveKbd(SC); }
		}
			
	} while((SC != SC_ESC) && (continuar == 0));
	
	clear_screen(0, VIDEO_BASE_ADDRESS);

	if (continuar == 1) {
		Sprite *finish = create_sprite_pos(Sucess_xpm, 0, 0);
		draw_sprite(finish, VIDEO_BASE_ADDRESS);

		drawStringAt("Pontuacao", HRES * 0.57, VRES * 0.4, 7, NUMEBR_BACKGROUD_COLOR, 4, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt(pontuation, HRES * 0.69, VRES * 0.5, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);

		int counter_x = HRES * 0.62;
		int counter_y = VRES * 0.83;
		int offset = 60;
		drawStringAt("Tempo", HRES * 0.64, VRES * 0.62, 7, NUMEBR_BACKGROUD_COLOR, 4, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt((int)counter.hour, counter_x, counter_y, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawCharAt(':', counter_x + offset, counter_y, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt((int)counter.min, counter_x + 2 * offset, counter_y, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawCharAt(':', counter_x + 3 * offset, counter_y, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt((int)counter.sec, counter_x + 4 * offset, counter_y, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);

		mili_sleep(10000);

	} else {
		Sprite *game_over = create_sprite_pos(GameOver_xpm, HRES * 0.3, VRES * 0.1);
		draw_sprite(game_over, VIDEO_BASE_ADDRESS);

		drawStringAt("Pontuacao", HRES * 0.37, VRES * 0.4, 7, NUMEBR_BACKGROUD_COLOR, 4, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt(pontuation, HRES * 0.49, VRES * 0.5, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);

		int counter_x = HRES * 0.4;
		int counter_y = VRES * 0.73;
		int offset = 60;
		drawStringAt("Tempo", HRES * 0.44, VRES * 0.62, 7, NUMEBR_BACKGROUD_COLOR, 4, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt((int)counter.hour, counter_x, counter_y, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawCharAt(':', counter_x + offset, counter_y, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt((int)counter.min, counter_x + 2 * offset, counter_y, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawCharAt(':', counter_x + 3 * offset, counter_y, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);
		drawIntAt((int)counter.sec, counter_x + 4 * offset, counter_y, CHAR_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, 3, VIDEO_BASE_ADDRESS, codepage);

		mili_sleep(10000);
	}




	//Libertação da memoria usada pelo programa
	
	//>>>>>>>>>>  blocos  <<<<<<<<<<
	del_mapa_principal();
	
	
	//>>>>>>>>>>  frame  <<<<<<<<<<
	destroy_sprite(gameframe);
	
	
	//>>>>>>>>>>  nave  <<<<<<<<<<
	destroy_naves();
	

	//>>>>>>>>>>  leave graphics mode  <<<<<<<<<
	clear_screen(0, VIDEO_BASE_ADDRESS);
	leave_graphics(map);
	fillScreen(0);
}



void saveJogo() {}
void loadJogo() {}
