#include "common.h"

//loop unrolling 2*2
void benchmark(double *v, double *dest){
    double sum1 = 1;
    double sum2 = 1;
    int i; 
    for(i = 0; i < MAX; i += 2){
        sum1 = sum1 * v[i];
        sum2 = sum2 * v[i + 1];
    }
    for(; i < MAX; i++) sum1 = sum1 * v[i];
    *dest = *dest * sum1 * sum2;
}

int main(){
    double *a = (double *)malloc(sizeof(double) * MAX);
    memset(a, 0, sizeof(a));
    double ans = 1;
    double start, end;

    //warm up
    benchmark(a, &ans);
    start = wall_time();
    for(int i = 0; i < n_iterator; i++){
        benchmark(a, &ans);
    }
    end = wall_time();
    printf("%d iterators: runtime of this algorimth is: %.4f s\n", n_iterator, (end-start));
    printf("%.2f\n", ans);
    free(a);
    return 0;
}