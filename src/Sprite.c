/**\file Sprite.c
 * \brief Módulo que contem toda a implementaçao para tratamento de imagens
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Sprite.c \n
 * DESCRIÇÃO: Módulo que contem toda a implementaçao para tratamento de imagens \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Sprite.h"

extern int HRES, VRES;
static char *video_buffer = NULL;

char *read_xpm_gimp (char *map[], unsigned int *wd, unsigned int *ht)
{
	int width, height, colors, nbyte;
	unsigned char sym[256 * 256];
	int i, j;
	char *pix;
	char *line;

	// read width, height, colors
	if (sscanf(map[0],"%d %d %d %d", &width, &height, &colors, &nbyte) != 4) {
		printf("read_xpm: incorrect width, height, colors, nbyte\n");
		return NULL;
	}

#ifdef DEBUG
  	printf("%d %d %d %d\n", width, height, colors, nbyte);
#endif
	*wd = width;
	*ht = height;

	if (nbyte != 2) {
		printf("read_xpm2: incorrect number of bytes\n");
		return NULL;
	}

	for (i=0; i<256*256 ; i++)
		sym[i] = 0;
	// read symbols <-> colors
	for (i=0; i<colors; i++) {
		sym[map[i+1][0] * 256 + map[i+1][1]] = i;
	}

	// allocate pixmap memory
	pix = (char*) malloc(width*height);

	// parse each pixmap symbol line
	for (i=0; i<height; i++) {
		line = map[colors+1+i];
#ifdef DEBUG
		printf("\nparsing %s\n", line);
#endif
		for (j = 0; j < width; j++) {
			pix[i * width +j] = sym[ line[2*j] * 256 + line[2*j + 1]];
		}
	}
	return pix;
}


Sprite* create_sprite(char *pic[])
{
	Sprite* sprt = create_unbuffered_sprite(pic);
	if(!sprt) return NULL;
	sprt->bgmap = (char*) malloc(sprt->width * sprt->height);
	return sprt;
}

Sprite* create_unbuffered_sprite(char *pic[])
{
	Sprite* sprt = (Sprite*) malloc(sizeof(Sprite));
	if(!sprt) return NULL;

	unsigned int wd, ht;
	sprt->map = read_xpm_gimp(pic, &wd, &ht);
	if(!sprt->map) { free(sprt); return NULL; }

	sprt->x = sprt->y = sprt->xspeed = sprt->yspeed = 0;
	sprt->width = wd; sprt->height = ht;
	sprt->bgmap = NULL;
	sprt->on_screen = false;
	return sprt;
}

Sprite* create_sprite_pos(char *pic[], int x, int y) {
	Sprite *sprite = create_sprite(pic);
	sprite->x = x;
	sprite->y = y;
	
	return sprite;
}

void draw_sprite(Sprite* sprt, char *base)
{
	char* dSprt = sprt->map;
	char* bgMap = sprt->bgmap;
	sprt->on_screen = true;
	
	int i,k;
	for(i=0; i < sprt->height; i++)
		for(k=0; k < sprt->width; k++)
		{
			if(bgMap) *(bgMap + sprt->width*i + k) = get_pixel(sprt->x+k, sprt->y+i, base); //guarda o valor antigo
			if(*dSprt != 0) set_pixel(sprt->x+k,sprt->y+i, *dSprt, base);  //actualiza com o valor actual
			dSprt++;
		}
}



//desenha uma sprite com um determinado angulo (0, 90, 180 e 270)
void draw_sprite_rotated(Sprite *sprt, char *base, int angle)
{
	char* dSprt = sprt->map;
	char* bgMap = sprt->bgmap;
	sprt->on_screen = true;
	
	while(angle < 0) angle += 360;
	while(angle >= 360) angle -= 360;

	int i, k;
	if(bgMap)
	{
		//guarda uma copia do background onde vai ser desenhada a sprite
		for(i=0; i < sprt->height; i++)
			for(k=0; k < sprt->width; k++)
				if (angle==0 || angle==180 || angle==360) //caso as dimensoes vertical e horizontal da sprite se mantenham
					*(bgMap + sprt->width*i + k) = get_pixel(sprt->x+k, sprt->y+i, base);
				else
					*(bgMap + sprt->width*k + i) = get_pixel(sprt->x+k, sprt->y+i, base);
	}
			
	//desenhar a sprite no sitio certo conforme o angulo		
	for(i=0; i < sprt->height; i++)
		for(k=0; k < sprt->width; k++)
		{
			if(*dSprt != 0)
				switch(angle)
				{
					case 90:	
						set_pixel(sprt->x+i,sprt->y+k, *dSprt, base);//actualiza com o valor actual
						break;
					case 180:
						set_pixel(sprt->x+sprt->width-k,sprt->y+sprt->height-i, *dSprt, base); //actualiza com o valor actual
						break;
					case 270:
						set_pixel(sprt->x+sprt->height-i,sprt->y+sprt->width-k, *dSprt, base); //actualiza com o valor actual
						break;
					default: //angulo 0 e 360
						set_pixel(sprt->x+k,sprt->y+i, *dSprt, base);  //actualiza com o valor actual
						break;
				}
					
			dSprt++;
		}
}

void draw_sprite_scaled(Sprite *sprt, char *base, int width, int height)
{
	char *dSprt = sprt->map;
	char* bgMap = sprt->bgmap;
	sprt->on_screen = true;
	if(bgMap)
	{
		bgMap = realloc(bgMap, width * height);
		sprt->bgmap = bgMap;
	}
	
	double dx = (double)sprt->width / width;
	double dy = (double)sprt->height / height;
	
	int i,k;
	for(i = 0; i < height; i++)
		for(k = 0; k < width; k++)
		{
			if(bgMap) *(bgMap + width*i + k) = get_pixel(sprt->x+k, sprt->y+i, base); //guarda o valor antigo
			
			int map_x = dx*k + 0.5;
			int map_y = dy*i + 0.5;
			int color = *(dSprt + sprt->width*map_y + map_x);
			if(color != 0) set_pixel(sprt->x+k,sprt->y+i, color, base);  //actualiza com o valor mapeado
		}
}


void delete_sprite(Sprite *sprt, char *base)
{
	char* bgMap = sprt->bgmap;
	sprt->on_screen = false;
	if(!bgMap) return;

	int i, k;
	for(i=0; i < sprt->height; i++)
		for(k=0; k < sprt->width; k++)
			set_pixel(sprt->x+k,sprt->y+i, *(bgMap + sprt->width*i + k), base);
		
}



void delete_sprite_rotated(Sprite *sprt, char *base, int angle)
{
	char* bgMap = sprt->bgmap;
	sprt->on_screen = false;
	if(!bgMap) return;

	while(angle < 0) angle += 360;
	while(angle >= 360) angle -= 360;

	int i, k;
	for(i=0; i < sprt->height; i++)
		for(k=0; k < sprt->width; k++)
			if (angle==0 || angle==180) //caso as dimensoes vertical e horizontal da sprite se mantenham
				set_pixel(sprt->x+k,sprt->y+i, *(bgMap + sprt->width*i + k), base);
			else
				set_pixel(sprt->x+i,sprt->y+k, *(bgMap + sprt->width*i + k), base);

}



void delete_sprite_scaled(Sprite *sprt, char *base, int width, int height)
{
	char* bgMap = sprt->bgmap;
	sprt->on_screen = false;
	if(!bgMap) return;

	int i, k;
	for(i = 0; i < height; i++)
		for(k = 0; k < width; k++)
			set_pixel(sprt->x+k,sprt->y+i, *(bgMap + width*i + k), base);

	bgMap = realloc(bgMap, sprt->width * sprt->height);
	sprt->bgmap = bgMap;
}



void destroy_sprite(Sprite *sprt)
{
	if (!sprt) return;
	free(sprt->map);
	free(sprt->bgmap);
	free(sprt);
}



void animate_sprite(Sprite *sprt, char *base)
{
	move_sprite(sprt, sprt->x + sprt->xspeed, sprt->y + sprt->yspeed, base);
}



void animate_sprite_rotated(Sprite *sprt, char *base, int angle)
{
	if (sprt->bgmap != NULL)
	delete_sprite_rotated(sprt, base, angle);
	sprt->x += sprt->xspeed;
	sprt->y += sprt->yspeed;
	draw_sprite_rotated(sprt, base, angle);
	//delay(20);
}



void move_sprite(Sprite *sprt, int x, int y, char *base)
{
	int xi = (x > sprt->x) ? sprt->x : x;
	int yi = (y > sprt->y) ? sprt->y : y;
	int xf = (x > sprt->x) ? x + sprt->width : sprt->x + sprt->width;
	int yf = (y > sprt->y) ? y + sprt->height : sprt->y + sprt->height;

	video_buffer = realloc(video_buffer, HRES * VRES);
	flip_buffer_partial(video_buffer, base, xi, yi, xf - xi, yf - yi);

	delete_sprite(sprt, video_buffer);
	sprt->x = x;
	sprt->y = y;
	draw_sprite(sprt, video_buffer);

	flip_buffer_partial(base, video_buffer, xi, yi, xf - xi, yf - yi);
}



void flip_buffer(char* dest, char* src)
{
	memcpy(dest, src, HRES*VRES);
}



void flip_buffer_partial(char* dest, char* src, int xi, int yi, int width, int height)
{
	if(xi + width >= HRES)
		width = HRES - xi;
	if(xi < 0) {
		width += xi;
		xi = 0;
	}
	if(yi + height >= VRES)
		height = VRES - yi;
	if(yi < 0) {
		height += yi;
		yi = 0;
	}

	int i;
	for (i = 0; i < height; i++)
		memcpy(dest + (yi+i)*HRES + xi, src + (yi+i)*HRES + xi, width);
}


