/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 100

void kernel_dist_itr_param(int m,
			   float A[3*N][N])
{

  int i,j;

#pragma HLS ALLOCATION instances=mul limit=2 operation

/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  if (m >= -97 && m <= 9) {
    for (int c1 = 0; c1 <= -m + 1; c1 += 1)
      for (int c3 = 0; c3 <= 1; c3 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=A_flt array inter false
        A_flt[100 * m + 200 * c1 + c3] = A_flt[100 * c1 + c3] + 0.5f;
    for (int c1 = max(0, -m + 2); c1 <= -m + 9; c1 += 1) {
      for (int c3 = c1; c3 <= min(-m + 9, m + 2 * c1 - 1); c3 += 1)
        for (int c5 = 0; c5 <= 1; c5 += 1)
          #pragma HLS PIPELINE
          #pragma HLS DEPENDENCE variable=A_flt array inter false
          A_flt[100 * m + 200 * c3 + c5] = A_flt[100 * c3 + c5] + 0.5f;
      c1 = c1 + (m + c1 - 1);
    }
    if (m <= 9)
      for (int c1 = -m + 10; c1 <= 99; c1 += 1)
        for (int c3 = 0; c3 <= 1; c3 += 1)
          #pragma HLS PIPELINE
          #pragma HLS DEPENDENCE variable=A_flt array inter false
          A_flt[100 * m + 200 * c1 + c3] = A_flt[100 * c1 + c3] + 0.5f;
  } else
    for (int c1 = 0; c1 <= 99; c1 += 1)
      for (int c3 = 0; c3 <= 1; c3 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=A_flt array inter false
        A_flt[100 * m + 200 * c1 + c3] = A_flt[100 * c1 + c3] + 0.5f;
}

/* End Accelerated Scop */ 


}
