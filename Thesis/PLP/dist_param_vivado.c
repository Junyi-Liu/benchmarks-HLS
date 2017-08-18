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
    for (int c1 = 0; c1 <= 99; c1 += 1)
      #pragma HLS PIPELINE
      A_flt[m + c1] = A_flt[c1] + 0.5f;
  } else
    for (int c1 = 0; c1 <= 99; c1 += 1)
      #pragma HLS PIPELINE
      #pragma HLS DEPENDENCE variable=A_flt array inter false
      A_flt[m + c1] = A_flt[c1] + 0.5f;
}

/* End Accelerated Scop */ 


}
