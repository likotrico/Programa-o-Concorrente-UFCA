#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(){

    float result;
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        #pragma omp single
        {
            float a, b, result, x, d;
            #pragma omp task depend(out: x)
                x = 1;
                printf("%f\n", x);
            #pragma omp task depend(out: d)
                d = -15;
            #pragma omp task depend(out: a)
                a = x * x * x;
            #pragma omp task depend(in: x) depend(out: b)
                b = 3*x*x;
            #pragma omp task depend(in: a) depend(in: b) depend(in: d) depend(out: result)
                result = a + b + d;
                printf("%f\n", a);            
                printf("%f\n", b); 
                printf("%f\n", d); 
        }
    }
    
    
      

    return 0;
}