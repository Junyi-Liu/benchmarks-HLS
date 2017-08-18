/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 100

void kernel_dist_param(int m,
		     float A[2*N])
{

  int i;

/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  if (m >= 1 && m <= 13) {
    if (m <= 13 && m >= 1)
      for (int c1 = 0; c1 <= 99; c1 += 1) {
        for (int c3 = c1; c3 <= min(99, m + c1 - 1); c3 += 1)
          #pragma HLS PIPELINE
          #pragma HLS DEPENDENCE variable=A_flt array inter false
          A_flt[m + c3] = A_flt[c3] + 0.5f;
        c1 = c1 + (m - 1);
      }
  } else
    for (int c1 = 0; c1 <= 99; c1 += 1)
      #pragma HLS PIPELINE
      #pragma HLS DEPENDENCE variable=A_flt array inter false
      A_flt[m + c1] = A_flt[c1] + 0.5f;
}

/* End Accelerated Scop */ 


}
