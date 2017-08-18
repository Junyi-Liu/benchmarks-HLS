#include "globals.h"

void kernel_typ_loop(int m, int n, float A[2*100][2*100]);
unsigned int hashFunction(int index0, int index1);


void kernel_typ_loop(int m, int n, float A[2*100][2*100]) {
	int i;
	int j;
	int k;
	
	for(j = 100; j <= 2*100 - 1; j = j + 1) {
		const unsigned int PIPELINE_LATENCY = 16;
		int pipeline_register_0[PIPELINE_LATENCY];
		int stall;
		unsigned int shift_index;
		
		i = 20;
		for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
			pipeline_register_0[shift_index] = -1;
		}
		while (i <= n - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=A array inter false
			stall = 0;
			for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(j - 1, i + m);
				pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
			}
			if (stall == 1)
				pipeline_register_0[0] = -1;
			else {
				pipeline_register_0[0] = hashFunction(j, i);
				A[j][i] = A[j - 1][i + m] + 0.5f;
				i = i + 1;
			}
		}
	}
}

unsigned int hashFunction(int index0, int index1) {
	return extractBits(index0, 0, 1) | extractBits(index1, 0, 4);
}

