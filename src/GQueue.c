/**\file GQueue.c
 * \brief Modulo queue genérica equivalente ao modulo Queue, mas generalizado, ou seja aceita elementos de qualquer tipo. Esta queue é usada na implementação do rato.
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: GQueue.c \n
 * DESCRIÇÃO: Modulo queue genérica equivalente ao modulo Queue, mas generalizado, ou seja aceita elementos de qualquer tipo. Esta queue é usada na implementação do rato.  \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 

#include "GQueue.h"


GQueue* newGQueue(int n_ele, int ele_size)
{
	GQueue* q = (GQueue*) malloc(sizeof(GQueue));
	if(!q) return NULL;
	
	q->ptr = malloc(n_ele * ele_size);
	if(!(q->ptr))
	{
		free(q);
		return NULL;
	}
	
	q->in = q->out = q->count = 0;
	q->size = n_ele; q->ele_size = ele_size;

	return q;
}


void deleteGQueue(GQueue* q)
{
	free(q->ptr);
	free(q);
}

void putGQueuePreHandler() {}

Bool putGQueue(GQueue* q, void* ele)
{
	if (isFullGQueue(q)) return false;
	
	// memcpy(dest, src, n_bytes) - “memory copy”
	memcpy(q->ptr + q->in, ele, q->ele_size);
	
	q->count++;
	q->in += q->ele_size;
	if(q->in == q->size * q->ele_size) q->in = 0;
	
	return true;
}

void lock_putGQueue() { _go32_dpmi_lock_code(putGQueue, (unsigned long)(lock_putGQueue - putGQueuePreHandler)); }


void* peekGQueue(GQueue* q)
{
	if (isEmptyGQueue(q)) return NULL;
	return q->ptr + q->out;
}


void* getGQueue(GQueue* q)
{
	if (isEmptyGQueue(q)) return NULL;
	void* pnt_data = q->ptr + q->out;
	
	q->count--;
	q->out += q->ele_size;
	if(q->out == q->size * q->ele_size) q->out = 0;
		
	return pnt_data;
}


void clearGQueue(GQueue* q)
{
	q->in = q->out = q->count = 0;
}


Bool isEmptyGQueue(GQueue* q)
{
	return q->count == 0;
}

void isFullGQueuePreHandler() {}

Bool isFullGQueue(GQueue* q)
{
	return q->count == q->size;
}

void lock_isFullGQueue() { _go32_dpmi_lock_code(putGQueue, (unsigned long)(lock_isFullGQueue - isFullGQueuePreHandler)); }
