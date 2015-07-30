#include "globals.h"

void kernel_Tri_Sp_Slv(int m, int lb, int ub, float x[100], float L[100][100]);
unsigned int hashFunction(int index0);


void kernel_Tri_Sp_Slv(int m, int lb, int ub, float x[100], float L[100][100]) {
	int i;
	float t;
	const unsigned int PIPELINE_LATENCY = 15;
	int pipeline_register_0[PIPELINE_LATENCY];
	int stall;
	unsigned int shift_index;
	
	i = lb + 0;
	for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
		pipeline_register_0[shift_index] = -1;
	}
	while (i <= ub + 1 - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=x array inter false
		stall = 0;
		for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
			stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i);
			stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(m);
			pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
		}
		if (stall == 1)
			pipeline_register_0[0] = -1;
		else {
			pipeline_register_0[0] = hashFunction(i);
			x[i] = x[i] - L[i][m] * x[m];
			i = i + 1;
		}
	}
}

unsigned int hashFunction(int index0) {
	return extractBits(index0, 0, 7);
}

