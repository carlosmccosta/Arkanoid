/**\file Sprite.h
 * \brief Módulo que contem toda a implementaçao para tratamento de imagens
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Sprite.h \n
 * DESCRIÇÃO: Módulo que contem toda a implementaçao para tratamento de imagens \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef SPRITE_H_
#define SPRITE_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GraficaVideo.h"
#include "utypes.h"


/** @defgroup sprite Sprite
 * @{
 *
 * Sprite related functions
 */

/** A Sprite is an "object" that contains all needed information to
 * create, animate, and destroy a pixmap.  The functions assume that
 * the background is BLACK and they take into account collision with
 * other graphical objects or the screen limits. 
 */
typedef struct {
	int x, y;            ///< current sprite position
	unsigned int width, height;   ///< sprite dimensions
	int xspeed, yspeed;  ///< sprite current speed in the x and y direction
	char *map;           ///< the sprite pixmap (use read_xpm())
	char *bgmap;		   ///<the sprite background map
	Bool on_screen;
} Sprite;

//JANELA DO JOGO
#define MIN_GAME_WINDOWS_X	15
#define MAX_GAME_WINDOWS_X	800
#define MIN_GAME_WINDOWS_Y	15
#define MAX_GAME_WINDOWS_Y	753

//TAMANHO DA NAVE -> 220 - 90
#define NAVE_MIN_X	(15 - 55)
#define NAVE_MAX_X	(MAX_GAME_WINDOWS_X - 220 + 61)
#define NAVE_MIN_Y	15
#define NAVE_MAX_Y	(MAX_GAME_WINDOWS_Y - 90)


#define MAX_SPEED 5    /**< each sprite maximum speed in pixels/frame */
#define RIGHT_HIT 2    /**< collision with right block (WHITE)  */
#define LEFT_HIT 3     /**< collision with left block (WHITE)   */
#define MOUSE_HIT 4    /**< collision with mouse (LIGHTMAGENTA) */

/** Reads a xpm-like sprite defined in "map" (look at pixmap.h for
 * examples). Returns the address of the allocated memory where the
 * sprite was read. Updates "width" and "heigh" with the sprite
 * dimension.  Return NULL on error.
 * Assumes that VRES and HRES (the screen vertical and horizontal resolution)
 * are externaly defined.
 * 
 * Usage example, using the defined sprite in pixmap.h:
 * <pre>
 *   #include "pixmap.h" // defines  pic1, pic2, etc 
 *   int wd, hg;
 *   char *sprite = read_xpm(pic1, &wd, &hg);
 * </pre>
*/


char *read_xpm_gimp (char *map[], unsigned int *wd, unsigned int *ht);

/** Creates with random speeds (not zero) and position
 * (within the screen limits), a new sprite with pixmap "pic", in
 * memory whose address is "base".
 * Returns NULL on invalid pixmap.
 */
 
Sprite* create_sprite(char *pic[]);

Sprite* create_unbuffered_sprite(char *pic[]);

Sprite* create_sprite_pos(char *pic[], int x, int y);

/** draws a sprite in graphics memory
* the sprite's background color isn't drawn 
*/
void draw_sprite(Sprite *sprt, char *base);
//void update_sprite(Sprite* sprt, char* base);

/** draws a sprite in graphics memory
* rotating the sprite with a certain angle
* the sprite's background color isn't drawn 
*/

void draw_sprite_rotated(Sprite *sprt, char *base, int angle);

void draw_sprite_scaled(Sprite *sprt, char *base, int width, int height);

/** Removes the sprite from the screen */
void delete_sprite(Sprite *sprt, char *base);

void delete_sprite_rotated(Sprite *sprt, char *base, int angle);

void delete_sprite_scaled(Sprite *sprt, char *base, int width, int height);

/** The "sprt" sprite is erased from memory whose address is "base"
 * and used resources released.
 */
void destroy_sprite(Sprite *sprt);

void flip_buffer(char* dest, char* src);

void flip_buffer_partial(char* dest, char* src, int xi, int yi, int width, int height);

/** Animate an Animated Sprite
*/
void animate_sprite(Sprite *sprt, char *base);

/** moves the sprite 'sprt' to the position (x,y) */
void move_sprite(Sprite *sprt, int x, int y, char *base);


/** @} end of sprite */

#endif
