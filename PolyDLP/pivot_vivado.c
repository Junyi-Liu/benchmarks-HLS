/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 100 // 32, 500, 1000, 2000, 4000

//kernal from MIT Gauss Pivot: forward reduction part
void kernel_pivot(int k,
		  int n,		  
		  float A[2*N][2*N])  
{
  int i,j;

/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  for (int c1 = k + 1; c1 <= n; c1 += 1)
    for (int c3 = k + 1; c3 <= n; c3 += 1)
      #pragma HLS PIPELINE
      #pragma HLS DEPENDENCE variable=A_flt array inter false
      A_flt[200 * c1 + c3] = A_flt[200 * c1 + c3] - (A_flt[200 * k + c3] * A_flt[k + 200 * c1] / A_flt[201 * k]);
}

/* End Accelerated Scop */ 
  
}
