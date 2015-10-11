#ifndef RECORDSDB_H_
#define RECORDSDB_H_

#include "Vector.h"
#include "Jogador.h"

typedef struct {
	char *nome;
	int pontuacao;
} Pontuacao;


extern Vector *records;

void init_records();
void addRecord(Jogador* jogador);
void listRecords();
void saveRecords();
void loadRecords();

#endif
