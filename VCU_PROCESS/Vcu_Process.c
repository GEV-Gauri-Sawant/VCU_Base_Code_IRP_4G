/*
 * Vcu_Process.c
 *
 *  Created on: 27-Jun-2023
 *      Author: Suchit Sawant
 */
#include "Vcu_Process.h"
#include "Vcu_Config.h"
#include "can_matrix.h"

int *cluster_door_in = &CAN_MSG_DB[CAN_18FF2121].CAN_Data[0];

void Process_VcuOutputs_Update(void)
{
	allFaults_Process();

	Vcu_OutPuts.charger_connect_OUT = charger_on();
	Vcu_OutPuts.IGNITION_1_OUT = Vcu_InPuts.IGNITION_1_IN;

	Relay_Control_Switch_OUT.elec_handbrake_pwr_out = (Switch_Ios_IN.handbrake_sw_IN || Switch_Ios_IN.electronic_brake_in_d);

	if(!Vcu_OutPuts.charger_connect_OUT)
		Vcu_OutPuts.IGNITION_2_OUT = Vcu_InPuts.IGNITION_2_IN;
	else
		Vcu_OutPuts.IGNITION_2_OUT = false;

	if(Vcu_OutPuts.IGNITION_1_OUT || Vcu_OutPuts.IGNITION_2_OUT)
	{
		Lights_OUT.brake_switch_out_d = !Switch_Ios_IN.brake_sw_in_d;
	}
	else
	{
		Lights_OUT.brake_switch_out_d = false;
	}

	if(Vcu_OutPuts.IGNITION_2_OUT && (Vcu_OutPuts.IGNITION_1_OUT == 0))
	{
		Vcu_OutPuts.IGNITION_1_OUT = 1;
	}

	all_doors();

	Process_State1_Inputs();
	Process_State2_Inputs();
}

void all_doors(void)
{
	int charging = 0;
	Door_Switch_OUT.driver_door_OUT = Door_Switch_IN.driver_door_IN;
	Door_Switch_OUT.passenger_door_OUT = Door_Switch_IN.passenger_door_IN;
	Door_Switch_OUT.bonnet_OUT = 0;//Door_Switch_IN.bonnet_IN;
	Door_Switch_OUT.hatch_OUT = Door_Switch_IN.hatch_IN;

	if(!Door_Switch_IN.driver_door_IN)
		instrument_cluster_doorsvar.driver_door_OUT = (uint8_t)right_door;
	else
		instrument_cluster_doorsvar.driver_door_OUT = 0;

	if(!Door_Switch_IN.passenger_door_IN)
		instrument_cluster_doorsvar.passenger_door_OUT = (uint8_t)left_door;
	else
		instrument_cluster_doorsvar.passenger_door_OUT = 0;

	if(!Door_Switch_IN.bonnet_IN)
		instrument_cluster_doorsvar.bonnet_OUT = 0;//(uint8_t)hood;
	else
		instrument_cluster_doorsvar.bonnet_OUT = 0;

	if(!Door_Switch_IN.hatch_IN)
		instrument_cluster_doorsvar.hatch_OUT = (uint8_t)tailgate;
	else
		instrument_cluster_doorsvar.hatch_OUT = 0;

	charging = 0x20;

	if(charger_on())
	{
		instrument_cluster_doorsvar.driver_door_OUT = 0;
		instrument_cluster_doorsvar.passenger_door_OUT = 0;
		instrument_cluster_doorsvar.bonnet_OUT = 0;
		instrument_cluster_doorsvar.hatch_OUT = 0;
	}
	else
	{
		charging = 0x00;
		charge_complete = 0x00;
	}

	if(charge_complete)
		charging = 0;

	//*cluster_door_in = instrument_cluster_doorsvar.driver_door_OUT + instrument_cluster_doorsvar.passenger_door_OUT + instrument_cluster_doorsvar.bonnet_OUT + instrument_cluster_doorsvar.hatch_OUT + charge_complete + charging;
}


int charger_on(void)
{
	return Vcu_InPuts.charger_connect_IN;
	//return charging_connected ;
	return 0;
}


