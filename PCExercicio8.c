#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define n 10000000

int main() {
    float vetor[n];
    int i;
    float sum = 0.0, mean, diferenca = 0.0, result;

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        vetor[i] = (float)rand() / RAND_MAX;
    }

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += vetor[i];
    }
    mean = sum / n;


    #pragma omp parallel for reduction(+:sum_sq_diff)
    for (i = 0; i < n; i++) {
        float a = vetor[i] - mean;
        diferenca += a * a;
    }
    result = sqrt(diferenca / n);

    printf("Desvio padraoo: %.5f\n", result);

    return 0;
}
