/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

// Data set size
#define N 32 // 32, 500, 1000, 2000, 4000

//kernal from xilinx vivado HLS ug902_2014.2/3/4 document page197
void kernel_row_col(int rows,
		    int cols,		  
		    float buff_A[N][N],
		    float buff_B[N][N])  
{
  int row,col;
  int temp;

//#pragma HLS ALLOCATION instances=mul limit=1 operation

/* Begin Accelerated Scop */ 
float* buff_A_flt = buff_A;
float* buff_B_flt = buff_B;
{
  if (cols <= 7 && cols >= 0 && rows >= 1) {
    if (cols <= 7 && rows >= 1)
      for (int c1 = 0; c1 <= rows; c1 += 1)
        for (int c3 = 0; c3 <= cols; c3 += 1) {
          #pragma HLS PIPELINE
          #pragma HLS DEPENDENCE variable=buff_A_flt array inter false
          #pragma HLS DEPENDENCE variable=buff_B_flt array inter false
          #pragma HLS LOOP_FLATTEN off
          buff_A_flt[c3 + 64] = buff_A_flt[c3 + 32] + 0.5f;
          buff_A_flt[c3 + 32] = buff_A_flt[c3] + 0.5f;
          buff_B_flt[c3 + 32] = buff_B_flt[c3] + 0.5f;
        }
  } else
    for (int c1 = 0; c1 <= rows; c1 += 1)
      for (int c3 = 0; c3 <= cols; c3 += 1) {
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=buff_A_flt array inter false
        #pragma HLS DEPENDENCE variable=buff_B_flt array inter false
        buff_A_flt[c3 + 64] = buff_A_flt[c3 + 32] + 0.5f;
        buff_A_flt[c3 + 32] = buff_A_flt[c3] + 0.5f;
        buff_B_flt[c3 + 32] = buff_B_flt[c3] + 0.5f;
      }
}

/* End Accelerated Scop */ 

}
 
