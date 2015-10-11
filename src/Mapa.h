#ifndef MAPA_H_
#define MAPA_H_

#include "Vector.h"
#include "Sprite.h"

typedef struct {
	Vector *blocos;
	Sprite bola;
} Mapa;

void printMapa(Mapa *mapa);
void updateMapa(Mapa *mapa);
void generateRandomMapa();

#endif

