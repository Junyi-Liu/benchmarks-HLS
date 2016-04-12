// Data set size
#define N 100

#define LB 20

#define STEP 1000

#include <stdio.h>

int main() {

  // input initialization
  int i,j,k,t;
  int check;

  int n;
  int n_list[STEP] = {LB+20, LB+10, N, LB+1};//{LB+20, LB+10, N, LB+1} ;
  
  int m;
  int m_list[STEP] = {10, 0, -1, -15}; //{10, 0, -1, -15} ;

  float A[2*N][2*N];
  float A_ref[2*N][2*N];

  srand(1);

  FILE *f = fopen("iter.dat", "w");
  if (!f)
  {
      printf("Error opening file!\n");
      exit(1);
  }

  for(t=0; t<STEP; t++){

	check = 0;

    //n = n_list[t];
    //m = m_list[t];

	// full test
	n = rand()%(2*N-LB) + LB +1;
	m = rand()%(2*N-n+LB +1) - LB;

	// conflict region test
//	do{
//		n = rand()%(2*N-LB) + LB +1;
//		m = rand()%(2*N-n+LB +1) - LB;
//	}
//	while(!(m + 40 >= n && n >= m + 21 && n + m >= 21));

    printf("\n===== n: %d \t| m: %d \n", n, m);

    // reference init
    for (j=0; j<2*N; j++){
      for (i=0; i<2*N; i++){
	A[j][i] = rand()%N;
	A_ref[j][i] = A[j][i];
      }
    }

    // run reference kernel
    for (j=N; j<2*N; j++){
      for (i=LB; i<n; i++){
	A_ref[j][i] = A_ref[j-1][i+m] + j;
      }
    }

    // run kernel
    kernel_typ_loop(m, n, A);

    // compare
    for (j=0; j<2*N; j++){
      for (i=0; i<2*N; i++){
	if (A[j][i] != A_ref[j][i]) check = check + 1;
      }
    }

    fprintf(f, "%d\n", N*(n-LB));

    if(check!=0){
    	fclose(f);
    	return 1;
    }

  }

  fclose(f);
  return 0;

}
