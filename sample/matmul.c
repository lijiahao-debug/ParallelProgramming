#include <stdio.h>
#include <stdlib.h>
#define N 2048

int main(int argc, char **argv)
{
    int i, j, k;
    double *a, *b, *c;
    a = (double *)malloc(N * N * sizeof(double));
    b = (double *)malloc(N * N * sizeof(double));
    c = (double *)malloc(N * N * sizeof(double));

    /* 行列の初期化 */ for (j = 0; j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            a[j * N + i] = i * j;
            b[j * N + i] = (i == j ? 1 : 0);
            c[j * N + i] = 0.0;
        }
    }
    /* 行列積の計算 */
    
    for (k = 0; k < N; k++)
    {
        for (j = 0; j < N; j++)
        {
            c[k * N + j] = 0.0;
            for (i = 0; i < N; i++)
            {
                c[k * N + j] += a[k * N + i] * b[i * N + j];
            }
        }
    }
    return 0;
}
