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

#pragma scop
  for (row = 0; row < rows + 1; row++){
    for (col = 0; col-1 < cols; col++){
      #pragma HLS PIPELINE
	  //#pragma HLS LOOP_FLATTEN off
      //if (col < cols) {
        buff_B[2][col] = buff_A[1][col]; // read from buff_A[1][col]
        buff_A[1][col] = buff_B[0][col]; // write to buff_A[1][col]
        //buff_B[1][col] = buff_B[0][col];
        //temp = buff_A[0][col];
	//}
    }
  } 
#pragma endscop

}
 
