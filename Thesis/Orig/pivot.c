// Data set size
#define N 100 // 32, 500, 1000, 2000, 4000

//kernal from MIT Gauss Pivot: forward reduction part
void kernel_pivot(int k,
		  int n,		  
		  float A[2*N][2*N])  
{
  int i,j;

  #pragma scop
  for (i=k+1; i<=n; i++){
    for (j=k+1; j<=n; j++){
      #pragma HLS PIPELINE
      A[i][j] = A[i][j] - A[k][j] * A[i][k] / A[k][k];
    }
  }
  #pragma endscop
  
}
