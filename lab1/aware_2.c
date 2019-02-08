#include <stdlib.h>
 
// define the matrix dimensions A is MxP, B is PxN, and C is MxN
#define M 2048
#define N 2048
#define P 2048
 
// calculate C = AxB
void matmul(float **a, float **b, float **c) {
  float sum;
  int   i;
  int   j;
  int   k;
  int   bi;
  int   bj;
  int   bk;
  int   bii;
  int   bjj;
  int   bkk;
  int blockSize = 32;
  int blockSize2 = 256;

  for(bii=0; bii<N; bii+=blockSize2)
  	for(bjj=0; bjj<N; bjj+=blockSize2)
          for(bkk=0; bkk<N; bkk+=blockSize2)

  for(bi=bii; bi<bii + blockSize2; bi+=blockSize)
  	for(bj=bjj; bj<bjj + blockSize2; bj+=blockSize)
          for(bk=bkk; bk<bkk + blockSize2; bk+=blockSize)

              for(i=bi; i<bi + blockSize; i++)
                  for(j=bj; j<bj + blockSize; j++)
                      for(k=bk; k<bk + blockSize; k++)
                          c[i][j] += a[i][k]*b[k][j];
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

