// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// ap_controls
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of sum
//        bit 31~0 - sum[31:0] (Read)
// 0x14 : Data signal of sum
//        bit 31~0 - sum[63:32] (Read)
// 0x18 : Control signal of sum
//        bit 0  - sum_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL  0x00
#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_GIE      0x04
#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_IER      0x08
#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_ISR      0x0c
#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_DATA 0x10
#define XAXI_STREAM_ADDER_AP_CONTROLS_BITS_SUM_DATA 64
#define XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_CTRL 0x18

