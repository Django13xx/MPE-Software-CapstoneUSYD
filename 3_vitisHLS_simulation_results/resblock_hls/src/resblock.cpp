#include <hls_stream.h>
#include <ap_int.h>

#define SIZE 56
#define CHANNELS 64

// Top-level function declaration
void resblock(float input[CHANNELS][SIZE][SIZE],
              float output[CHANNELS][SIZE][SIZE]) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // Simple element-wise copy to simulate a skip connection
    for (int c = 0; c < CHANNELS; c++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
#pragma HLS PIPELINE II=1
                output[c][i][j] = input[c][i][j];
            }
        }
    }
}
