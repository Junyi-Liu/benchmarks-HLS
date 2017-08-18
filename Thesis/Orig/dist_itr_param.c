// Data set size
#define N 100

void kernel_dist_itr_param(int m,
			   float A[3*N][N])
{

  int i,j;

#pragma HLS ALLOCATION instances=mul limit=2 operation

#pragma scop
  for (i=0; i<N; i++){
    for (j=0; j<2; j++){
      #pragma HLS PIPELINE
      A[2*i+m][j] = A[i][j] + 0.5f;
    }
  }
#pragma endscop


}
