/**\file GQueue.h
 * \brief Modulo queue genérica equivalente ao modulo Queue, mas generalizado, ou seja aceita elementos de qualquer tipo. Esta queue é usada na implementação do rato.
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: GQueue.h \n
 * DESCRIÇÃO: Modulo queue genérica equivalente ao modulo Queue, mas generalizado, ou seja aceita elementos de qualquer tipo. Esta queue é usada na implementação do rato.  \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

 
 /** @defgroup queue Queue
 * @{
 *
 * Queue related functions
 */

/** Queue definition
 */
#ifndef GQUEUE_H_
#define GQUEUE_H_

#include <stdlib.h>
#include <string.h>
#include <dpmi.h>

#include "utypes.h"

typedef struct
{
	void *ptr;
	int in, out, count, size, ele_size;
	
} GQueue;

GQueue* newGQueue(int n_ele, int ele_size);
void deleteGQueue(GQueue* q);
void lock_putGQueue();
Bool putGQueue(GQueue* q, void* ele);
void* peekGQueue(GQueue* q);
void* getGQueue(GQueue* q);
void clearGQueue(GQueue* q);
Bool isEmptyGQueue(GQueue* q);
Bool isFullGQueue(GQueue* q);
void lock_isFullGQueue();

#endif
