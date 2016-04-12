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
/* Begin Accelerated Scop */ 
float* L_flt = L;
float* x_flt = x;
{
  if (m >= lb && ub >= m + 1) {
    for (int c1 = lb; c1 <= ub; c1 += 1)
      #pragma HLS PIPELINE
      x_flt[c1] = x_flt[c1] - L_flt[m + 100 * c1] * x_flt[m];
  } else
    for (int c1 = lb; c1 <= ub; c1 += 1)
      #pragma HLS PIPELINE
      #pragma HLS DEPENDENCE variable=L_flt array inter false
      #pragma HLS DEPENDENCE variable=x_flt array inter false
      x_flt[c1] = x_flt[c1] - L_flt[m + 100 * c1] * x_flt[m];
}

/* End Accelerated Scop */ 

}
