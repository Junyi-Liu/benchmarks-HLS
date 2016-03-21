/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 100

#define LB 20

void kernel_typ_loop(int m,
		     int n,
		     float A[2*N][2*N])
{

  int i;
  int j;
  int k;



#pragma HLS ALLOCATION instances=mul limit=4 operation

  // 2D nested loop
/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  if (m + 40 >= n && n >= m + 21 && n + m >= 21) {
    if (n >= m + 21 && m + 40 >= n && n + m >= 21)
      for (int c1 = 100; c1 <= 199; c1 += 1)
        for (int c3 = 20; c3 < n; c3 += 1)
          #pragma HLS PIPELINE
          #pragma HLS DEPENDENCE variable=A_flt array inter false
          #pragma HLS LOOP_FLATTEN off
          A_flt[200 * c1 + c3] = A_flt[m + 200 * c1 + c3 - 200] + c1;
  } else
    for (int c1 = 100; c1 <= 199; c1 += 1)
      for (int c3 = 20; c3 < n; c3 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=A_flt array inter false
        A_flt[200 * c1 + c3] = A_flt[m + 200 * c1 + c3 - 200] + c1;
}

/* End Accelerated Scop */ 



}
