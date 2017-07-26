#define N 128

void kernel_floyd_warshall(int n,
			   float path[N][N])
{
  int i, j, k;

#pragma scop
  for(k = 0; k < N; k++){
    for(i = 0; i < N; i++)
      for(j = 0; j < N; j++)
#pragma HLS PIPELINE
	path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
  }
#pragma endscop

  return;
 
}
