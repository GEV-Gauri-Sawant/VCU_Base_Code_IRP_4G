/*
 * State2_Process.c
 *
 *  Created on: 30-Jun-2023
 *      Author: Suchit Sawant
 */

#include "Vcu_Config.h"
#include "Vcu_Process.h"

void Process_State2_Inputs(void)
{
	if(Vcu_OutPuts.IGNITION_2_OUT)
	{
		Process_vehicleDrive_Inputs();
		Process_ig2_lights();
	}
	else if(!(Vcu_OutPuts.IGNITION_2_OUT))
	{
		Process_vehicleDrive_Inputs_off();
		Process_ig2_lights_off();
	}

}

void Process_vehicleDrive_Inputs(void)
{
	Motor_controller_OUT.neutral = Switch_Ios_IN.gear_sw1_IN;//neutral
	Motor_controller_OUT.forward_Relay = Switch_Ios_IN.gear_sw2_IN;//forward
	Motor_controller_OUT.reverse_relay = Switch_Ios_IN.gear_sw3_IN;//reverse
	Motor_controller_OUT.park_relay = Switch_Ios_IN.gear_sw4_IN;//park
	Motor_controller_OUT.regen_relay;
}
void Process_vehicleDrive_Inputs_off(void)
{
	Motor_controller_OUT.neutral = HIGH;// neutral
	Motor_controller_OUT.forward_Relay = LOW;//forward
	Motor_controller_OUT.reverse_relay = LOW;//reverse
	Motor_controller_OUT.park_relay = LOW;//park
	Motor_controller_OUT.regen_relay = LOW;

}

void Process_ig2_lights(void)
{
	Lights_OUT.reverse_light_out = Switch_Ios_IN.gear_sw3_IN;
}

void Process_ig2_lights_off(void)
{
	Lights_OUT.reverse_light_out = LOW;
}
