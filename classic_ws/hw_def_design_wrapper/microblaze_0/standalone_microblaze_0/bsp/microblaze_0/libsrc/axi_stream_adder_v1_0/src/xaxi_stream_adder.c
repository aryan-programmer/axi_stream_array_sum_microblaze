// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xaxi_stream_adder.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAxi_stream_adder_CfgInitialize(XAxi_stream_adder *InstancePtr, XAxi_stream_adder_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ap_controls_BaseAddress = ConfigPtr->Ap_controls_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

u64 XAxi_stream_adder_Get_sum(XAxi_stream_adder *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_DATA);
    Data += (u64)XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_DATA + 4) << 32;
    return Data;
}

u32 XAxi_stream_adder_Get_sum_vld(XAxi_stream_adder *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_SUM_CTRL);
    return Data & 0x1;
}

