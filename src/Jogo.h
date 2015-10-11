#ifndef JOGO_H_
#define JOGO_H_

#include "GraficaVideo.h"
#include "GraficaTexto.h"
#include "Sprite.h"
#include "Nave.h"
#include "Bola.h"
#include "RTC.h"
#include "Music.h"
#include "RTC.h"
#include "MapasDB.h"
#include "Timer.h"
#include "xpm\GameFrame.xpm"
#include "xpm\Sucess.xpm"
#include "xpm\Bola.xpm"



void drawGameFrame(char *VIDEO_BASE_ADDRESS, char *codepage);
void startJogo(int modo_carregamento_mapa);
void saveJogo();
void loadJogo();

#endif
