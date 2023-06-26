int main(){

	srand(time(NULL));

    Vector *v = vector_construct();

    int N, i, M = 1000;
    for (N = 1; N <= 2001; N += 200){ //50100 e 400
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
    }

    vector_destroy(v);

    return 0;
}
