#include "globals.h"

void kernel_dist_itr_param(int m, float A[3*100][100]);
unsigned int hashFunction(int index0, int index1);


void kernel_dist_itr_param(int m, float A[3*100][100]) {
	int i;
	int j;
	

	for(i = 0; i <= 100 - 1; i = i + 1) {
		const unsigned int PIPELINE_LATENCY = 15;
		int pipeline_register_0[PIPELINE_LATENCY];
		int stall;
		unsigned int shift_index;
		
		j = 0;
		for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
			pipeline_register_0[shift_index] = -1;
		}
		while (j <= 2 - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=A array inter false
			stall = 0;
			for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, j);
				pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
			}
			if (stall == 1)
				pipeline_register_0[0] = -1;
			else {
				pipeline_register_0[0] = hashFunction(2*i + m, j);
				A[2*i + m][j] = A[i][j] + 0.5f;
				j = j + 1;
			}
		}
	}
}

unsigned int hashFunction(int index0, int index1) {
	return concat(extractBits(index0, 0, 3), extractBits(index1, 0, 2));
}

