#include <stdio.h>
#include <omp.h>

int main(){
    long int number = 1000000100.00;
    long int i;
    double sum_total = 0;
    double inicio = omp_get_wtime();
    
    //SEQUENCIAL
    for(i = 1; i <= number; i++){
        if(number % i == 0) sum_total+= i; 
    }

    printf("Sequencial: %e\n", sum_total);
    double fim = omp_get_wtime();
    printf("TSequencial: %f\n",fim-inicio);
    sum_total = 0;
    inicio = omp_get_wtime();

    //PARALELO REGIÃO CRÍTICA EXPLÍCITA
    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        #pragma omp for 
            for(i = 1; i <= number; i++){
                if(number % i == 0){
                    sum += i;
                }
            }
        #pragma omp critical
            sum_total += sum;
    }

    printf("Critica: %e\n", sum_total);
    fim = omp_get_wtime();
    printf("TCritica: %f\n",fim-inicio);

    sum_total = 0;
    inicio = omp_get_wtime();

    //PARALELO SCHEDULE ESTÁTICO
    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        #pragma omp for schedule(static, 3)
            for(i = 1; i <= number; i++){
                if(number % i == 0){
                    sum += i;
                }
            }
            #pragma omp critical
                sum_total += sum;
    }

    printf("Static: %e\n", sum_total);
    fim = omp_get_wtime();
    printf("TStatic: %f\n",fim-inicio);

    sum_total = 0;
    inicio = omp_get_wtime();

    //PARALELO SCHEDULE DINÂMICO
    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        #pragma omp for schedule(dynamic,3)
            for(i = 1; i <= number; i++){
                if(number % i == 0){
                    sum += i;
                }
            }
            sum_total += sum;
    }

    printf("Dynamic: %e\n", sum_total);
    fim = omp_get_wtime();
    printf("TDynamic: %f\n",fim-inicio);

    return 0;
}