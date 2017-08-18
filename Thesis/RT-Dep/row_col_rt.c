#include "globals.h"

void kernel_row_col(int rows, int cols, float buff_A[32][32], float buff_B[32][32]);
unsigned int hashFunction(int index0, int index1);


void kernel_row_col(int rows, int cols, float buff_A[32][32], float buff_B[32][32]) {
	int row;
	int col;
	int temp;
	
	for(row = 0; row <= rows + 1 - 1; row = row + 1) {
		const unsigned int PIPELINE_LATENCY = 8;
		int pipeline_register_0[PIPELINE_LATENCY];
		int stall;
		unsigned int shift_index;
		
		col = 0;
		for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
			pipeline_register_0[shift_index] = -1;
		}
		while (col <= cols - 1 + 1) {
			//for(col = 0; col <= cols - 1 + 1; col = col + 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=buff_A array inter false
#pragma HLS DEPENDENCE variable=buff_B array inter false
			stall = 0;
			for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(0, col);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(1, col);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction(0, col);
				pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
			}
			if (stall == 1)
				pipeline_register_0[0] = -1;
			else {
				pipeline_register_0[0] = hashFunction(2, col);
				buff_A[2][col] = buff_A[1][col] + 0.5;
				pipeline_register_0[0] = hashFunction(1, col);
				buff_A[1][col] = buff_A[0][col] + 0.5;
				pipeline_register_0[0] = hashFunction(1, col);
				buff_B[1][col] = buff_B[0][col] + 0.5;
				col = col + 1;
			}
		}
	}
}

unsigned int hashFunction(int index0, int index1) {
	return concat(extractBits(index0, 0, 1), extractBits(index1, 0, 3));
}

