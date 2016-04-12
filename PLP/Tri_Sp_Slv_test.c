// Data set size
#define N 100

#define STEP 1000

#include <stdio.h>

int main() {

  // input initialization
  int i,j,k,t;
  int check;

  int n = 0;

  int m;
  int m_list[STEP] = {1,50} ;

  int lb;
  int ub;

  float x[N];
  float x_ref[N];

  float L[N][N];

  srand(1);

  FILE *f = fopen("iter.dat", "w");
  if (!f)
  {
      printf("Error opening file!\n");
      exit(1);
  }


  for(t=0; t<STEP; t++){

	check = 0;
    
    //m = m_list[t];
	ub = rand()%(N-1) +1;
	lb = rand()%ub;

	// for full region
    m = rand()%N;

    // for conflict region
    //m = rand()%(ub-lb) + lb;

    printf("\n===== lb: %d ", lb);
    printf("\n===== ub: %d ", ub);
    printf("\n===== m: %d \n", m);

    // reference init
    for (i=0; i<N; i++){
      x[i] = rand()%N;
      x_ref[i] = x[i];
    }

    for (j=0; j<N; j++){
      for (i=0; i<N; i++){
	L[j][i] = rand()%N;
      }
    }

    // run reference kernel
    for(i = lb; i<=ub ; i++){
      x_ref[i] = x_ref[i] - L[i][m]*x_ref[m];
    }

    // run kernel
    kernel_Tri_Sp_Slv(m, lb, ub, x, L);

    // compare
    for (i=0; i<N; i++){
      if (x[i] != x_ref[i]) check = check + 1;
    }

    fprintf(f, "%d\n", ub-lb+1);

    if(check!=0){
    	fclose(f);
    	return 1;
    }

    }

  fclose(f);
  return 0;

  }

