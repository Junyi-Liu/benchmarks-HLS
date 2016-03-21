// Data set size
#define N 300 // 32, 500, 1000, 2000, 4000

#define _PB_N 200


void kernel_jacobi_2d_imper(int n,
			    int m,
			    float A[N][N])
{
  int i, j;

#pragma HLS ALLOCATION instances=mul limit=3 operation

#pragma scop
  for (i = 100; i < _PB_N - 1; i++){
    for (j = 100; j < _PB_N - 1; j++)
      #pragma HLS PIPELINE
      A[i][j] = 0.2f * (A[i][j] + A[i][j-m] + A[i][m+j] + A[m+i][j] + A[i-m][j]);
  } 
#pragma endscop

}

