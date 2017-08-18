#include "globals.h"

void kernel_floyd_warshall(int n, float path[128][128]);
unsigned int hashFunction(int index0, int index1);


void kernel_floyd_warshall(int n, float path[128][128]) {
	int i;
	int j;
	int k;
	
	for(k = 0; k <= 128 - 1; k = k + 1) {
		for(i = 0; i <= 128 - 1; i = i + 1) {
			const unsigned int PIPELINE_LATENCY = 10;
			int pipeline_register_0[PIPELINE_LATENCY];
			int stall;
			unsigned int shift_index;
			
			j = 0;
			for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
				pipeline_register_0[shift_index] = -1;
			}
			while (j <= 128 - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=path array inter false
				stall = 0;
				//path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
				for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
					stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, j);
					stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, k);
					stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(k, j);
					stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, j);
					stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, k);
					stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(k, j);
					pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
				}
				if (stall == 1)
					pipeline_register_0[0] = -1;
				else {
					pipeline_register_0[0] = hashFunction(i, j);
					path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
					j = j + 1;
				}
			}
		}
	}
	return ;
}

unsigned int hashFunction(int index0, int index1) {
	return concat(extractBits(index0, 0, 1), extractBits(index1, 0, 3));
}

