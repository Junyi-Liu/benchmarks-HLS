/* Begin Extra Functions Definition */ 
int min(int a, int b) { return (a<b) ? a : b;} 
int max(int a, int b) { return (a>b) ? a : b;} 
/* End Extra Functions Definition */ 

#define N 128

void kernel_floyd_warshall(int n,
			   float path[N][N])
{
  int i, j, k;

/* Begin Accelerated Scop */ 
float* path_flt = path;
{
  for (int c1 = 0; c1 <= 127; c1 += 1)
    for (int c3 = 0; c3 <= 127; c3 += 1) {
      for (int c4 = 0; c4 <= c1; c4 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=path_flt array inter false
        path_flt[128 * c3 + c4] = path_flt[128 * c3 + c4] < path_flt[c1 + 128 * c3] + path_flt[128 * c1 + c4] ? path_flt[128 * c3 + c4] : path_flt[c1 + 128 * c3] + path_flt[128 * c1 + c4];
      for (int c4 = c1 + 1; c4 <= 127; c4 += 1)
        #pragma HLS PIPELINE
        #pragma HLS DEPENDENCE variable=path_flt array inter false
        path_flt[128 * c3 + c4] = path_flt[128 * c3 + c4] < path_flt[c1 + 128 * c3] + path_flt[128 * c1 + c4] ? path_flt[128 * c3 + c4] : path_flt[c1 + 128 * c3] + path_flt[128 * c1 + c4];
    }
}

/* End Accelerated Scop */ 

  return;
 
}
