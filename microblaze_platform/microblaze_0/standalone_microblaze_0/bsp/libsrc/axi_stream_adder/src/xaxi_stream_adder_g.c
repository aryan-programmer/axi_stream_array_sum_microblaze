#include "xaxi_stream_adder.h"

XAxi_stream_adder_Config XAxi_stream_adder_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,axi-stream-adder-1.0", /* compatible */
		0x40000 /* reg */
	},
	 {
		 NULL
	}
};