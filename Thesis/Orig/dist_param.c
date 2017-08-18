// Data set size
#define N 100

void kernel_dist_param(int m,
		     float A[2*N])
{

  int i;

#pragma scop
  for (i=0; i<N; i++){
    #pragma HLS PIPELINE
    A[i+m] = A[i] + 0.5f;
  }
#pragma endscop


}
