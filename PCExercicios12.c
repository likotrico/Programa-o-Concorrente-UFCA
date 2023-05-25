#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAM 10

int main()
{

    MPI_Init(NULL, NULL);

    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *vetor = NULL;
    int tam_paralelo = 5;
    int *sub_vetor = NULL, i;
    double *vetor_soma = NULL;
    double media = 0;
    sub_vetor = malloc(sizeof(int) * tam_paralelo);

    if (rank == 0)
    {
        vetor_soma = malloc((nprocs) * sizeof(double));
        vetor = (int *)malloc(sizeof(int) * TAM);
        for (i = 0; i < TAM; i++)
        {
            vetor[i] = i + 1;
        }
        // CÁLCULO DA MÉDIA
        for (i = 0; i < TAM; i++)
        {
            media += vetor[i];
        }
        media = media / TAM;
        MPI_Bcast(&media, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    MPI_Scatter(vetor, tam_paralelo, MPI_INT, sub_vetor, tam_paralelo, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&media, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double somatorio = 0;
    double diff;
   
    for (i = 0; i < tam_paralelo; i++)
    {
        diff = sub_vetor[i] - media;
        somatorio += diff * diff;
    }

    MPI_Gather(&somatorio, 1, MPI_DOUBLE, vetor_soma, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    //MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
    {
        double total = 0;
        for (i = 0; i < nprocs; i++)
        {
            total += vetor_soma[i];
        }
        double desvioPadrao = total;
        desvioPadrao = desvioPadrao / TAM;
        desvioPadrao = sqrt(desvioPadrao);
        printf("Desvio padrao: %e\n", desvioPadrao);
    }

    MPI_Finalize();

    return 0;
}