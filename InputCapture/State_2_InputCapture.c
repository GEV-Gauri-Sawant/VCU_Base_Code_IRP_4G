/*
 * State_2_InputCapture.c
 *
 *  Created on: 30-Jun-2023
 *      Author: Suchit Sawant
 */
#include "InputCapture.h"
#include "Vcu_Config.h"

void State_2_InputCapture(void)
{
	if(Vcu_InPuts.IGNITION_2_IN)
	{

	}
	else if(!(Vcu_InPuts.IGNITION_2_IN))
	{

	}

	Read_State2_inputs();

}
void Read_State2_inputs(void)
{
	Switch_Ios_IN.brake_sw_in_d = DIGITAL_IO_GetInput(&BRAKE_SW_IN_D);

	/* gear inputs */
	Switch_Ios_IN.gear_sw1_IN = DIGITAL_IO_GetInput(&GEAR_SW1_IN_D); //Neutral
	Switch_Ios_IN.gear_sw2_IN = DIGITAL_IO_GetInput(&GEAR_SW2_IN_D); //forward
	Switch_Ios_IN.gear_sw3_IN = DIGITAL_IO_GetInput(&GEAR_SW3_IN_D); //reverse
	Switch_Ios_IN.gear_sw4_IN = DIGITAL_IO_GetInput(&GEAR_SW4_IN_D); //parking

	/* ig2 Lights */

}



