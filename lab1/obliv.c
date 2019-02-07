#include <stdlib.h>
 
// define the matrix dimensions A is MxP, B is PxN, and C is MxN
#define M 4096
#define N 4096
#define P 4096
 
// calculate C = AxB

void recur(int i0, int i1,int j0, int j1, int k0, int k1, float **A, float **B, float **C)
    { 
        int i, j, k, di = i1 - i0, dj = j1 - j0, dk = k1 - k0;
        const int CUTOFF = 8;
        if (di >= dj && di >= dk && di > CUTOFF) {
            int im = (i0 + i1) / 2;
            recur(i0,im,j0,j1,k0,k1, A, B, C);                         
            recur(im,i1,j0,j1,k0,k1, A, B, C);
        } else if (dj >= dk && dj > CUTOFF) {
            int jm = (j0 + j1) / 2;
            recur(i0,i1,j0,jm,k0,k1, A, B, C);                   
            recur(i0,i1,jm,j1,k0,k1, A, B, C);
        } else if (dk > CUTOFF) {
            int km = (k0 + k1) / 2;
            recur(i0,i1,j0,j1,k0,km, A, B, C);                
            recur(i0,i1,j0,j1,km,k1, A, B, C);
        } else {
            for (i = i0; i < i1; ++i) 
                for (j = j0; j < j1; ++j)
                    for (k = k0; k < k1; ++k)
                        C[i][j] += A[i][k] * B[k][j];
        }
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
 
  //matmul(A, B, C);
  recur(0, N, 0, M, 0, P, A, B, C);
 
  return (0);
}

