#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int sequencial(int num){

}

int main(){
    time_t t;
    srand((unsigned) time(&t));
    long int *vetor;
    int i, tamanho = 500000000;
    vetor = (long int*)malloc(sizeof(long int)*tamanho);
    
    for(i = 0; i < tamanho; i++){
        int random = (rand() % (tamanho + 1));
        vetor[i] = random;
    }
    int num = 37;
    double inicio, fim;
    inicio = omp_get_wtime();
    int achamos = 0;
    for(i = 0; i < tamanho; i++){
        if(vetor[i] == num) achamos = 1;
    }

    printf("%d", achamos);
    achamos = 0;
    fim = omp_get_wtime();
    double sequencial_diff = fim - inicio;
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
            for(i = 0; i < tamanho; i++){
                if(vetor[i] == num) achamos = 1;
            }

    }
    printf("%d", achamos);
    fim = omp_get_wtime();
    double paralelo_diff = fim - inicio;
    printf("\nseq: %f\n", sequencial_diff);
    printf("par: %f\n", paralelo_diff);
    printf("div: %f", sequencial_diff/paralelo_diff);

    return 0;
}