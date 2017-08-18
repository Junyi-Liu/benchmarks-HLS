// Data set size
#define N 32

#define STEP 100

#include <stdio.h>

int main() {

  // input initialization
  int i,j,k,t;
  int check;

  int rows;
  int rows_list[STEP] = {1,10} ;

  int cols;
  int cols_list[STEP] = {0,10} ;
  
  float buff_A[N][N];
  float buff_B[N][N];

  float buff_A_ref[N][N];
  float buff_B_ref[N][N];

  srand(1);

  FILE *f = fopen("iter.dat", "w");
  if (!f)
  {
      printf("Error opening file!\n");
      return 1;
  }

  for(t=0; t<STEP; t++){

	check = 0;
    
	// selected
    //rows = rows_list[t];
    //cols = cols_list[t];
    
	// full
//    rows = rand()%N;
//    cols = rand()%N;

    // conflict region
    rows = rand()%N+1;
    cols = rand()%7+1;

    printf("\n=====[%d] rows: %d \t| cols: %d \n", t+1, rows, cols);

    // reference init
    for (j=0; j<N; j++){
      for (i=0; i<N; i++){
	buff_A[j][i] = rand()%N+1;
	buff_A_ref[j][i] = buff_A[j][i];
	buff_B[j][i] = rand()%N+1;
	buff_B_ref[j][i] = buff_B[j][i];
      }
    }

    // run reference kernel
    int row,col;
    float temp;
    for (row = 0; row < rows + 1; row++){
      for (col = 0; col-1 < cols; col++){
//        buff_B_ref[2][col] = buff_A_ref[1][col]; // read from buff_A[1][col]
//        buff_A_ref[1][col] = buff_B_ref[0][col]; // write to buff_A[1][col]
        buff_A_ref[2][col] = buff_A_ref[1][col]+0.5f; // read from buff_A[1][col]
        buff_A_ref[1][col] = buff_A_ref[0][col]+0.5f; // write to buff_A[1][col]
        buff_B_ref[1][col] = buff_B_ref[0][col]+0.5f;
//        temp = buff_A[0][col];
      }
    } 
    
    // run kernel
    kernel_row_col(rows, cols, buff_A, buff_B);

    // compare
    for (j=0; j<3; j++){
      for (i=0; i<N; i++){
	if(buff_A[j][i] != buff_A_ref[j][i] || buff_B[j][i] != buff_B_ref[j][i]){
	  check = check + 1;
	}
      }
    }

    fprintf(f, "%d\n",(cols+1)*(rows+1));

    if(check!=0){
    	fclose(f);
    	return 1;
    }

  }

  fclose(f);
  return 0;

}
