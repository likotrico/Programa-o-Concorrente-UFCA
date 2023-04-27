#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(){
    float a, b, x, d;
    float result;
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task depend(out: x)
                {
                    x = 1;
                    printf("x: %.1f\n", x);
                }
            #pragma omp task depend(out: d)
                {
                    d = -15;
                    printf("d: %.1f\n", d); 
                }
            #pragma omp task depend (in: x) depend(out: a) 
                {
                    a = x * x * x;
                    printf("a: %.1f\n", a); 
                }
            #pragma omp task depend(in: x) depend(out: b)
                {
                    b = 3*x*x;
                    printf("b: %.1f\n", b);
                }
            #pragma omp task depend(in: a) depend(in: b) depend(in: d) depend(out: result)
                {
                    result = a + b + d;
                    printf("result: %.1f\n", result);
                }
        }
    }
    return 0;
}
