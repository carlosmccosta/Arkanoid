/**\file Bola.h
 * \brief Módulo com as subrotinas necessárias para o uso da nave do Bola
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Bola.h \n
 * DESCRIÇÃO: Módulo com as subrotinas necessárias para o uso da nave do Bola \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef BOLA_H_
#define BOLA_H_

#include <Math.h>
#include <stdlib.h>

#include "Sprite.h"
#include "Teclado.h"
#include "Rato.h"
#include "GraficaVideo.h"
#include "utypes.h"

#include "Sprite.h"
#include "GraficaVideo.h"
#include "Altifalante.h"
#include "Bloco.h"
#include "Nave.h"
#include "Timer.h"
#include "Altifalante.h"
#include "RTC.h"
#include "utypes.h"

#include "xpm\GameOver.xpm"
//#include "xpm\Bola.xpm"


int pontuation;
int lives;
int speed;
unsigned int blocos_destruidos;

#define SCORE_X_POS 880
#define SCORE_Y_POS 355
#define SPEED_X_POS 880
#define SPEED_Y_POS 405
#define LIFES_X_POS 880
#define LIFES_Y_POS 455


#define COLLISION_DETECTION_OFFSET 5


extern Sprite* bola;

///Funcão que implementa a trajectoria da bola
int move_ball(Sprite *bola, Vector *vec_blocos);



#endif
