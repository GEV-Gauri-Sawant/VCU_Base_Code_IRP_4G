/*
 * State_1.c
 *
 *  Created on: 28-Jun-2023
 *      Author: Suchit Sawant
 */

#include "InputCapture.h"
#include "Vcu_Config.h"
#include "IOExp_lib.h"
#include "Vcu_Init.h"

void state_1_InputCapture(void)
{
	if(Vcu_InPuts.IGNITION_1_IN)
	{
		/* check for io_expander */

	}
	else if(!(Vcu_InPuts.IGNITION_1_IN))
	{
		/* do the necessary task */
	}

	Switch_Ios_IN.brake_oil_IN = DIGITAL_IO_GetInput(&BRAKE_OIL_IN_D);

	/* check for io_expander */
	Io_Exp_U24();
	Io_Exp_U25();
	Io_Exp_U38();
	//Io_Exp_U48();

}

void Io_Exp_U24(void)
{
	//uart_debugg("in U24");

	uint8_t *port_data = NULL, IOExp_Address = 0x40;

	port_data = IOExp_ReadPIN_LEVEL(&I2C_MASTER_0, IOExp_Address, 0x00);

	/* port 0 */

	Combi_Switch_IN.low_beam_IN = (port_data[0] & (0x01));

	Combi_Switch_IN.high_beam_IN = ((port_data[0] >> 1) & (0x01));

	Combi_Switch_IN.pos_light_IN = ((port_data[0] >> 2) & (0x01));

	Combi_Switch_IN.left_indicator_IN = ((port_data[0] >> 3) & 0x01);

	Combi_Switch_IN.right_indicator_IN = ((port_data[0] >> 4) & 0x01);

	Combi_Switch_IN.hazzard_sw_IN = ((port_data[0] >> 5) & 0x01);

	Seat_Switch_IN.seat_belt_d_IN = ((port_data[0] >> 6) & 0x01);

	Seat_Switch_IN.seat_belt_p_IN = ((port_data[0] >> 7) & 0x01);


	/*    ***********************************************************   */

	/* port 1 */


	Seat_Switch_IN.seat_occup_p_IN = (port_data[1] & (0x01));

	Door_Switch_IN.door_lock_IN = ((port_data[1] >> 1) & (0x01));

	Door_Switch_IN.driver_door_IN = ((port_data[1] >> 2) & (0x01));

	Door_Switch_IN.passenger_door_IN = ((port_data[1] >> 3) & 0x01);

	Door_Switch_IN.passenger_2r_IN = ((port_data[1] >> 4) & 0x01);

	Door_Switch_IN.bonnet_IN = ((port_data[1] >> 5) & 0x01);

	Door_Switch_IN.hatch_IN = ((port_data[1] >> 6) & 0x01);

	Door_Switch_IN.passenger_2l_IN = ((port_data[1] >> 7) & 0x01);

	char str[] = "exit U24";
//	uart_debugg(str);

}

void Io_Exp_U25(void)
{

	//uart_debugg("in U25");

	uint8_t *port_data = NULL, IOExp_Address = 0x42;

	port_data = IOExp_ReadPIN_LEVEL(&I2C_MASTER_0, IOExp_Address, 0x00);


	/* port 0 */

	Switch_Ios_IN.ac_on_in = ((port_data[0] >> 1) & (0x01));

	Hvac_IN.blower_speed1_IN = ((port_data[0] >> 2) & (0x01));

	Hvac_IN.blower_speed2_IN = ((port_data[0] >> 3) & 0x01);

	Hvac_IN.blower_speed3_IN = ((port_data[0] >> 4) & 0x01);

	Hvac_IN.circulation_on_off = ((port_data[0] >> 5) & 0x01);

	/*    ***********************************************************   */

	/* port 1 */

//
	//uart_debugg("exit U25");
}

void Io_Exp_U38(void)
{
	//uart_debugg("in U38");

	uint8_t *port_data = NULL, IOExp_Address = 0x40;

	port_data = IOExp_ReadPIN_LEVEL(&I2C_MASTER_1, IOExp_Address, 0x00);


	/* port 0 */

	Switch_Ios_IN.power_window_in_d = ((port_data[0] >> 4) & 0x01);

	Aux_Inputs.AUX_IN4_D = ((port_data[0] >> 5) & 0x01);

	Aux_Inputs.AUX_IN5_D = ((port_data[0] >> 6) & 0x01);

	Switch_Ios_IN.orvm_fold_IN = ((port_data[0] >> 7) & 0x01);


	/*    ***********************************************************   */

	/* port 1 */

	Switch_Ios_IN.orvm_open_IN = (port_data[1] & (0x01));

	//uart_debugg("exit U38");

}

void Io_Exp_U48(void)
{

	//uart_debugg("in U48");

	uint8_t *port_data = NULL, IOExp_Address = 0x42;

	port_data = IOExp_ReadPIN_LEVEL(&I2C_MASTER_1, IOExp_Address, 0x00);


	/* port 0 */

	Hvac_IN.ac_solenoid = ((port_data[0] >> 2) & (0x01));



	/*    ***********************************************************   */

	/* port 1 */

	Aux_Inputs.AUX_IN3_D = (port_data[1] & (0x01));

	Aux_Inputs.AUX_IN2_D= ((port_data[1] >> 1) & (0x01));

	//uart_debugg("exit U48");

}

