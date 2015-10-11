#ifndef MAPADB_H_
#define MAPADB_H_

#include <stdlib.h>
#include <time.h>

#include "Mapa.h"
#include "Nave.h"
#include "Sprite.h"
#include "Vector.h"
#include "Bloco.h"
#include "RTC.h"
#include "Timer.h"
#include "GraficaVideo.h"
#include "xpm\barra.xpm"
#include "xpm\barra1.xpm"
#include "xpm\barra2.xpm"
#include "xpm\barra3.xpm"
#include "xpm\barra4.xpm"

extern Vector *mapa_principal;

void load_mapa_principal();
void load_mapa_principal_random();
void draw_mapa_principal();

void del_mapa_principal();

/*
void loadMapa(Mapa *mapa);
void saveMapa(Mapa *mapa);
void addMapa(Mapa *mapa);
void delMapa(Mapa *mapa);
*/

#endif
