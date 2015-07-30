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
  #pragma scop
  for (j=N; j<2*N; j++){
    for (i=LB; i<n; i++){
      #pragma HLS PIPELINE
	  //#pragma HLS LOOP_FLATTEN off
      A[j][i] = A[j-1][i+m] + j;
    }
  }
  #pragma endscop

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
