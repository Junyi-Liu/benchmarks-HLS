// Data set size
#define N 100
#define NL 3

void kernel_adi_int(int n,
			int nl1,
			int nl2,			
			float du1[N],
			float du2[N],
			float du3[N],			
			float u1[NL][N][N],
			float u2[NL][N][N],
			float u3[NL][N][N])
{
  int kx;
  int ky;

  float sig = 1.0f;
  float a11 = 1.0f; float a12 = 1.0f; float a13 = 1.0f;
  float a21 = 1.0f; float a22 = 1.0f; float a23 = 1.0f;
  float a31 = 1.0f; float a32 = 1.0f; float a33 = 1.0f;
  
//#pragma HLS ALLOCATION instances=mul limit=2 operation

  // ADI integration
  // Kernal 8 in livermorec
  #pragma scop
  for ( kx=1 ; kx<4 ; kx++ ){
    for ( ky=1 ; ky<n ; ky++ ) {
      #pragma HLS PIPELINE
      du1[ky] = u1[nl1][ky+1][kx] - u1[nl1][ky-1][kx];
      du2[ky] = u2[nl1][ky+1][kx] - u2[nl1][ky-1][kx];
      du3[ky] = u3[nl1][ky+1][kx] - u3[nl1][ky-1][kx];
      u1[nl2][ky][kx]=
	u1[nl1][ky][kx]+a11*du1[ky]+a12*du2[ky]+a13*du3[ky] + sig*
	(u1[nl1][ky][kx+1]-2.0f*u1[nl1][ky][kx]+u1[nl1][ky][kx-1]);
      u2[nl2][ky][kx]=
	u2[nl1][ky][kx]+a21*du1[ky]+a22*du2[ky]+a23*du3[ky] + sig*
	(u2[nl1][ky][kx+1]-2.0f*u2[nl1][ky][kx]+u2[nl1][ky][kx-1]);
      u3[nl2][ky][kx]=
	u3[nl1][ky][kx]+a31*du1[ky]+a32*du2[ky]+a33*du3[ky] + sig*
	(u3[nl1][ky][kx+1]-2.0f*u3[nl1][ky][kx]+u3[nl1][ky][kx-1]);
    }
  }
  #pragma endscop
  
}
