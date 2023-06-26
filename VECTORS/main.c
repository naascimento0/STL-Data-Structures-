#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

int compare(const void *a, const void *b) {
    data_type x = *(data_type*)a;
    data_type y = *(data_type*)b;
    if (x < y) return -1;
    else if (x > y) return 1;
    else return 0;
}

void vector_qsort(Vector *v){
    qsort(v->data, v->size, sizeof(data_type), compare);
}

int main(){

	srand(time(NULL));

    Vector *v = vector_construct();

    int N = 1000, i, M = 0;

    Vector *v = vector_construct();

	for(i = 0; i < N; i++){
		vector_push_back(v, rand());
	}

	vector_sort(v);

	double menor = 1e9, maior = 0, media = 0;
	double primeiroElem = 0, ultimoElem;

	int j;
	for(j = 0; j < M; j++){

		int idx = rand() % N;
		int valor = vector_get(v, idx);

		double inicio = get_timestamp();
		vector_sort(v);
		double fim = get_timestamp();
		double duracao = fim - inicio;

		if (duracao < menor){
			menor = duracao;
		}

		if (duracao > maior){
			maior = duracao;
		}

		media += duracao;

		if (valor == vector_get(v, 0)){
			primeiroElem = duracao;
		}

		if (valor == vector_get(v, N - 1)){
			ultimoElem = duracao;
		}
	}

	media /= M;
	printf("%d %.7f %.7f %.7f %.7f %.7f\n", N, menor, maior, media, primeiroElem, ultimoElem);

    vector_destroy(v);

    return 0;
}



