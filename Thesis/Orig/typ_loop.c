// Data set size
#define N 100

#define LB 20

void kernel_typ_loop(int m,
		     int n,
		     float A[2*N][2*N])
{

  int i;
  int j;
  int k;

#pragma HLS ALLOCATION instances=mul limit=4 operation

  // 2D nested loop
  #pragma scop
  for (j=N; j<2*N; j++){
    for (i=LB; i<n; i++){
      #pragma HLS PIPELINE
      A[j][i] = A[j-1][i+m] + 0.5f;
    }
  }
  #pragma endscop

}
