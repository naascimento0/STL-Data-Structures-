#include "list.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

List *list_construct(){

    List *list = calloc(1, sizeof(List));
    list->last = list->head = NULL;

    return list;
}

int list_size(List *l){

    return l->size;
}

void list_push_front(List *l, data_type data){

    Node *new = node_construct(data, NULL, l->head);
    if(l->head != NULL)
        l->head->prev = new;
    else
        l->last = new;
    
    l->head = new;
    l->size++;
}

void list_push_back(List *l, data_type data){

    Node *new = node_construct(data, l->last, NULL);

    if(l->last != NULL)
        l->last->next = new;
    else
        l->head = new;

    l->last = new;
    l->size++;
}

void list_print(List *l, void (*print_fn)(data_type)){

    printf("[");

    Node *aux = l->head;

    while(aux != NULL){

        print_fn(aux->value);
        aux = aux->next;

        if(aux != NULL)
            printf(", ");
    }

    printf("]");
}

void list_print_reverse(List *l, void (*print_fn)(data_type)){

    printf("[");

    if(l->last != NULL){
        Node *aux = l->last;

        while(aux != NULL){

            print_fn(aux->value);
            aux = aux->prev;

            if(aux != NULL)
                printf(", ");
        }
    }

    printf("]");

}

void list_destroy(List *l){

    while(l->head != NULL){

        Node *aux = l->head;
        l->head = l->head->next;
        node_destroy(aux);
    }

    free(l);
}

data_type list_pop_front(List *l){

    if(l->head == NULL)
	    exit(printf("Error: list is empty!\n"));

    Node *aux = l->head;
    data_type value = aux->value;
    l->head = aux->next;
    node_destroy(aux);
    l->size--;

    return value;
}

ListIterator *list_front_iterator(List *l){

	ListIterator *it = malloc(sizeof(ListIterator));
	it->current = l->head;

	return it;
}

ListIterator *list_back_iterator(List *l){

	ListIterator *it = malloc(sizeof(ListIterator));
	it->current = l->last;

	return it;
}

data_type *list_iterator_next(ListIterator *it){

	data_type* data = &(it->current->value);
	it->current = it->current->next;

	return data;
}

data_type *list_iterator_previous(ListIterator *it){

	data_type* data = &(it->current->value);
	it->current = it->current->prev;

	return data;
}

bool list_iterator_is_over(ListIterator *it){

	return it->current == NULL;
}

void list_iterator_destroy(ListIterator *it){

	free(it);
}
