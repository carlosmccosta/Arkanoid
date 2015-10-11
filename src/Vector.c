/**\file Vector.c
 * \brief Classe que trata da implementacao de um vector
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Vector.c \n
 * DESCRIÇÃO: Classe que trata da implementacao de um vector \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#include "Vector.h"

Vector* newVector(unsigned int tamanho_ele, unsigned int tamanho_vec, void *ptr) {
	Vector* vec = (Vector*) malloc(sizeof(Vector));

	if(vec == NULL)
		return NULL;

	if (ptr == NULL) {
		vec->ptr = malloc(tamanho_vec * tamanho_ele);
		vec->count = 0;
	}
	else {
		vec->ptr = ptr;
		vec->count = tamanho_vec;
	}
	vec->size = tamanho_vec;
	vec->ele_size = tamanho_ele;

	return vec;
}


Bool isEmptyVector(Vector* vec) {
	return (vec->count == 0);
}


unsigned int sizeVector(Vector* vec) {
	return vec->count;
}


void growVector(Vector* vec)
{
	if (vec->size == 0)
		vec->size++;
	else
		vec->size *= 2;
	
	vec->ptr = realloc(vec->ptr, vec->size * vec->ele_size);
}


void shrinkVector(Vector* vec)
{
	vec->size /= 2;
	vec->ptr = realloc(vec->ptr, vec->size * vec->ele_size);
}


void* elementAtVector(Vector* vec, unsigned int index) {
	if(index < 0 || index >= vec->count)
		return NULL;

	return vec->ptr + index * vec->ele_size;
}

void* get_back_element(Vector *vec) {
	return (elementAtVector(vec, vec->count - 1));
}

void push_backVector(Vector* vec, void* ele) {
	if(vec->count == vec->size)
		growVector(vec);

	void* new_ele_pos = vec->ptr + vec->count * vec->ele_size;
	memcpy(new_ele_pos, ele, vec->ele_size);
	++(vec->count);
}


void pop_backVector(Vector* vec) {
	if(isEmptyVector(vec))
		return;

	--(vec->count);

	if(vec->count <= vec->size/2)
		shrinkVector(vec);
}


void clearVector(Vector* vec) {
	vec->ptr = realloc(vec->ptr, 1);
	vec->count = 0;
	vec->size = 1;
}


void deleteVector(Vector* vec) {
	free(vec->ptr);
	free(vec);
}



