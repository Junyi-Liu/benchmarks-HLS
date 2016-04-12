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

  // 1D simple loop
/* #pragma scop */
/*   for (i=N; i<2*N; i++){ */
/*     A[i+m] = A[i] + i; */
/*   } */
/* #pragma endscop */

#pragma HLS ALLOCATION instances=mul limit=4 operation

  // 2D nested loop
/* Begin Accelerated Scop */ 
float* A_flt = A;
{
  if (m + 40 >= n && n >= m + 21 && n + m >= 21) {
    for (int c1 = 100; c1 <= 199; c1 += 1)
      for (int c3 = 20; c3 < n; c3 += 1)
        #pragma HLS PIPELINE
        A_flt[200 * c1 + c3] = A_flt[m + 200 * c1 + c3 - 200] + c1;
  } else
    for (int c1 = 100; c1 <= 199; c1 += 1)
      for (int c3 = 20; c3 < n; c3 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=A_flt array inter false
        A_flt[200 * c1 + c3] = A_flt[m + 200 * c1 + c3 - 200] + c1;
}

/* End Accelerated Scop */ 

  // 3D nested loop
  /* #pragma scop */
  /* for (k=N; k<2*N; k++){ */
  /*   for (j=0; j<N; j++){ */
  /*     for (i=LB; i<N; i++){ */
  /* 	# pragma HLS PIPELINE */
  /* 	A[k][j][i-m] = A[k][j][i] + j; */
  /*     } */
  /*   } */
  /* } */
  /* #pragma endscop */

}
