// Data set size
#define N 300 // 32, 500, 1000, 2000, 4000

#define _PB_N 200

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//static
void kernel_jacobi_2d_imper(int n,
			    int m,
			    float A[N][N])
{
  int i, j;

#pragma HLS ALLOCATION instances=mul limit=3 operation

/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  if ((m <= -1 && m >= -19) || (m <= 19 && m >= 1)) {
    for (int c1 = 100; c1 <= 198; c1 += 1)
      for (int c3 = 100; c3 <= 198; c3 += 1)
        #pragma HLS PIPELINE
        A_flt[300 * c1 + c3] = 0.2f * (A_flt[300 * c1 + c3] + A_flt[-m + 300 * c1 + c3] + A_flt[m + 300 * c1 + c3] + A_flt[300 * m + 300 * c1 + c3] + A_flt[-300 * m + 300 * c1 + c3]);
  } else
    for (int c1 = 100; c1 <= 198; c1 += 1)
      for (int c3 = 100; c3 <= 198; c3 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=A_flt array inter false
        A_flt[300 * c1 + c3] = 0.2f * (A_flt[300 * c1 + c3] + A_flt[-m + 300 * c1 + c3] + A_flt[m + 300 * c1 + c3] + A_flt[300 * m + 300 * c1 + c3] + A_flt[-300 * m + 300 * c1 + c3]);
}

/* End Accelerated Scop */ 

}

/*
#pragma scop
  for (i = 1; i < _PB_N - 1; i++)
    for (j = 1; j < _PB_N - 1; j++)
      B[i][j] = 0.2 * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);
  for (i = 1; i < _PB_N-1; i++)
    for (j = 1; j < _PB_N-1; j++)
      A[i][j] = B[i][j];
#pragma endscop
 */
