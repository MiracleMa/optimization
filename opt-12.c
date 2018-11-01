#include "common.h"
#include <immintrin.h>
//using SIMD and loop unrolling 4*1
void benchmark(double *v, double *dest){
    __m256d sum = _mm256_setzero_pd();
    int i;
    for(i = 0; i < MAX; i += 16){
        sum = _mm256_mul_pd(sum, _mm256_mul_pd( \
                                 _mm256_mul_pd(_mm256_loadu_pd(v + i), _mm256_loadu_pd(v + i + 4)), \
                                 _mm256_mul_pd(_mm256_loadu_pd(v + i + 8), _mm256_loadu_pd(v + i + 12))));
    }
    double d[4];
    _mm256_storeu_pd(d, sum);
    double ret = d[0] * d[1] * d[2] * d[3];
    for(; i < MAX; i++) ret = ret * v[i];
    *dest = *dest * ret;
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
    free(a);
    return 0;
}