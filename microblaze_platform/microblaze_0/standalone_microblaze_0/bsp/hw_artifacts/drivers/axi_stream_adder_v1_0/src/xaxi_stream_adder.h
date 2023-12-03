// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XAXI_STREAM_ADDER_H
#define XAXI_STREAM_ADDER_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xaxi_stream_adder_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Ap_controls_BaseAddress;
} XAxi_stream_adder_Config;
#endif

typedef struct {
    u64 Ap_controls_BaseAddress;
    u32 IsReady;
} XAxi_stream_adder;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAxi_stream_adder_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAxi_stream_adder_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAxi_stream_adder_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAxi_stream_adder_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XAxi_stream_adder_Initialize(XAxi_stream_adder *InstancePtr, UINTPTR BaseAddress);
XAxi_stream_adder_Config* XAxi_stream_adder_LookupConfig(UINTPTR BaseAddress);
#else
int XAxi_stream_adder_Initialize(XAxi_stream_adder *InstancePtr, u16 DeviceId);
XAxi_stream_adder_Config* XAxi_stream_adder_LookupConfig(u16 DeviceId);
#endif
int XAxi_stream_adder_CfgInitialize(XAxi_stream_adder *InstancePtr, XAxi_stream_adder_Config *ConfigPtr);
#else
int XAxi_stream_adder_Initialize(XAxi_stream_adder *InstancePtr, const char* InstanceName);
int XAxi_stream_adder_Release(XAxi_stream_adder *InstancePtr);
#endif

void XAxi_stream_adder_Start(XAxi_stream_adder *InstancePtr);
u32 XAxi_stream_adder_IsDone(XAxi_stream_adder *InstancePtr);
u32 XAxi_stream_adder_IsIdle(XAxi_stream_adder *InstancePtr);
u32 XAxi_stream_adder_IsReady(XAxi_stream_adder *InstancePtr);
void XAxi_stream_adder_EnableAutoRestart(XAxi_stream_adder *InstancePtr);
void XAxi_stream_adder_DisableAutoRestart(XAxi_stream_adder *InstancePtr);

u64 XAxi_stream_adder_Get_sum(XAxi_stream_adder *InstancePtr);
u32 XAxi_stream_adder_Get_sum_vld(XAxi_stream_adder *InstancePtr);

void XAxi_stream_adder_InterruptGlobalEnable(XAxi_stream_adder *InstancePtr);
void XAxi_stream_adder_InterruptGlobalDisable(XAxi_stream_adder *InstancePtr);
void XAxi_stream_adder_InterruptEnable(XAxi_stream_adder *InstancePtr, u32 Mask);
void XAxi_stream_adder_InterruptDisable(XAxi_stream_adder *InstancePtr, u32 Mask);
void XAxi_stream_adder_InterruptClear(XAxi_stream_adder *InstancePtr, u32 Mask);
u32 XAxi_stream_adder_InterruptGetEnabled(XAxi_stream_adder *InstancePtr);
u32 XAxi_stream_adder_InterruptGetStatus(XAxi_stream_adder *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
