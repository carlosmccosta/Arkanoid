/**\file GraficaTexto.h
 * \brief Modulo que implementa a placa grafica no modo texto a ser usada no jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: GraficaTexto.h \n
 * DESCRIÇÃO: Modulo que implementa a placa grafica no modo texto a ser usada no jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#ifndef GRAFICATEXTO_H_
#define GRAFICATEXTO_H_

#include <sys/farptr.h>		//onde estao definidas as funcoes _farpokeb() e _farpeekb()
#include <go32.h>			//onde se encontra definido '_dos_ds'
#include "utypes.h"

/** @name Screen and video memory definitions in text mode */
/*@{*/
#define VIDEO_TEXT 0xB8000 ///< Video address in text mode
#define WIDTH 80	   ///< Number of rows
#define HEIGHT 25	   ///< Number of columns
/*@}*/

/** @name Bit meaning in attribute byte
* (see color definitions in system header file conio.h)
*/
/*@{*/
#define BLUE_FOREG  (1 << 0)  ///< Foreground blue bit
#define GREEN_FOREG (1 << 1)  ///< Foreground green bit
#define RED_FOREG   (1 << 2)  ///< Foreground red bit

#define STRONG      (1 << 3)  ///< Foreground intensity bit

#define BLUE_BACK   (1 << 4)  ///< Background blue bit
#define GREEN_BACK  (1 << 5)  ///< Background gren bit
#define RED_BACK    (1 << 6)  ///< Background red bit

//#define BLINK       (1 << 7)  ///< already defined in conio.h

#define NORMAL (RED_FOREG | GREEN_FOREG | BLUE_FOREG) ///< handy definition
/*@}*/


/** Calculate memory offset for writing at position x, y
*/
unsigned long calcMemPosition(int x, int y);

///Function that get character at position x, y
int getCharAt(int x, int y);

///Function that get the character at position x, y
int getAttributesAt(int x, int y);

/** Function - Print character ch at position x,y with attributes
* return true if sucessfull
*/
Bool printCharAt(char ch, int x, int y, char attributes);

/** Function - Print character int at position x,y with attributes
* return true if sucessfull
*/
void printIntAt(int num, int x, int y, char attributes);

///Function - Print line
void printLineAt(char ch, int xi, int yi, int xf, int yf, char attributes);

/**Function - Print character array str at position x,y with attributes
* return true if sucessfull
*/
void printStringAt(char *str, int x, int y, char attributes);

/**Function - Clear screen with background color
*/
void fillScreen(char background);

/**Function - Draw rectangular frame with left upper corner at position x,y
* with width and height dimensions, decorated with title attributes.
* return true if sucessfull
*/
Bool drawFrame(char *title, char attributes, int x, int y, int width, int height);

///Function that draw table with n_lin x n_col cells (1x1 size)
Bool drawTable(char attributes, int x, int y, int n_lin, int n_col);


#endif
