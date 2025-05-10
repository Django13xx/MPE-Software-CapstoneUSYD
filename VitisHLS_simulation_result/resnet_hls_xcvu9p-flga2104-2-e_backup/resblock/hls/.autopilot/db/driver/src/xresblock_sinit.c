// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xresblock.h"

extern XResblock_Config XResblock_ConfigTable[];

#ifdef SDT
XResblock_Config *XResblock_LookupConfig(UINTPTR BaseAddress) {
	XResblock_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XResblock_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XResblock_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XResblock_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XResblock_Initialize(XResblock *InstancePtr, UINTPTR BaseAddress) {
	XResblock_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XResblock_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XResblock_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XResblock_Config *XResblock_LookupConfig(u16 DeviceId) {
	XResblock_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XRESBLOCK_NUM_INSTANCES; Index++) {
		if (XResblock_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XResblock_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XResblock_Initialize(XResblock *InstancePtr, u16 DeviceId) {
	XResblock_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XResblock_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XResblock_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

