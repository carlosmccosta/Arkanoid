/**\file Queue.h
 * \brief Modulo que contem funções de manipulação da fila constituída por caracteres
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Queue.h \n
 * DESCRIÇÃO: Modulo que contem funções de manipulação da fila constituída por caracteres \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "utypes.h"
#include <dpmi.h>

/** @defgroup queue Queue
 * @{
 *
 * Queue related functions
 */

/** Queue definition
 */
typedef struct {
    unsigned char buf[16];  	///< array which the queue is based on
    int in;		///< index on array where to put next element
    int out;		///< index on array where to get next element from
    int cnt;		///< current number of elements in the queue
    int size;		///< queue capacity
} Queue;

/** Initialize the queue
*/
void queueInit(Queue *q);

/** Put char 'c' in the queue pointed to by 'q'
* Returns false if operation failed (the queue is full)
*/
Bool queuePut(Queue *q, unsigned char c);
void lock_queuePut();

/** Get next element from queue
*  Returns -1 (an int) if there are no elements in the queue
*/
unsigned char queueGet(Queue *q);

/** Returns true if the queue is empty
*/
Bool queueEmpty(Queue *q);

/** Returns true if the queue if full
*/
Bool queueFull(Queue *q);

///Funçao que bloqueia o codigo para que não seja paginado para o disco e evite page faults
void lock_queueFull();

#endif /* _QUEUE_H_ */


