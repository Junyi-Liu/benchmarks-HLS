// Data set size
#define N 100

#define STEP 1000

#include <stdio.h>

int main() {

  // input initialization
  int i,j,t;
  int check;

  int n;
  int n_list[STEP] = {100, 200} ;
  
  int k;
  int k_list[STEP] = {0, 100} ;

  float A[2*N][2*N];
  float A_ref[2*N][2*N];

  srand(1);

  FILE *f = fopen("iter.dat", "w");
  if (!f)
  {
      printf("Error opening file!\n");
      return 1;
  }

  for(t=0; t<STEP; t++){

	check = 0;

    //n = n_list[t];
    //k = k_list[t];

    n = rand()%(2*N-1) +1;
    k = rand()%(n);
	//n=275;
	//k=72;
    printf("\n===== n: %d \t| k: %d \n", n, k);

    // reference init
    for (i=0; i<2*N; i++){
      for (j=0; j<2*N; j++){
	A[i][j] = rand()%N +1;
	A_ref[i][j] = A[i][j];
      }
    }

    // run reference kernel
    for (i=k+1; i<=n; i++){
      for (j=k+1; j<=n; j++){
	A_ref[i][j] = A_ref[i][j] - A_ref[k][j] * A_ref[i][k] / A_ref[k][k];
      }
    }

    // run kernel
    kernel_pivot(k, n, A);

    // compare
    for (i=0; i<2*N; i++){
      for (j=0; j<2*N; j++){	
	if (A[i][j] != A_ref[i][j]) check = check + 1;
      }
    }

    fprintf(f, "%d\n",(n-k)*(n-k));

    if(check!=0){
    	fclose(f);
    	return 1;
    }

  }

  fclose(f);
  return 0;

}
