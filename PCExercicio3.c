#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main(){
    time_t t;
    srand((unsigned) time(&t));
    long int *vetor;
    int i, tamanho = 500000000;
    double soma = 0;
    vetor = (long int*)malloc(sizeof(long int)*tamanho);

    //PREENCHENDO O VETOR
    for(i = 0; i < tamanho; i++){
        int random = 1 + (rand() % 100000);
        vetor[i] = random;
    }
    double inicio, fim;
    inicio = omp_get_wtime();

    for(i = 0; i < tamanho; i++){
        soma = soma + vetor[i];
    }
    
    printf("Soma: %e\n", soma);
    printf("Média: %e\n", (soma/tamanho));

    fim = omp_get_wtime();
    double sequencial_diff = fim - inicio;
    inicio = omp_get_wtime();

    int threads = 3;
    soma = 0;
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for reduction (+: soma)
            for(i = 0; i < tamanho; i++){
                soma = soma + vetor[i];    
            }
    }
    printf("Soma Paralelo: %e\n", soma);
    printf("Média Paralelo: %e\n", (soma/tamanho));

    fim = omp_get_wtime();
    double paralelo_diff = fim - inicio;

    printf("\nSequencial: %f\n", sequencial_diff);
    printf("Paralelo: %f\n", paralelo_diff);
    printf("SpeedUp: %f\n", sequencial_diff/paralelo_diff);
    printf("Eficiência: %f\n", (sequencial_diff/paralelo_diff)/threads);

    return 0;
}