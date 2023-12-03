#include "./axi_stream_adder.hpp"

void                  axi_stream_adder(hls::stream<data_t>& in_stream, data_acc_t* sum) {
#pragma HLS INTERFACE mode = ap_none port = in_stream
#pragma HLS INTERFACE mode = axis port = in_stream name = input_data
#pragma HLS INTERFACE mode = ap_ctrl_none port = return
#pragma HLS INTERFACE mode = s_axilite port = return bundle = ap_controls
#pragma HLS INTERFACE mode = s_axilite port = sum bundle = ap_controls

	static data_acc_t l_sum = 0;
	l_sum += in_stream.read();
	*sum = l_sum;
}
