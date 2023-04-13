#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DOUBLE 100
#define MAX 10
#define TAMANHO_DOUBLE 100000000
#define TAMANHO 10

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);
int count_serial(int *v, int x, int tamanho);
int count_serial_double(double *v, int x, int tamanho);
int count_paralelo(int *v, int x, int tamanho);
int count_paralelo_double(double *v, int x, int tamanho);

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    mostrar_vetor_inteiro(vetor, TAMANHO);

    //SEQUENCIAL
    double inicio = omp_get_wtime();
    printf("%d\n", count_serial(vetor, 5, TAMANHO));
    double fim = omp_get_wtime();
    double tsep = fim-inicio;
    printf("TSequencial: %f\n", tsep);
    


    //PARALELO
    inicio = omp_get_wtime();
    printf("%d\n", count_paralelo(vetor, 5, TAMANHO));
    fim = omp_get_wtime();
    printf("TParalelo: %f\n",fim-inicio);
    double speedup = tsep/(fim-inicio);
    printf("SpeedUp: %f\n", speedup);
    printf("Eficiência: %f\n", speedup/3);

    printf("\n");
    printf("\n");

    //CRIANDO VETOR DOUBLE
    double *vetor_double = NULL;
    vetor_double = gerar_vetor(TAMANHO_DOUBLE);
    //mostrar_vetor(vetor_double, TAMANHO_DOUBLE);

    //SEQUENCIAL DOUBLE
    inicio = omp_get_wtime();
    printf("%d\n", count_serial_double(vetor_double, 50, TAMANHO_DOUBLE));
    fim = omp_get_wtime();
    tsep = fim-inicio;
    printf("TSequencial_double: %f\n", tsep);
    


    //PARALELO DOUBLE
    inicio = omp_get_wtime();
    printf("%d\n", count_paralelo_double(vetor_double, 50, TAMANHO_DOUBLE));
    fim = omp_get_wtime();
    printf("TParalelo_double: %f\n",fim-inicio);
    speedup = tsep/(fim-inicio);
    printf("SpeedUp_double: %f\n", speedup);
    printf("Eficiência_double: %f\n", speedup/3);



    /*
    FIM
    */
    return 0;
}


//SEQUENCIAL
int count_serial(int *v, int x, int tamanho){
    int count = 0;
    for(int i = 0; i < tamanho; i++){
        if(v[i] == x) count++;
    }
    return count;
}

int count_serial_double(double *v, int x, int tamanho){
    int count = 0;
    for(int i = 0; i < tamanho; i++){
        if(v[i] == x) count++;
    }
    return count;
}

//PARALELO
int count_paralelo(int *v, int x, int tamanho){
    int count = 0;
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction( + : count)
            for(int i = 0; i < tamanho; i++){
                if(v[i] == x) count++;
            }
    }
    return count;
}

int count_paralelo_double(double *v, int x, int tamanho){
    int count = 0;
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction( + : count)
            for(int i = 0; i < tamanho; i++){
                if(v[i] == x) count++;
            }
    }
    return count;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() % MAX_DOUBLE);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}