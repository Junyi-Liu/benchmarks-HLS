#include "globals.h"

void kernel_jacobi_2d_imper(int n, int m, float A[300][300]);
unsigned int hashFunction(int index0, int index1);


void kernel_jacobi_2d_imper(int n, int m, float A[300][300]) {
	int i;
	int j;
	
	for(i = 100; i <= 200 - 1 - 1; i = i + 1) {
#pragma HLS PIPELINE
		const unsigned int PIPELINE_LATENCY = 24;
		int pipeline_register_0[PIPELINE_LATENCY];
		int stall;
		unsigned int shift_index;
		
		j = 100;
		for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
			pipeline_register_0[shift_index] = -1;
		}
		while (j <= 200 - 1 - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=A array inter false
			stall = 0;
			//A[i][j] = 0.2 * (A[i][j] + A[i][j - m] + A[i][m + j] + A[m + i][j] + A[i - m][j]);
			for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, j);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, j - m);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i, m + j);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(m + i, j);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(i - m, j);
				pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
			}
			if (stall == 1)
				pipeline_register_0[0] = -1;
			else {
				pipeline_register_0[0] = hashFunction(i, j);
				A[i][j] = 0.2 * (A[i][j] + A[i][j - m] + A[i][m + j] + A[m + i][j] + A[i - m][j]);
				j = j + 1;
			}
		}
	}
}

unsigned int hashFunction(int index0, int index1) {
	return concat(extractBits(index0, 0, 3), extractBits(index1, 0, 15));
	//return extractBits(index0, 0, 3) | extractBits(index1, 0, 7);
}

