/**\file GraficaVideo.h
 * \brief Modulo que implementa a placa grafica no modo grafico a ser usada no jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: GraficaVideo.h \n
 * DESCRIÇÃO: Modulo que implementa a placa grafica no modo grafico a ser usada no jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 
#ifndef GRAFICAVIDEO_H_
#define GRAFICAVIDEO_H_

#include <dpmi.h>
#include <go32.h> //__tb  ,  dosmemget()  e  dosmemput()
#include <sys\nearptr.h> //__djgpp_nearptr_enable()  e  __djgpp_nearptr_disable()

#include "CodePage.h"
#include "conio.h"
#include "utypes.h"

///Tipos de Modos
#define MODE_640x480 0x101
#define MODE_800x600 0x103
#define MODE_1024x768 0x105
#define MODE_1280x1024 0x107

#define TRANSPARENTE -1
#define COR_DE_TIJOLO 113


/*
 * there are two global variables, declared (but not defined) here
 */
extern int HRES;  /**< global variable with the horizontal resolution in pixels */
extern int VRES;  /**< global variable with the vertical resolution in pixels */
extern char *VIDEO_BASE_ADDRESS;
extern char codepage[];
extern unsigned long VIDEO_MEM; //endereco fisico da memoria video, 0xD3000000

// Funçao que obtem o endereco da memoria de video
unsigned long get_video_mem_address(int mode);

/** Enter graphics mode, enabling near pointers and mapping video physical memory
 * to program virtual address.
 *
 * Returns a generic pointer pointing to video memory address or NULL on error. 
 * "mode" specifies the VESA graphics mode to use, and
 * the mapping information is returned through "map".
 *
 * Also initializes two global variables, VRES and HRES,
 */
char * enter_graphics(int mode, __dpmi_meminfo* map);

/** Unmap video memory, disable near pointer and returns to text mode
 */
void leave_graphics(__dpmi_meminfo map);

/** Draws a pixel of color "color" at screen coordinates x, y at memory address "base"
 */
void set_pixel(int x, int y, int color, char *base);

/** Returns the pixel color at screen coordinates x, y at memory address "base"
 */
int get_pixel(int x, int y, char *base);

/** Set graphics memory at memory address "base" to "color".
 */
void clear_screen(char color, char *base);

/** Draw a line of color "color" between point (xi,yi) and (xf,yf) at memory address "base"
*/
void draw_line(int xi, int yi, int xf, int yf, int color, char *base);

/** Funçao que desenha um caracter com cores fornecidas numa dada posicao
*/
void drawCharAt(char c, int x, int y, int fore_color, int back_color,
int char_scale, char *video_base, char *table);

/** Funçao que desenha um caracter no centro com cores fornecidas numa dada posicao
*/
void drawCharCenteredAt(char c, int x, int y, int fore_color, int back_color,
int char_scale, char* video_base, char* table);

/** Funçao que desenha um conjunto de caracteres(string) com cores fornecidas numa dada posicao
*/
void drawStringAt(char* str, int x, int y, int fore_color, int back_color,
int char_scale, char *video_base, char *table);

/** Funçao que desenha um inteiro(numero) com cores fornecidas numa dada posicao
*/
void drawIntAt(int num, int x, int y, int fore_color, int back_color,
int char_scale, char *video_base, char *table);

/** Funçao que desenha um rectangulo com cores fornecidas numa dada posicao
*/
void draw_rectangle(int xi, int yi, int xf, int yf, int espessura, int line_color, int
back_color, char *base);

/*
Sprite* create_sprite(char *pic[]);
void draw_sprite(Sprite *sprt, char *base);
void update_sprite(Sprite* sprt, char* base);
void draw_sprite_rotated(Sprite *sprt, char *base, int angle);
void draw_sprite_scaled(Sprite *sprt, char *base, int width, int height);
void delete_sprite(Sprite *sprt, char *base);
void animate_sprite(Sprite *sprt, char *base);
void move_sprite(Sprite *sprt, int x, int y, char *base);
*/


#endif
