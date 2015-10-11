/**\file GraficaVideo.c
 * \brief Modulo que implementa a placa grafica no modo grafico a ser usada no jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: GraficaVideo.c \n
 * DESCRI��O: Modulo que implementa a placa grafica no modo grafico a ser usada no jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 
#include "GraficaVideo.h"


char codepage[256 * CHR_H];
int HRES = 1024, VRES = 768;
char *VIDEO_BASE_ADDRESS = 0;
unsigned long VIDEO_MEM = 0;

unsigned long get_video_mem_address(int mode)
{
	__dpmi_regs regs;
	unsigned long dosbuf, address = 0;

	dosbuf = __tb & 0xFFFFF; /* dosbuf � a �rea de transfer�ncia */
	dosmemput(&address, 4, dosbuf + 40); /*apaga bytes 40 a 43 dessa �rea*/

	regs.x.ax = 0x4F01; /* VBE get mode info */
	regs.x.di = dosbuf & 0xF; /* LSB da �rea de transfer�ncia */
	regs.x.es = (dosbuf >> 4) & 0xFFFF; /*MSB da �rea de transfer�ncia*/
	regs.x.cx = mode; /*informa��o sobre o modo 105h*/
	__dpmi_int(0x10, &regs); /* DOS int 10h */
	if (regs.h.ah)
		return 1;	/* tratamento de erro, modo n�o suportado */

	dosmemget(dosbuf+40, 4, &address); /* l� o endere�o da mem�ria v�deo */
	if (!address)
	{
		return 1;
	} /* tratamento de erro, modo n�o suportado */

	return address;
}


char * enter_graphics(int mode, __dpmi_meminfo* map) {

	//gera interrupcao de software 0x10 com os registos indicados, activando o modo grafico
	__dpmi_regs regs;
	regs.x.ax = 0x4F02; //AX especifica a rotina de mudanca do modo da placa
	regs.x.bx = 0x4000 + mode; //BX especifica o modo grafico, com o bit 14 a 1
	__dpmi_int(0x10, &regs); //interrupcao - entrar no modo grafico

	VIDEO_MEM = get_video_mem_address(mode); //obter endereco da memoria video

	//inicializar/actualizar variaveis HRES e VRES
	if(mode == MODE_640x480) { HRES = 640; VRES = 480; }
	else if(mode == MODE_800x600) { HRES = 800; VRES = 600; }
	else if(mode == MODE_1024x768) { HRES = 1024; VRES = 768; }
	else if(mode == MODE_1280x1024) { HRES = 1280; VRES = 1024; }

	__djgpp_nearptr_enable(); //permite acesso a memoria fisica usando apontadores
	map->address = VIDEO_MEM; //endereco fisico da memoria video
	map->size = HRES * VRES; //tamanho do bloco de memoria (cada pixel ocupa um byte na memoria)
	__dpmi_physical_address_mapping(map); //mapear bloco de memoria pretendido

	return (char*)(map->address + __djgpp_conventional_base); //retornar endereco generico a usar
}


void leave_graphics(__dpmi_meminfo map) {

	__dpmi_free_physical_address_mapping(&map); //liberta mapeamento
	__djgpp_nearptr_disable(); //desactivar acesso a memoria fisica usando apontadores

	__dpmi_regs regs;
	regs.x.ax = 0x0003;
	__dpmi_int(0x10, &regs); //gera interrupcao software 0x10, entrando no modo texto
}


void set_pixel(int x, int y, int color, char *base) {
	if(x < 0 || x >= HRES || y < 0 || y >= VRES) return;
	if (color != TRANSPARENTE)
		*(base + y*HRES + x) = color;
}


int get_pixel(int x, int y, char *base) {
	if(x < 0 || x >= HRES || y < 0 || y >= VRES) return -1;
	return (int)(*(base + y*HRES + x));
}


void clear_screen(char color, char *base) {
	int x, y;
	for(y = 0; y < VRES; y++)
		for(x = 0; x < HRES; x++)
			set_pixel(x, y, color, base);
}


void draw_line(int xi, int yi, int xf, int yf, int color, char *base) {
	//obter o comprimento da linha em x
	int x_size = xf - xi;
	if(x_size < 0) x_size = -x_size;

	//obter o comprimento da linha em y
	int y_size = yf - yi;
	if(y_size < 0) y_size = -y_size;

	int i;
	if(x_size > y_size) //dimensao maior e a horizontal
	{
		if(xf - xi < 0) //orientar a recta no sentido positivo de x
		{
			int aux = xi;
			xi = xf;
			xf = aux;
			aux = yi;
			yi = yf;
			yf = aux;
		}

		for(i = 0; i <= x_size; i++)
		{
			//regra de 3 simples; se x_size esta para y_size, entao i esta para y_point
			double y_point = (double)y_size * (double)i / (double)x_size;

			//desenhar pixel
			if(yf - yi < 0) set_pixel(xi + i, yi - (int)(y_point + 0.5), color, base);
			else set_pixel(xi + i, yi + (int)(y_point + 0.5), color, base);
		}
	}

	else //dimensao maior e a vertical
	{
		if(yf - yi < 0) //orientar a recta no sentido positivo de y
		{
			int aux = xi;
			xi = xf;
			xf = aux;
			aux = yi;
			yi = yf;
			yf = aux;
		}

		for(i = 0; i <= y_size; i++)
		{
			//regra de 3 simples; se y_size esta para x_size, entao i esta para x_point
			double x_point = (double)x_size * (double)i / (double)y_size;

			//desenhar pixel
			if(xf - xi < 0) set_pixel(xi - (int)(x_point + 0.5), yi + i, color, base);
			else set_pixel(xi + (int)(x_point + 0.5), yi + i, color, base);
		}
	}
}


void drawCharAt(char c, int x, int y, int fore_color, int back_color,
		int char_scale, char *video_base, char *table) {
	// posi��o do car�cter "c" em "table" (lida de po.dat)
	char* char_def = table + c * CHR_H;

	int i, j;
	Byte mask = 0x80;
	int color;
	int x_act, y_act, sx, sy;
	// usar operadores bitwise para isolar e testar cada um dos bits
	for (j = 0, y_act = y; j < CHR_H; j++, y_act += char_scale) // for each character row
	{
		for (i = 0, x_act = x; i < 8; i++, x_act += char_scale)		// for each pixel in row
		{
			color = (*char_def & (mask >> i)) ? fore_color : back_color;
			if (color == TRANSPARENTE) continue;
			for(sx = 0; sx < char_scale; sx++)
				for(sy = 0; sy < char_scale; sy++)
					set_pixel(x_act + sx, y_act + sy, color, video_base);
		}
		char_def++;
	}
}


void drawCharCenteredAt(char c, int x, int y, int fore_color, int back_color,
		int char_scale, char* video_base, char* table) {
	x -= 4*char_scale;
	y -= CHR_H/2*char_scale;
	drawCharAt(c, x, y, fore_color, back_color, char_scale, video_base, table);
}


void drawStringAt(char* str, int x, int y, int fore_color, int back_color,
		int char_scale, char *video_base, char *table) {
	int i = 0;
	while(str[i] != 0)
	{
		drawCharAt(str[i], x + 8 * char_scale * i, y, fore_color, back_color, char_scale, video_base, table);
		i++;
	}
}


void drawIntAt(int num, int x, int y, int fore_color, int back_color,
		int char_scale, char *video_base, char *table) {

	int i = 0;

	//se o numero for negativo, imprimir '-'
	if(num < 0)
	{
		drawCharAt('-', x, y, fore_color, back_color, char_scale, video_base, table);
		i++;
		num = 0 - num;
	}

	//descobrir a ordem de grandeza do numero
	int ordem = 1;
	while(num / ordem >= 10) ordem *= 10;

	//da esquerda para a direita, imprimir os algarismos
	while(true)
	{
		int digito = num / ordem;
		drawCharAt(digito + '0', x + 8 * char_scale * i, y, fore_color, back_color, char_scale, video_base, table);
		num -= digito * ordem;
		if(ordem == 1) break;
		ordem /= 10;
		i++;
	}
}


void draw_rectangle(int xi, int yi, int xf, int yf, int espessura, int line_color, int
		back_color, char *base) {
	int i, j;
	for (i = 0; i < espessura; i++)
	{
		draw_line(xi,yi+i, xf, yi+i, line_color, base); //horizontal superior
		draw_line(xi,yf-i, xf, yf-i, line_color, base); //horizontal inferior
		draw_line(xi+i,yi, xi+i, yf, line_color, base); //vertical esquerda
		draw_line(xf-i,yi, xf-i, yf, line_color, base); //vertical direita
	}

	int x_fin = xf-espessura;
	int y_fin = yf-espessura;

	if(back_color != TRANSPARENTE)
	{
		for (i=yi+espessura; i <= y_fin; i++)
			for (j=xi+espessura; j <= x_fin; j++)
				set_pixel(j, i, back_color, base);
	}
}
