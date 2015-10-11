/**\file List.c
 * \brief Módulo que contém toda a implementaçao necessaria sobre listas
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: List.c \n
 * DESCRIÇÃO: Módulo que contém toda a implementaçao necessaria sobre listas \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "List.h"

ListRoot* newListRoot(unsigned int ele_size, void *new_ele) {
	ListRoot *new_list = (ListRoot*) malloc(sizeof(ListRoot));

	if (new_ele) {
		ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
		new_list->next_node = new_node;
		new_list->num_ele = 1;
	} else {
		new_list->next_node = NULL;
		new_list->num_ele = 0;
	}

	return new_list;
}

ListNode* newListNode(void *ele, ListNode *next_node) {
	ListNode *new_list_node = (ListNode*) malloc(sizeof(ListNode));
	new_list_node->ele = (ListNode*)ele;
	new_list_node->next_node = next_node;

	return new_list_node;

}


void insertList(ListRoot *list_root, void *ele) {
	ListNode* ele_temp = list_root->next_node;

	while(ele_temp)
		if (ele_temp->next_node == NULL) {
			ListNode *new_list_node = newListNode(ele, 0);
			ele_temp->next_node = new_list_node;
			++(list_root->num_ele);
			break;
		}
		else
			ele_temp = ele_temp->next_node;
}


void insertSortedList(void *ele, ListRoot *list_root) {
	ListNode *prev_node = list_root->next_node;
	ListNode *next_node = prev_node->next_node;

	while (*(next_node->ele) < *ele) {
		prev_node = next_node;
		next_node = next_node->next_node;
	}

	ListNode *new_node = newListNode(ele, next_node);
	prev_node->next_node = new_node;
	++(list_root->num_ele);
}


void clearList(ListRoot *list_root) {
	ListNode *prev_node_temp = list_root->next_node;
	ListNode *next_node_temp = prev_node_temp->next_node;

	while(next_node_temp) {
		prev_node_temp = next_node_temp;
		free(prev_node_temp);
		next_node_temp = next_node_temp->next_node;
	}
}


void deleteList(List *list) {
	clearList(list);
	free(list);
}
