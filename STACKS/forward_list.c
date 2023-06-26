#include "forward_list.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>


ForwardList *forward_list_construct(){

	ForwardList *forward = malloc(sizeof(ForwardList));
	forward->head = NULL;
	forward->size = 0;

	return forward;
}

int forward_list_size(ForwardList *l){

	return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data){

	 l->head = node_construct(data, l->head);
	 l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){

	Node *current = l->head;
	printf("[");

	while(current != NULL){

		print_fn(current->value);
		current = current->next;

		if(current != NULL)
			printf(", ");
	}

	printf("]");
}

void forward_list_destroy(ForwardList *l){

	while(l->head != NULL){

		Node *aux = l->head;
		l->head = l->head->next;
		node_destroy(aux);
		l->size--;
	}

	free(l);
}

data_type forward_list_get(ForwardList *l, int i){

	Node *aux = l->head;

	while(i){

		aux = aux->next;
		i--;
	}

	return aux->value;
}

data_type forward_list_pop_front(ForwardList *l){

	Node *aux = l->head;
	l->head = aux->next;

	data_type value = aux->value;
	node_destroy(aux);
	l->size--;

	return value;
}

ForwardList *forward_list_reverse(ForwardList *l){

	ForwardList *l2 = forward_list_construct();

	Node *aux = l->head;
	while(aux != NULL){

		forward_list_push_front(l2, aux->value);
		aux = aux->next;
	}

	return l2;
}

void forward_list_remove(ForwardList *l, data_type val){

	while(l->head != NULL && l->head->value == val){
		forward_list_pop_front(l);
	}

	Node *current = l->head;
	while(current != NULL && current->next != NULL){

		if(current->next->value == val){
			Node *aux = current->next->next;
			node_destroy(current->next);
			current->next = aux;
			l->size--;

		}else{
			current = current->next;
		}
	}
}

void forward_list_cat(ForwardList *l, ForwardList *m){

	while(m->head != NULL){

		forward_list_push_front(l, m->head->value);
		Node *aux = m->head;
		m->head = m->head->next;
		node_destroy(aux);
		m->size--;
	}
}































