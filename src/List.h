/**\file List.h
 * \brief M�dulo que cont�m toda a implementa�ao necessaria sobre listas
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: List.h \n
 * DESCRI��O: M�dulo que cont�m toda a implementa�ao necessaria sobre listas \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>


typedef struct {
	struct ListNode *next_node;
	void *ele;
} ListNode;


typedef struct {
	ListNode *next_node;
	unsigned int num_ele;
} ListRoot;


ListRoot *newListRoot(unsigned int ele_size, void *new_ele);
ListNode *newListNode(void *ele, ListNode *next_node);

///fun�aao que insere na lista um determinado elemento
void insertList(ListRoot *list_root, void *ele);
void insertSortedList(void *ele, ListRoot *list_root);
///fun�ao que limpa um lista
void clearList(ListRoot *list_root);

///Fun�ao que elemina da lista
void deleteList(ListRoot *list);


#endif
