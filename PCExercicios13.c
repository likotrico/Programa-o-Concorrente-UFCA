#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100

int *gerar_vetor_binario(int n) {
  int *vetor;
  int i; 
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
    vetor[i] = num;
  }
  return vetor;
}

int main(){
    MPI_Init(NULL, NULL);

    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *arquivo_vetor = NULL, *sub_vetor = NULL, *vetor_zeros = NULL, *vetor_uns = NULL;
    int qtd_um = 0, qtd_zero = 0, i;
    int quantidade = TAM/nprocs;
    sub_vetor = malloc(sizeof(int)*quantidade);
    vetor_zeros = malloc(sizeof(int)*nprocs);
    vetor_uns = malloc(sizeof(int)*nprocs);
    if(rank == 0){
        arquivo_vetor = gerar_vetor_binario(TAM);
    }
    MPI_Scatter(arquivo_vetor, quantidade, MPI_INT, sub_vetor, quantidade, MPI_INT, 0, MPI_COMM_WORLD);
    for(i = 0; i < quantidade; i++){
        if(sub_vetor[i] == 0) qtd_zero += 1;
        else qtd_um += 1;    
    }
    MPI_Gather(&qtd_um, 1, MPI_INT, vetor_uns, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&qtd_zero, 1, MPI_INT, vetor_zeros, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        int total_zeros = 0, total_uns = 0;
        for(i = 0; i < nprocs; i++){
            total_zeros += vetor_zeros[i];
            total_uns += vetor_uns[i];
        }
        printf("Zeros: %d\t", total_zeros);
        printf("Uns: %d\t", total_uns);
        printf("Qtd um é impar? %d", total_uns % 2 );
        if((total_uns % 2 )!= 0){
            arquivo_vetor =(int*)realloc(arquivo_vetor, sizeof(int)*(TAM+1));
            arquivo_vetor[TAM] = 1;
        }
        printf("\n");
        for(i = 0; i < TAM+1; i++){
            printf("%d\n", arquivo_vetor[i]);
        }
    }


    MPI_Finalize();
    return 0;
}