#ifndef AXI_STREAM_ADDER_HPP
#define AXI_STREAM_ADDER_HPP

#include <hls_stream.h>

#include "../common.hpp"

void axi_stream_adder(hls::stream<data_t>& in_stream, data_acc_t* sum);

#endif  // AXI_STREAM_ADDER_HPP