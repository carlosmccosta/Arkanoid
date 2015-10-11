/**\file Vector.h
 * \brief Classe que trata da implementacao de um vector
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Vector.h \n
 * DESCRIÇÃO: Classe que trata da implementacao de um vector \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <string.h>
#include "utypes.h"


 ///Estrutura que contem informaçao acerca do vector
typedef struct {
	//Apontador para o primeiro elemento do array
	void *ptr;
	//Número de elementos guardados
	unsigned int count;
	//Tamanho do vector
	unsigned int size;
	//Tamanho dos elementos do vector
	unsigned int ele_size;

} Vector;

/** \brief Cria um novo vector
 * \param unsigned int tamaho_ele com o tamanho do elemento, unsigned int tamanho_vec com o tamanho do vector , void *ptr apontador = NULL
 * \returns Um novo vector
 */
Vector* newVector(unsigned int tamanho_ele, unsigned int tamanho_vec, void *ptr);

/** \brief Verifica se um vector esta vazio
 * \param Vector* vec 
 * \returns true se este estiver vazio
 */
Bool isEmptyVector(Vector* vec);

/** \brief Verifica o tamanho de um vector
 * \param Vector* vec 
 * \returns count
 */
unsigned int sizeVector(Vector* vec);

void growVector(Vector* vec);
void shrinkVector(Vector* vec);

/** \brief Verifica o tamanho de um vector
 * \param Vector* vec 
 */
void* elementAtVector(Vector* vec, unsigned int index);

/** \brief Funçao de devolve o ultimo elemento do vector
 * \param Vector* vec 
 * \returns devolve o ultimo count que esta presente no vector
 */
 
void* get_back_element(Vector *vec);

/** \brief Funçao de acrescenta um elemento ao vector
 * \param Vector* vec vector que desejamos acrescentar, void* ele elemento que queremos por no vector
 */
void push_backVector(Vector* vec, void* ele);

/** \brief Funçao de retira o ultimo elemento ao vector
 * \param Vector* vec vector que desejamos retirar
 */
void pop_backVector(Vector* vec);

/** \brief Funçao de retira limpa o vector
 * \param Vector* vec vector que desejamos limpar
 */
void clearVector(Vector* vec);

/** \brief Funçao que elimina um dado vector
 * \param Vector* vec vector que desejamos eliminar
 */
void deleteVector(Vector* vec);


#endif
