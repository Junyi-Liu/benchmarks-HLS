// Data set size
#define N 100

void kernel_dist_itr(float A[2*N])
{

  int i;

#pragma scop
  for (i=0; i<N; i++){
    #pragma HLS PIPELINE II=14
    A[2*i] = A[i] + 0.5f;
  }
#pragma endscop


}
