#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define num_steps 100000000

int main(){

    MPI_Init(NULL, NULL);

    double step;
    int i; double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;

    for (i=0;i< num_steps; i++){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo
    }
    pi = step * sum;
    printf("PI serial: %e\n", pi);
    pi = 0.0;
    sum = 0.0;

    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(i = rank; i < num_steps; i+=nprocs){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo
    }
    double num = step * sum;
    double total;
    MPI_Reduce(&num, &total, 1, MPI_DOUBLE, MPI_SUM, 0 ,MPI_COMM_WORLD);

    if(rank == 0){
        printf("PI MPI: %f\n", total);
    }
    
    MPI_Finalize();

    return 0;
}
