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

void XAxi_stream_adder_Start(XAxi_stream_adder *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL) & 0x80;
    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAxi_stream_adder_IsDone(XAxi_stream_adder *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAxi_stream_adder_IsIdle(XAxi_stream_adder *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAxi_stream_adder_IsReady(XAxi_stream_adder *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAxi_stream_adder_EnableAutoRestart(XAxi_stream_adder *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL, 0x80);
}

void XAxi_stream_adder_DisableAutoRestart(XAxi_stream_adder *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_AP_CTRL, 0);
}

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

void XAxi_stream_adder_InterruptGlobalEnable(XAxi_stream_adder *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_GIE, 1);
}

void XAxi_stream_adder_InterruptGlobalDisable(XAxi_stream_adder *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_GIE, 0);
}

void XAxi_stream_adder_InterruptEnable(XAxi_stream_adder *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_IER);
    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_IER, Register | Mask);
}

void XAxi_stream_adder_InterruptDisable(XAxi_stream_adder *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_IER);
    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_IER, Register & (~Mask));
}

void XAxi_stream_adder_InterruptClear(XAxi_stream_adder *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAxi_stream_adder_WriteReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_ISR, Mask);
}

u32 XAxi_stream_adder_InterruptGetEnabled(XAxi_stream_adder *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_IER);
}

u32 XAxi_stream_adder_InterruptGetStatus(XAxi_stream_adder *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAxi_stream_adder_ReadReg(InstancePtr->Ap_controls_BaseAddress, XAXI_STREAM_ADDER_AP_CONTROLS_ADDR_ISR);
}

