// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XRESBLOCK_H
#define XRESBLOCK_H

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
#include "xresblock_hw.h"

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
    u64 Control_BaseAddress;
    u64 Control_r_BaseAddress;
} XResblock_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u64 Control_r_BaseAddress;
    u32 IsReady;
} XResblock;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XResblock_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XResblock_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XResblock_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XResblock_ReadReg(BaseAddress, RegOffset) \
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
int XResblock_Initialize(XResblock *InstancePtr, UINTPTR BaseAddress);
XResblock_Config* XResblock_LookupConfig(UINTPTR BaseAddress);
#else
int XResblock_Initialize(XResblock *InstancePtr, u16 DeviceId);
XResblock_Config* XResblock_LookupConfig(u16 DeviceId);
#endif
int XResblock_CfgInitialize(XResblock *InstancePtr, XResblock_Config *ConfigPtr);
#else
int XResblock_Initialize(XResblock *InstancePtr, const char* InstanceName);
int XResblock_Release(XResblock *InstancePtr);
#endif

void XResblock_Start(XResblock *InstancePtr);
u32 XResblock_IsDone(XResblock *InstancePtr);
u32 XResblock_IsIdle(XResblock *InstancePtr);
u32 XResblock_IsReady(XResblock *InstancePtr);
void XResblock_EnableAutoRestart(XResblock *InstancePtr);
void XResblock_DisableAutoRestart(XResblock *InstancePtr);

void XResblock_Set_input_r(XResblock *InstancePtr, u64 Data);
u64 XResblock_Get_input_r(XResblock *InstancePtr);
void XResblock_Set_output_r(XResblock *InstancePtr, u64 Data);
u64 XResblock_Get_output_r(XResblock *InstancePtr);

void XResblock_InterruptGlobalEnable(XResblock *InstancePtr);
void XResblock_InterruptGlobalDisable(XResblock *InstancePtr);
void XResblock_InterruptEnable(XResblock *InstancePtr, u32 Mask);
void XResblock_InterruptDisable(XResblock *InstancePtr, u32 Mask);
void XResblock_InterruptClear(XResblock *InstancePtr, u32 Mask);
u32 XResblock_InterruptGetEnabled(XResblock *InstancePtr);
u32 XResblock_InterruptGetStatus(XResblock *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
