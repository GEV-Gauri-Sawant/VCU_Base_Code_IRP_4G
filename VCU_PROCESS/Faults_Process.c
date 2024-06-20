/*
 * Faults_Process.c
 *
 *  Created on: 30-Sep-2023
 *      Author: Suchit Sawant
 */

#include "Vcu_Process.h"
#include "Vcu_Config.h"
#include "can_matrix.h"


bmsFault1_t *bmsFault1 = &CAN_BMS_29bit[CAN_0X1814A7F3].CAN_Data[0];
bmsFault2_t *bmsFault2 = &CAN_BMS_29bit[CAN_0X1815A7F3].CAN_Data[0];
GtakeFault_t *GtakeFaults = &CAN_Gtake_29bit[CAN_id0x8000221].CAN_Data[2];

allFault_indicator_t allFault_indicator;
cluster_Fault_Indicator_t *cluster_Fault_Indicator = &CAN_MSG_DB[CAN_18FED911].CAN_Data[6];

IRP_Mcu_rx_id0x30_t *Irp_MCU_Faults_29bit = &CAN_IRP_29bit[CAN_id0x30].CAN_Data[0];


void clusterFault_Indicator(void)
{
	/* cluster fault screen */

	if(allFault_indicator.Hvbatt_Fault && allFault_indicator.Mcu_Fault)
		cluster_Fault_Indicator ->cluster_Fault_Indicator = 100;
	else
		cluster_Fault_Indicator ->cluster_Fault_Indicator = allFault_indicator.Hvbatt_Fault + allFault_indicator.Mcu_Fault;
}

void HighVoltBattery_FaultIndicator(void)
{
	allFault_indicator.Hvbatt_Fault = 0;
	/* all bms faults & alarm */

	if(CAN_BMS_29bit[CAN_0X1814A7F3].CAN_Data[0] || CAN_BMS_29bit[CAN_0X1814A7F3].CAN_Data[1] || CAN_BMS_29bit[CAN_0X1814A7F3].CAN_Data[2])
	{
		// battery all faults
		allFault_indicator.Hvbatt_Fault = 101;
	}
}

void Gtake_FaultIndicator(void)
{
	allFault_indicator.Mcu_Fault = 0;
	if(CAN_Gtake_29bit[CAN_id0x8000221].CAN_Data[2])
	{
		// Gtake faults
		allFault_indicator.Mcu_Fault = 102;
	}
}

void Irp_FaultIndicator(void)
{
	allFault_indicator.Mcu_Fault = 0;
	if(Irp_MCU_Faults_29bit->FLT_MotorOverTemp || Irp_MCU_Faults_29bit->FLT_ControllerOverTemp)
	{
		allFault_indicator.Mcu_Fault = 102;
	}
}

void Mcu_FaultIndicator(void)
{
	//Gtake_FaultIndicator();
	Irp_FaultIndicator();
}

void allFaults_Process(void)
{
//	HighVoltBattery_FaultIndicator();
//	Mcu_FaultIndicator();
//	clusterFault_Indicator();
}


