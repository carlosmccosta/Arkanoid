/**\file Queue.c
 * \brief Modulo que contem funções de manipulação da fila constituída por caracteres
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Queue.c \n
 * DESCRIÇÃO: Modulo que contem funções de manipulação da fila constituída por caracteres \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 
#include "Queue.h"

void queueInit(Queue *q)
{
	q->in = q->out = 0;
	q->cnt = 0;
	q->size = 16;
}

void queuePutPreHandler() {}

Bool queuePut(Queue *q, unsigned char c)
{
	if (queueFull(q)) {
		return false;
	}
	else {	
		q->buf[q->in] = c;
		
		/* incrementa para a proxima posicao */
		q->in++;

		/* incrementar o numero de elementos da queue */
		q->cnt++;
		
		if(q->in == q->size)
			q->in = 0;
	}
	
	return true;
}

void lock_queuePut() { _go32_dpmi_lock_code(lock_queuePut, (unsigned long)(lock_queuePut - queuePutPreHandler)); }


unsigned char queueGet(Queue *q)
{
	if (queueEmpty(q))
		return 0xFF;
	else {
		unsigned char c = q->buf[q->out];
		q->out++;
		q->cnt--;
		if(q->out == q->size)
			q->out = 0;
		return c;
	}
}

Bool queueEmpty(Queue *q)
{
	if (q->cnt == 0)
		return true;
		
	return false;
}


void queueFullPreHandler() {}

Bool queueFull(Queue *q)
{
	if (q->cnt == q->size)
		return true;
		
	return false;
}


void lock_queueFull() { _go32_dpmi_lock_code(lock_queueFull, (unsigned long)(lock_queueFull - queueFullPreHandler)); }
