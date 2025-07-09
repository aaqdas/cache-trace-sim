#include <stdio.h>
#include <stdlib.h>
#define BLOCKED

double** alloc_matrix(int N) {
    double** mat = malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++)
        mat[i] = calloc(N, sizeof(double));
    return mat;
}

void free_matrix(double** mat, int N) {
    for (int i = 0; i < N; i++) free(mat[i]);
    free(mat);
}

void init_matrix(double** mat, int N, double value) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = value;
}




void matmul_naive(int N, double** A, double** B, double** C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul_blocked(int N, double** A, double** B, double** C, int blockSize) {
    for (int ii = 0; ii < N; ii += blockSize) {
        for (int jj = 0; jj < N; jj += blockSize) {
            for (int kk = 0; kk < N; kk += blockSize) {
                for (int i = ii; i < ii + blockSize && i < N; i++) {
                    for (int j = jj; j < jj + blockSize && j < N; j++) {
                        double sum = C[i][j];
                        for (int k = kk; k < kk + blockSize && k < N; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}
int main() {
    int N = 64;
    int blockSize = 16;

    double** A = alloc_matrix(N);
    double** B = alloc_matrix(N);
    double** C = alloc_matrix(N);

    init_matrix(A, N, 1.0);
    init_matrix(B, N, 2.0);
    #ifdef NAIVE
        matmul_naive(N, A, B, C);
    #endif
    #ifdef BLOCKED
        matmul_blocked(N, A, B, C, blockSize);
    #endif
    printf("C[0][0] = %f\n", C[0][0]); // should print something like 1024.0

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}