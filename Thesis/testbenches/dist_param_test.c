// Data set size
#define N 100

#define STEP 100

#include <stdio.h>

int main() {

  // input initialization
  int i,j,k,t;
  int check;

  int m;

  float A[2*N];
  float A_ref[2*N];

  srand(1);

  FILE *f = fopen("iter.dat", "w");
  if (!f)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  for(t=0; t<STEP; t++){

    check = 0;

    // conflict region random test
    m = rand()%(13) + 1;

    // conlfict region seperate test
    //m = t;

    //m=12;

    printf("\n===== m: %d \n", m);

    // reference init
    for (i=0; i<2*N; i++){
      A[i] = rand()%N;
      A_ref[i] = A[i];
    }

    // run reference kernel
    for (i=0; i<N; i++){
      A_ref[i+m] = A_ref[i] + 0.5f;
    }

    // run kernel
    kernel_dist_param(m, A);

    // compare
    for (i=0; i<2*N; i++){
      if (A[i] != A_ref[i]){
    	  check = check + 1;
    	  printf("*** A[%d] \n", i);
      }
    }

    fprintf(f, "%d\n", N);

    if(check!=0){
      fclose(f);
      return 1;
    }

  }

  fclose(f);
  return 0;

}
