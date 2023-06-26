#include "forward_list.h"

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
			printf(",");
	}

	printf("]");
}

void forward_list_destroy(ForwardList *l){

	while(l->head != NULL){

		Node *aux = l->head;
		l->head = l->head->next;
		node_destroy(aux);
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
