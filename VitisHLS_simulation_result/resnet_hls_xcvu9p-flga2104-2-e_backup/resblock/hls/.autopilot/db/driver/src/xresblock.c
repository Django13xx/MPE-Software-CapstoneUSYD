// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xresblock.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XResblock_CfgInitialize(XResblock *InstancePtr, XResblock_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->Control_r_BaseAddress = ConfigPtr->Control_r_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XResblock_Start(XResblock *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL) & 0x80;
    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XResblock_IsDone(XResblock *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XResblock_IsIdle(XResblock *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XResblock_IsReady(XResblock *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XResblock_EnableAutoRestart(XResblock *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XResblock_DisableAutoRestart(XResblock *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_AP_CTRL, 0);
}

void XResblock_Set_input_r(XResblock *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_INPUT_R_DATA, (u32)(Data));
    XResblock_WriteReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_INPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XResblock_Get_input_r(XResblock *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResblock_ReadReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_INPUT_R_DATA);
    Data += (u64)XResblock_ReadReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_INPUT_R_DATA + 4) << 32;
    return Data;
}

void XResblock_Set_output_r(XResblock *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_OUTPUT_R_DATA, (u32)(Data));
    XResblock_WriteReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_OUTPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XResblock_Get_output_r(XResblock *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResblock_ReadReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_OUTPUT_R_DATA);
    Data += (u64)XResblock_ReadReg(InstancePtr->Control_r_BaseAddress, XRESBLOCK_CONTROL_R_ADDR_OUTPUT_R_DATA + 4) << 32;
    return Data;
}

void XResblock_InterruptGlobalEnable(XResblock *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_GIE, 1);
}

void XResblock_InterruptGlobalDisable(XResblock *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_GIE, 0);
}

void XResblock_InterruptEnable(XResblock *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_IER);
    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_IER, Register | Mask);
}

void XResblock_InterruptDisable(XResblock *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_IER);
    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_IER, Register & (~Mask));
}

void XResblock_InterruptClear(XResblock *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResblock_WriteReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_ISR, Mask);
}

u32 XResblock_InterruptGetEnabled(XResblock *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_IER);
}

u32 XResblock_InterruptGetStatus(XResblock *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XResblock_ReadReg(InstancePtr->Control_BaseAddress, XRESBLOCK_CONTROL_ADDR_ISR);
}

