/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 100

void kernel_dist_itr(float A[2*N])
{

  int i;

/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  for (int c1 = 0; c1 <= 1; c1 += 1)
    #pragma HLS PIPELINE
    #pragma HLS DEPENDENCE variable=A_flt array inter false
    A_flt[2 * c1] = A_flt[c1] + 0.5f;
  for (int c1 = 2; c1 <= 13; c1 += 1) {
    for (int c3 = c1; c3 <= min(13, 2 * c1 - 1); c3 += 1)
      #pragma HLS PIPELINE
      #pragma HLS DEPENDENCE variable=A_flt array inter false
      A_flt[2 * c3] = A_flt[c3] + 0.5f;
    c1 = c1 + (c1 - 1);
  }
  for (int c1 = 14; c1 <= 99; c1 += 1)
    #pragma HLS PIPELINE
    #pragma HLS DEPENDENCE variable=A_flt array inter false
    A_flt[2 * c1] = A_flt[c1] + 0.5f;
}

/* End Accelerated Scop */ 


}
