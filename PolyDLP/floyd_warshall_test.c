#define N 128


int main() {

  // input initialization
  int i,j,k,t;
  int check = 0;

  int n = 0;
  
  float path[N][N];
  float path_ref[N][N];

  // reference init
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      path[i][j] = rand()%N;
      path_ref[i][j] = path[i][j];
    }
  }

  // run reference kernel
  for(k = 0; k < N; k++){
    for(i = 0; i < N; i++)
      for(j = 0; j < N; j++)
	path_ref[i][j] = path_ref[i][j] < path_ref[i][k] + path_ref[k][j] ? path_ref[i][j] : path_ref[i][k] + path_ref[k][j];
  }

  // run kernel
  kernel_floyd_warshall(n, path);

  // compare
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      if (path[i][j] != path_ref[i][j]) check = check + 1;
    }
  }
  
  return check;

}
