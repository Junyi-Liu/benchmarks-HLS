// Data set size
#define N 100 // 

void kernel_Tri_Sp_Slv(int m,
		       int lb,
		       int ub,
		       float x[N],
		       float L[N][N])
{
  int i;
  float t;

#pragma HLS ALLOCATION instances=mul limit=1 operation
  
  // x[i] = x[i] - L[i][j] * x[j], i>j
#pragma scop
  for(i = lb; i<=ub ; i++){
    #pragma HLS PIPELINE
    x[i] = x[i] - L[i][m]*x[m];
  }
#pragma endscop

}
