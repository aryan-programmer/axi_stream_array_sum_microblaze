// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// ap_controls
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of sum
//        bit 31~0 - sum[31:0] (Read)
// 0x14 : Data signal of sum
//        bit 31~0 - sum[63:32] (Read)
// 0x18 : Control signal of sum
//        bit 0  - sum_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_DATA 0x10
#define XAXI_STREAM_ADDER_AP_CONTROLS_BITS_SUM_DATA 64
#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_CTRL 0x18

