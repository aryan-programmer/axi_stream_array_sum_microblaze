
/*******************************************************************
*
* CAUTION: This file is automatically generated by HSI.
* Version: 2023.2
* DO NOT EDIT.
*
* Copyright (C) 2010-2023 Xilinx, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT 

* 
* Description: Driver configuration
*
*******************************************************************/

#include "xparameters.h"
#include "xintc.h"


extern void XNullHandler (void *);

/*
* The configuration table for devices
*/

XIntc_Config XIntc_ConfigTable[] =
{
	{
		XPAR_INTERRUPT_CONTROLLER_DEVICE_ID,
		XPAR_INTERRUPT_CONTROLLER_BASEADDR,
		XPAR_INTERRUPT_CONTROLLER_KIND_OF_INTR,
		XPAR_INTERRUPT_CONTROLLER_HAS_FAST,
		XPAR_INTERRUPT_CONTROLLER_IVAR_RESET_VALUE,
		XPAR_INTERRUPT_CONTROLLER_NUM_INTR_INPUTS,
		XPAR_INTERRUPT_CONTROLLER_ADDR_WIDTH,
		XIN_SVC_SGL_ISR_OPTION,
		XPAR_INTERRUPT_CONTROLLER_TYPE,
		{
			{
				XNullHandler,
				(void *) XNULL
			}
		},
		XPAR_INTERRUPT_CONTROLLER_NUM_SW_INTR
	}
};
