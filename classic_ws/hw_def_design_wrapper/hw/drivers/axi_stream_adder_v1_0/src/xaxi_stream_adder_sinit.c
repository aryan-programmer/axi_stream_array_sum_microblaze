// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xaxi_stream_adder.h"

extern XAxi_stream_adder_Config XAxi_stream_adder_ConfigTable[];

#ifdef SDT
XAxi_stream_adder_Config *XAxi_stream_adder_LookupConfig(UINTPTR BaseAddress) {
	XAxi_stream_adder_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XAxi_stream_adder_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XAxi_stream_adder_ConfigTable[Index].Ap_controls_BaseAddress == BaseAddress) {
			ConfigPtr = &XAxi_stream_adder_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAxi_stream_adder_Initialize(XAxi_stream_adder *InstancePtr, UINTPTR BaseAddress) {
	XAxi_stream_adder_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAxi_stream_adder_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAxi_stream_adder_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XAxi_stream_adder_Config *XAxi_stream_adder_LookupConfig(u16 DeviceId) {
	XAxi_stream_adder_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XAXI_STREAM_ADDER_NUM_INSTANCES; Index++) {
		if (XAxi_stream_adder_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAxi_stream_adder_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAxi_stream_adder_Initialize(XAxi_stream_adder *InstancePtr, u16 DeviceId) {
	XAxi_stream_adder_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAxi_stream_adder_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAxi_stream_adder_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

