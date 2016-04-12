"globals.h"

void kernel_adi_int(int n, int nl1, int nl2, float du1[100], float du2[100], float du3[100], float u1[3][100][100], float u2[3][100][100], float u3[3][100][100]);
unsigned int hashFunction(int index0);


void kernel_adi_int(int n, int nl1, int nl2, float du1[100], float du2[100], float du3[100], float u1[3][100][100], float u2[3][100][100], float u3[3][100][100]) {
	int kx;
	int ky;
	float sig = 1.0;
	float a11 = 1.0;
	float a12 = 1.0;
	float a13 = 1.0;
	float a21 = 1.0;
	float a22 = 1.0;
	float a23 = 1.0;
	float a31 = 1.0;
	float a32 = 1.0;
	float a33 = 1.0;
	
	for(kx = 1; kx <= 4 - 1; kx = kx + 1) {
#pragma HLS PIPELINE
		const unsigned int PIPELINE_LATENCY = 52;
		int pipeline_register_0[PIPELINE_LATENCY];
		int stall;
		unsigned int shift_index;
		
		ky = 1;
		for(shift_index = 0; shift_index < PIPELINE_LATENCY; shift_index = shift_index + 1) {
#pragma HLS UNROLL
			pipeline_register_0[shift_index] = -1;
		}
		while (ky <= n - 1) {
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE variable=u1 array inter false
#pragma HLS DEPENDENCE variable=u2 array inter false
#pragma HLS DEPENDENCE variable=u3 array inter false
#pragma HLS DEPENDENCE variable=du1 array inter false
#pragma HLS DEPENDENCE variable=du2 array inter false
#pragma HLS DEPENDENCE variable=du3 array inter false
			stall = 0;
			for(shift_index = PIPELINE_LATENCY - 1; shift_index > 0; shift_index = shift_index - 1) {
#pragma HLS UNROLL
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky + 1, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky - 1, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx + 1);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx - 1);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky + 1, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky - 1, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx + 1);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx - 1);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky + 1, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky - 1, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx + 1);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction3(nl1, ky, kx - 1);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				stall = stall | pipeline_register_0[shift_index - 1] == hashFunction1(ky);
				pipeline_register_0[shift_index] = pipeline_register_0[shift_index - 1];
			}
			if (stall == 1)
				pipeline_register_0[0] = -1;
			else {
				pipeline_register_0[0] = hashFunction(ky);
				du1[ky] = u1[nl1][ky + 1][kx] - u1[nl1][ky - 1][kx];
				pipeline_register_0[0] = hashFunction(ky);
				du2[ky] = u2[nl1][ky + 1][kx] - u2[nl1][ky - 1][kx];
				pipeline_register_0[0] = hashFunction(ky);
				du3[ky] = u3[nl1][ky + 1][kx] - u3[nl1][ky - 1][kx];
				pipeline_register_0[0] = hashFunction(nl2, ky, kx);
				u1[nl2][ky][kx] = u1[nl1][ky][kx] + a11 * du1[ky] + a12 * du2[ky] + a13 * du3[ky] + sig * (u1[nl1][ky][kx + 1] - 2.0 * u1[nl1][ky][kx] + u1[nl1][ky][kx - 1]);
				pipeline_register_0[0] = hashFunction(nl2, ky, kx);
				u2[nl2][ky][kx] = u2[nl1][ky][kx] + a21 * du1[ky] + a22 * du2[ky] + a23 * du3[ky] + sig * (u2[nl1][ky][kx + 1] - 2.0 * u2[nl1][ky][kx] + u2[nl1][ky][kx - 1]);
				pipeline_register_0[0] = hashFunction(nl2, ky, kx);
				u3[nl2][ky][kx] = u3[nl1][ky][kx] + a31 * du1[ky] + a32 * du2[ky] + a33 * du3[ky] + sig * (u3[nl1][ky][kx + 1] - 2.0 * u3[nl1][ky][kx] + u3[nl1][ky][kx - 1]);
				ky = ky + 1;
			}
		}
	}
}

unsigned int hashFunction1(int index0) {
	return extractBits(index0, 0, 7);
}

unsigned int hashFunction3(int index0, int index1, , int index2) {
	return concat(extractBits(index0, 0, 7), extractBits(index1, 0, 15), extractBits(index1, 0, 3));
}

