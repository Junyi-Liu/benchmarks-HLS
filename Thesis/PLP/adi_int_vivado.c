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
/* Begin Accelerated Scop */ 
float* a11_flt = &a11;
float* a12_flt = &a12;
float* a13_flt = &a13;
float* a21_flt = &a21;
float* a22_flt = &a22;
float* a23_flt = &a23;
float* a31_flt = &a31;
float* a32_flt = &a32;
float* a33_flt = &a33;
float* du1_flt = du1;
float* du2_flt = du2;
float* du3_flt = du3;
float* sig_flt = &sig;
float* u1_flt = u1;
float* u2_flt = u2;
float* u3_flt = u3;
{
  if ((n <= 23 && n >= 2) || (nl2 == nl1 && n >= 24)) {
    for (int c1 = 1; c1 <= 3; c1 += 1)
      for (int c3 = 1; c3 < n; c3 += 1) {
        #pragma HLS PIPELINE
        du1_flt[c3] = u1_flt[10000 * nl1 + c1 + 100 * c3 + 100] - u1_flt[10000 * nl1 + c1 + 100 * c3 - 100];
        du2_flt[c3] = u2_flt[10000 * nl1 + c1 + 100 * c3 + 100] - u2_flt[10000 * nl1 + c1 + 100 * c3 - 100];
        du3_flt[c3] = u3_flt[10000 * nl1 + c1 + 100 * c3 + 100] - u3_flt[10000 * nl1 + c1 + 100 * c3 - 100];
        u1_flt[10000 * nl2 + c1 + 100 * c3] = u1_flt[10000 * nl1 + c1 + 100 * c3] + a11_flt[0] * du1_flt[c3] + a12_flt[0] * du2_flt[c3] + a13_flt[0] * du3_flt[c3] + sig_flt[0] * (u1_flt[10000 * nl1 + c1 + 100 * c3 + 1] - 2.0f * u1_flt[10000 * nl1 + c1 + 100 * c3] + u1_flt[10000 * nl1 + c1 + 100 * c3 - 1]);
        u2_flt[10000 * nl2 + c1 + 100 * c3] = u2_flt[10000 * nl1 + c1 + 100 * c3] + a21_flt[0] * du1_flt[c3] + a22_flt[0] * du2_flt[c3] + a23_flt[0] * du3_flt[c3] + sig_flt[0] * (u2_flt[10000 * nl1 + c1 + 100 * c3 + 1] - 2.0f * u2_flt[10000 * nl1 + c1 + 100 * c3] + u2_flt[10000 * nl1 + c1 + 100 * c3 - 1]);
        u3_flt[10000 * nl2 + c1 + 100 * c3] = u3_flt[10000 * nl1 + c1 + 100 * c3] + a31_flt[0] * du1_flt[c3] + a32_flt[0] * du2_flt[c3] + a33_flt[0] * du3_flt[c3] + sig_flt[0] * (u3_flt[10000 * nl1 + c1 + 100 * c3 + 1] - 2.0f * u3_flt[10000 * nl1 + c1 + 100 * c3] + u3_flt[10000 * nl1 + c1 + 100 * c3 - 1]);
      }
  } else
    for (int c1 = 1; c1 <= 3; c1 += 1)
      for (int c3 = 1; c3 < n; c3 += 1) {
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=a11_flt array inter false
        #pragma HLS DEPENDENCE variable=a12_flt array inter false
        #pragma HLS DEPENDENCE variable=a13_flt array inter false
        #pragma HLS DEPENDENCE variable=a21_flt array inter false
        #pragma HLS DEPENDENCE variable=a22_flt array inter false
        #pragma HLS DEPENDENCE variable=a23_flt array inter false
        #pragma HLS DEPENDENCE variable=a31_flt array inter false
        #pragma HLS DEPENDENCE variable=a32_flt array inter false
        #pragma HLS DEPENDENCE variable=a33_flt array inter false
        #pragma HLS DEPENDENCE variable=du1_flt array inter false
        #pragma HLS DEPENDENCE variable=du2_flt array inter false
        #pragma HLS DEPENDENCE variable=du3_flt array inter false
        #pragma HLS DEPENDENCE variable=sig_flt array inter false
        #pragma HLS DEPENDENCE variable=u1_flt array inter false
        #pragma HLS DEPENDENCE variable=u2_flt array inter false
        #pragma HLS DEPENDENCE variable=u3_flt array inter false
        du1_flt[c3] = u1_flt[10000 * nl1 + c1 + 100 * c3 + 100] - u1_flt[10000 * nl1 + c1 + 100 * c3 - 100];
        du2_flt[c3] = u2_flt[10000 * nl1 + c1 + 100 * c3 + 100] - u2_flt[10000 * nl1 + c1 + 100 * c3 - 100];
        du3_flt[c3] = u3_flt[10000 * nl1 + c1 + 100 * c3 + 100] - u3_flt[10000 * nl1 + c1 + 100 * c3 - 100];
        u1_flt[10000 * nl2 + c1 + 100 * c3] = u1_flt[10000 * nl1 + c1 + 100 * c3] + a11_flt[0] * du1_flt[c3] + a12_flt[0] * du2_flt[c3] + a13_flt[0] * du3_flt[c3] + sig_flt[0] * (u1_flt[10000 * nl1 + c1 + 100 * c3 + 1] - 2.0f * u1_flt[10000 * nl1 + c1 + 100 * c3] + u1_flt[10000 * nl1 + c1 + 100 * c3 - 1]);
        u2_flt[10000 * nl2 + c1 + 100 * c3] = u2_flt[10000 * nl1 + c1 + 100 * c3] + a21_flt[0] * du1_flt[c3] + a22_flt[0] * du2_flt[c3] + a23_flt[0] * du3_flt[c3] + sig_flt[0] * (u2_flt[10000 * nl1 + c1 + 100 * c3 + 1] - 2.0f * u2_flt[10000 * nl1 + c1 + 100 * c3] + u2_flt[10000 * nl1 + c1 + 100 * c3 - 1]);
        u3_flt[10000 * nl2 + c1 + 100 * c3] = u3_flt[10000 * nl1 + c1 + 100 * c3] + a31_flt[0] * du1_flt[c3] + a32_flt[0] * du2_flt[c3] + a33_flt[0] * du3_flt[c3] + sig_flt[0] * (u3_flt[10000 * nl1 + c1 + 100 * c3 + 1] - 2.0f * u3_flt[10000 * nl1 + c1 + 100 * c3] + u3_flt[10000 * nl1 + c1 + 100 * c3 - 1]);
      }
}

/* End Accelerated Scop */ 
  
}
