#include "globals.h"

void kernel_pivot(int k, int n, float A[2*100][2*100]);
unsigned int hashFunction(int index0, int index1);


void kernel_pivot(int k, int n, float A[2*100][2*100]) {
	int i;
	int j;
	
	for(i = k + 1; i <= n + 1 - 1; i = i + 1) {
#pragma HLS PIPELINE
		const unsigned int PIPELINE_LATENCY = 19;
		int pipeline_register_0[PIPELINE_LATENCY];
		int stall;
		unsigned int shift_index;
		
		j = k + 1;
		for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
			pipeline_register_0[shift_index] = -1;
		}
		while (j <= n + 1 - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=A array inter false
			stall = 0;
			for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, j);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(k, j);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, k);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(k, k);
				pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
			}
			if (stall == 1)
				pipeline_register_0[0] = -1;
			else {
				pipeline_register_0[0] = hashFunction(i, j);
				A[i][j] = A[i][j] - A[k][j] * A[i][k] / A[k][k];
				j = j + 1;
			}
		}
	}
}

unsigned int hashFunction(int index0, int index1) {
	return concat(extractBits(index0, 0, 3), extractBits(index1, 0, 7));
	//return extractBits(index0, 0, 3) | extractBits(index1, 0, 4);
}

