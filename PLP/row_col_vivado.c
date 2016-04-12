// Data set size
#define N 100 // 32, 500, 1000, 2000, 4000

//kernal from xilinx vivado HLS ug902_2014.2/3/4 document page197
void kernel_row_col(int rows,
		    int cols,		  
		    float buff_A[N][N],
		    float buff_B[N][N])  
{
  int row,col;
  int temp;

#pragma HLS ALLOCATION instances=mul limit=1 operation

/* Begin Accelerated Scop */ 
float* buff_A_flt = buff_A;
float* buff_B_flt = buff_B;
{
  if (cols <= 3 && cols >= 0 && rows >= 1) {
    for (int c1 = 0; c1 <= rows; c1 += 1)
      for (int c3 = 0; c3 <= cols; c3 += 1) {
        #pragma HLS PIPELINE
        buff_B_flt[c3 + 200] = buff_A_flt[c3 + 100];
        buff_A_flt[c3 + 100] = buff_B_flt[c3];
      }
  } else
    for (int c1 = 0; c1 <= rows; c1 += 1)
      for (int c3 = 0; c3 <= cols; c3 += 1) {
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=buff_A_flt array inter false
        #pragma HLS DEPENDENCE variable=buff_B_flt array inter false
        buff_B_flt[c3 + 200] = buff_A_flt[c3 + 100];
        buff_A_flt[c3 + 100] = buff_B_flt[c3];
      }
}

/* End Accelerated Scop */ 

}
 
