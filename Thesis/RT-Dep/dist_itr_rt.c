#include "globals.h"

void kernel_dist_itr(float A[2*100]);
unsigned int hashFunction(int index0);


void kernel_dist_itr(float A[2*100]) {
	int i;
	const unsigned int PIPELINE_LATENCY = 14;
	int pipeline_register_0[PIPELINE_LATENCY];
	int stall;
	unsigned int shift_index;
	
	i = 0;
	for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
		pipeline_register_0[shift_index] = -1;
	}
	while (i <= 100 - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=A array inter false
		stall = 0;
		for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
			stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i);
			pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
		}
		if (stall == 1)
			pipeline_register_0[0] = -1;
		else {
			pipeline_register_0[0] = hashFunction(2*i);
			A[2*i] = A[i] + 0.5;
			i = i + 1;
		}
	}
}

unsigned int hashFunction(int index0) {
	return extractBits(index0, 0, 7);
}

