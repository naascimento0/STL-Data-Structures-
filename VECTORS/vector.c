#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

//O(1)
Vector *vector_construct(){

	Vector* vector = calloc(1, sizeof(Vector));
	vector->allocated = 10;
	vector->size = 0;
	vector->data = calloc(vector->allocated, sizeof(data_type));

	return vector;
}

//O(1)
void vector_destroy(Vector *v){

	free(v->data);
	free(v);
}

//O(n) ou O(1)
void vector_push_back(Vector *v, data_type val){

	if(v->size >= v->allocated){
		v->data = realloc(v->data, (2 * v->allocated) * sizeof(data_type));
		v->allocated *= 2;
	}

	v->data[v->size] = val;
	v->size += 1;
}

//O(1)
int vector_size(Vector *v){

	return v->size;
}

//O(1)
data_type vector_get(Vector *v, int i){

	if(i >= v->size || i < 0){
		printf("Invalid index\n");
		exit(1);
	}

	return v->data[i];
}

//O(1)
void vector_set(Vector *v, int i, data_type val){

	v->data[i] = val;
}

//O(n)
int vector_find(Vector *v, data_type val){

	int i;
	for(i = 0; i < v->size; i++){

		if(v->data[i] == val){ //vector_get(v, i)
			return i;
		}
	}

	return -1;
}

//O(n)
data_type vector_remove(Vector *v, int i){

	data_type remove = v->data[i];

	int k;
	for(k = i; k < v->size - 1; k++)
		v->data[k] = v->data[k + 1];
	
	v->size--;

	return remove;
}

//O(n)
data_type vector_pop_front(Vector *v){

	return vector_remove(v, 0);
}

//O(1)
data_type vector_pop_back(Vector *v){

	return vector_remove(v, v->size - 1);
}

//O(n)
void vector_insert(Vector *v, int i, data_type val){

	if(v->size >= v->allocated){
		v->data = realloc(v->data, (2 * v->allocated) * sizeof(data_type));
		v->allocated *= 2;
	}

	int k;
	for(k = vector_size(v); k >= i; k--)
		v->data[k + 1] = v->data[k];
	
	v->size++;
	v->data[i] = val;
}

//O(1)
void vector_swap(Vector *v, int i, int j){

	data_type aux = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = aux;
}

//O(n²)
void vector_sort(Vector *v){

	int i, j;
	for(i = 0; i < vector_size(v) - 1; i++){

		for(j = 0; j < vector_size(v) - 1 - i; j++){

			if(v->data[j] > v->data[j + 1])
				vector_swap(v, j, j + 1);
		}
	}
}

//O(log(n))
int vector_binary_search(Vector *v, data_type val){

	int left = 0;
	int right = v->size - 1;

	while(left <= right){

		int mid = (left + right) / 2;

		if(v->data[mid] == val)
			return mid;
		else if(v->data[mid] > val)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}

//O(n²)
void vector_reverse(Vector *v){

	int i, j;
	for(i = 0; i < v->size; i++){

		for(j = 0; j < v->size - 1 - i; j++){

			int aux = v->data[j + 1];
			v->data[j + 1] = v->data[j];
			v->data[j] = aux;
		}
	}
}


//O(n)
/*void vector_reverse(Vector *v)
{
    for (int i = 0; i < v->size / 2; i++)
        vector_swap(v, i, v->size - i - 1);
}*/
