// Data set size
#define N 100
#define NL 3

#define STEP 100

#include <stdio.h>

int main() {

  // input initialization
  int i,kx,ky,t;
  int check = 0;

  int n;
  int n_list[STEP] = {24,24,10} ;
  
  int nl1;
  int nl1_list[STEP] = {1,1,2} ;

  int nl2;
  int nl2_list[STEP] = {1,2,1} ;

  float sig = 1.0f;
  float a11 = 1.0f; float a12 = 1.0f; float a13 = 1.0f;
  float a21 = 1.0f; float a22 = 1.0f; float a23 = 1.0f;
  float a31 = 1.0f; float a32 = 1.0f; float a33 = 1.0f;
  
  float du1[N];
  float du2[N];
  float du3[N];		
  float u1[NL][N][N];
  float u2[NL][N][N];
  float u3[NL][N][N];  

  float du1_ref[N];
  float du2_ref[N];
  float du3_ref[N];		
  float u1_ref[NL][N][N];
  float u2_ref[NL][N][N];
  float u3_ref[NL][N][N];  

  // test loop
  for(t=0; t<STEP; t++){

	// specific test
//    n = n_list[t];
//    nl1 = nl1_list[t];
//    nl2 = nl2_list[t];
    
    // random test
    n = rand()%(44) +2; //rand()%(22) +2;
    nl1 = rand()%NL;
    nl2 = rand()%NL;

    // reference init
    for (ky=0; ky<N; ky++){
      du1[ky] = rand()%N;
      du1_ref[ky] = du1[ky];      

      du2[ky] = rand()%N;
      du2_ref[ky] = du2[ky];
      
      du3[ky] = rand()%N;
      du3_ref[ky] = du3[ky];            
    }
    
    for (i=0; i<NL; i++){
      for (kx=0; kx<N; kx++){
	for (ky=0; ky<N; ky++){
	  u1[i][ky][kx] = rand()%N;
	  u1_ref[i][ky][kx] = u1[i][ky][kx];
	  
	  u2[i][ky][kx] = rand()%N;
	  u2_ref[i][ky][kx] = u2[i][ky][kx];
	  
	  u3[i][ky][kx] = rand()%N;
	  u3_ref[i][ky][kx] = u3[i][ky][kx];	  
	}
      }
    }

    // run reference kernel
    for ( kx=1 ; kx<4 ; kx++ ){
      for ( ky=1 ; ky<n ; ky++ ) {
	du1_ref[ky] = u1_ref[nl1][ky+1][kx] - u1_ref[nl1][ky-1][kx];
	du2_ref[ky] = u2_ref[nl1][ky+1][kx] - u2_ref[nl1][ky-1][kx];
	du3_ref[ky] = u3_ref[nl1][ky+1][kx] - u3_ref[nl1][ky-1][kx];
	u1_ref[nl2][ky][kx]=
	  u1_ref[nl1][ky][kx]+a11*du1_ref[ky]+a12*du2_ref[ky]+a13*du3_ref[ky] + sig*
	  (u1_ref[nl1][ky][kx+1]-2.0f*u1_ref[nl1][ky][kx]+u1_ref[nl1][ky][kx-1]);
	u2_ref[nl2][ky][kx]=
	  u2_ref[nl1][ky][kx]+a21*du1_ref[ky]+a22*du2_ref[ky]+a23*du3_ref[ky] + sig*
	  (u2_ref[nl1][ky][kx+1]-2.0f*u2_ref[nl1][ky][kx]+u2_ref[nl1][ky][kx-1]);
	u3_ref[nl2][ky][kx]=
	  u3_ref[nl1][ky][kx]+a31*du1_ref[ky]+a32*du2_ref[ky]+a33*du3_ref[ky] + sig*
	  (u3_ref[nl1][ky][kx+1]-2.0f*u3_ref[nl1][ky][kx]+u3_ref[nl1][ky][kx-1]);
      }
    }
    
    // run kernel
    kernel_adi_int(n, nl1, nl2, du1, du2, du3, u1, u2, u3);

    // compare
    for (ky=0; ky<N; ky++){
      if (du1[ky] != du1_ref[ky]) {
	check = check + 1;
	printf("du1[%d]: %e \n", ky,du1[ky]);
	printf("du1_ref[%d]: %e \n", ky,du1_ref[ky]);
      }
      if (du2[ky] != du2_ref[ky]) {
	check = check + 1;
	printf("du2[%d]: %e \n", ky,du2[ky]);
	printf("du2_ref[%d]: %e \n", ky,du2_ref[ky]);
      }
      if (du3[ky] != du3_ref[ky]) {
	check = check + 1;
	printf("du3[%d]: %e \n", ky,du3[ky]);
	printf("du3_ref[%d]: %e \n", ky,du3_ref[ky]);	
      }
    }

    for (i=0; i<NL; i++){
      for (kx=0; kx<N; kx++){
	for (ky=0; ky<N; ky++){
	  if (u1[i][ky][kx] != u1_ref[i][ky][kx]) {
	    check = check + 1;
	    printf("u1[%d][%d][%d]: %e \n", i,ky,kx,u1[i][ky][kx]);
	    printf("u1_ref[%d][%d][%d] : %e \n", i,ky,kx,u1_ref[i][ky][kx]);
	  }
	  if (u2[i][ky][kx] != u2_ref[i][ky][kx]) {
	    check = check + 1;
	    printf("u2[%d][%d][%d]: %e \n", i,ky,kx,u2[i][ky][kx]);
	    printf("u2_ref[%d][%d][%d] : %e \n", i,ky,kx,u2_ref[i][ky][kx]);	    
	  }
	  if (u3[i][ky][kx] != u3_ref[i][ky][kx]) {
	    check = check + 1;
	    printf("u3[%d][%d][%d]: %e \n", i,ky,kx,u3[i][ky][kx]);
	    printf("u3_ref[%d][%d][%d] : %e \n", i,ky,kx,u3_ref[i][ky][kx]);
	  }
	}
      }
    }
    
  }

  return check;

}
