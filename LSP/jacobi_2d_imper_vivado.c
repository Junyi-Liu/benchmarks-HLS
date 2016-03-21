/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 300 // 32, 500, 1000, 2000, 4000

#define _PB_N 200


void kernel_jacobi_2d_imper(int n,
			    int m,
			    float A[N][N])
{
  int i, j;

#pragma HLS ALLOCATION instances=mul limit=3 operation

/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  if ((m <= -1 && m >= -19) || (m <= 19 && m >= 1)) {
    if (m <= -1 && m >= -19) {
      for (int c1 = 100; c1 <= 198; c1 += 1)
        for (int c3 = 100; c3 <= 198; c3 += 1) {
          for (int c5 = c3; c5 <= min(198, -m + c3 - 1); c5 += 1)
            #pragma HLS PIPELINE
            #pragma HLS DEPENDENCE variable=A_flt array inter false
            A_flt[300 * c1 + c5] = 0.2f * (A_flt[300 * c1 + c5] + A_flt[-m + 300 * c1 + c5] + A_flt[m + 300 * c1 + c5] + A_flt[300 * m + 300 * c1 + c5] + A_flt[-300 * m + 300 * c1 + c5]);
          c3 = c3 + (-m - 1);
        }
    } else if (m <= 19 && m >= 1)
      for (int c1 = 100; c1 <= 198; c1 += 1)
        for (int c3 = 100; c3 <= 198; c3 += 1) {
          for (int c5 = c3; c5 <= min(198, m + c3 - 1); c5 += 1)
            #pragma HLS PIPELINE
            #pragma HLS DEPENDENCE variable=A_flt array inter false
            A_flt[300 * c1 + c5] = 0.2f * (A_flt[300 * c1 + c5] + A_flt[-m + 300 * c1 + c5] + A_flt[m + 300 * c1 + c5] + A_flt[300 * m + 300 * c1 + c5] + A_flt[-300 * m + 300 * c1 + c5]);
          c3 = c3 + (m - 1);
        }
  } else
    for (int c1 = 100; c1 <= 198; c1 += 1)
      for (int c3 = 100; c3 <= 198; c3 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=A_flt array inter false
        A_flt[300 * c1 + c3] = 0.2f * (A_flt[300 * c1 + c3] + A_flt[-m + 300 * c1 + c3] + A_flt[m + 300 * c1 + c3] + A_flt[300 * m + 300 * c1 + c3] + A_flt[-300 * m + 300 * c1 + c3]);
}

/* End Accelerated Scop */ 

}


