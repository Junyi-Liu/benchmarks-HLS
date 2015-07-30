// Data set size
#define N 100 // 32, 500, 1000, 2000, 4000

//kernal from MIT Gauss Pivot: forward reduction part
void kernel_pivot(int k,
		  int n,		  
		  float A[2*N][2*N])  
{
  int i,j;
  //int tmp;
  
//#pragma HLS ALLOCATION instances=fdiv limit=1 operation
//#pragma HLS ALLOCATION instances=fmul limit=1 operation
//#pragma HLS ALLOCATION instances=fsub limit=1 operation
//#pragma HLS ALLOCATION instances=mul limit=2 operation

/* #pragma scop */
/*   for (i = 0; i < N; i++){ */
/*     #pragma HLS PIPELINE */
/*     tmp = A[k][i]; */
/*     A[k][i] = A[p][i]; */
/*     A[p][i] = tmp;  */
/*   }  */
/* #pragma endscop */

  #pragma scop
  for (i=k+1; i<=n; i++){
    for (j=k+1; j<=n; j++){
      #pragma HLS PIPELINE
	  //#pragma HLS LOOP_FLATTEN off
      A[i][j] = A[i][j] - A[k][j] * A[i][k] / A[k][k];
    }
  }
  #pragma endscop
  
}
