#include <stdlib.h>
 
// define the matrix dimensions A is MxP, B is PxN, and C is MxN
#define M 4096
#define N 4096
#define P 4096
 
// calculate C = AxB
void matmul(float **a, float **b, float **c) {
  float sum;
  int   i;
  int   j;
  int   k;
  int   bi;
  int   bj;
  int   bk;
  int blockSize = 16;

  for(bi=0; bi<N; bi+=blockSize)
  	for(bj=0; bj<N; bj+=blockSize)
          for(bk=0; bk<N; bk+=blockSize)
              for(i=0; i<blockSize; i++)
                  for(j=0; j<blockSize; j++)
                      for(k=0; k<blockSize; k++)
                          c[bi+i][bj+j] += a[bi+i][bk+k]*b[bk+k][bj+j];
}
 
// function to allocate a matrix on the heap
// creates an mXn matrix and returns the pointer.
//
// the matrices are in row-major order.
void create_matrix(float*** A, int m, int n) {
  float **T = 0;
  int i;
 
  T = (float**)malloc( m*sizeof(float*));
  for ( i=0; i<m; i++ ) {
     T[i] = (float*)malloc(n*sizeof(float));
  }
  *A = T;
}
 
int main() {
  float** A;
  float** B;
  float** C;
 
  create_matrix(&A, M, P);
  create_matrix(&B, P, N);
  create_matrix(&C, M, N);
 
  // assume some initialization of A and B
  // think of this as a library where A and B are
  // inputs in row-major format, and C is an output
  // in row-major.
 
  matmul(A, B, C);
 
  return (0);
}

