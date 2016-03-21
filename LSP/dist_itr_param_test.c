// Data set size
#define N 100

#define STEP 1000

#include <stdio.h>

int main() {

  // input initialization
  int i,j,k,t;
  int check = 0;
  
  int m;
  int m_list[STEP] = {1,20,50} ;

  float A[3*N][N];
  float A_ref[3*N][N];

  srand(1);

  FILE *f = fopen("iter.dat", "w");
  if (!f)
  {
      printf("Error opening file!\n");
      exit(1);
  }

  for(t=0; t<STEP; t++){

    //m = m_list[t];

    m = rand()%(10);
    printf("\n===== m: %d \n", m);


    // reference init
    for (j=0; j<3*N; j++){
      for (i=0; i<N; i++){
	A[j][i] = rand()%N;
	A_ref[j][i] = A[j][i];
      }
    }

    // run reference kernel
    for (i=0; i<N; i++){
      for (j=0; j<2; j++){
	A_ref[2*i+m][j] = A_ref[i][j] + 0.5f;
      }
    }

    // run kernel
    kernel_dist_itr_param(m, A);

    // compare
    for (j=0; j<3*N; j++){
      for (i=0; i<N; i++){
	if (A[j][i] != A_ref[j][i]) check = check + 1;
      }
    }

    fprintf(f, "%d\n", N*N);

    if(check!=0){
    	fclose(f);
    	return 1;
    }

  }

  fclose(f);
  return 0;

}
