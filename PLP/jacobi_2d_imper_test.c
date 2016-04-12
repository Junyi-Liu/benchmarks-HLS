// Data set size
#define N 300 // 32, 500, 1000, 2000, 4000

#define _PB_N 200

#define STEP 1000

int main() {

  // input initialization
  int i,j,k;
  int check = 0;

  int n = 0;

  int m;
  int m_list[STEP] = {20,1,19} ;

  float A[N][N];
  float A_ref[N][N];
  float diff;

  for(k=0; k<STEP; k++){
    
    //m = m_list[k];

	// full test
    m = rand()%(N-100) -100;

    // conflit region test
//	do{
//		m = rand()%(N-100) -100;
//	}
//	while(!((m <= -1 && m >= -19) || (m <= 19 && m >= 1)));


    printf("\n===== m: %d \n", m);

    // reference init
    for(i = 0; i<N; i++){
      for(j = 0; j<N; j++){
	A[i][j] = rand()%N;
	A_ref[i][j] = A[i][j];
      }    
    }

    // run reference kernel
    for (i = 100; i < _PB_N - 1; i++){
      for (j = 100; j < _PB_N - 1; j++)
	A_ref[i][j] = 0.2f * (A_ref[i][j] + A_ref[i][j-m] + A_ref[i][m+j] + A_ref[m+i][j] + A_ref[i-m][j]);
    } 

    // run kernel
    kernel_jacobi_2d_imper(n, m, A);

    // compare
    printf("===================Compare: m[%d] ==================\n", k);
    for(i = 0; i<N; i++){
      for(j = 0; j<N; j++){
	diff = fabs(A[i][j]-A_ref[i][j]);	
	if (diff > pow(2, -23)){
//	  printf("-------------------------\n");
//	  //printf("A[%d][%d] difference: %e \n", i, j, diff);
//	  printf("A[%d][%d]: %e \n", i, j, A[i][j]);
//	  printf("A_ref[%d][%d] : %e \n", i, j, A_ref[i][j]);
	  check = check + 1;
	}
      }
    }  

    printf("check value: %d \n", check);

  }

  return check;

}
