/*
 * State1_Process.c
 *
 *  Created on: 29-Jun-2023
 *      Author: Suchit Sawant
 */

//#include "DAVE.h"
#include "Vcu_Config.h"
#include "Vcu_Process.h"
#include "can_matrix.h"

instrument_clustor_indicators_t *instrument_clustor_indicators = (instrument_clustor_indicators_t *)&(CAN_MSG_DB[CAN_18FFB632].CAN_Data[0]);
instrument_clustor_buzzer_t *instrument_clustor_buzzer = &(CAN_MSG_DB[CAN_18FF2021].CAN_Data[0]);
Instrumetcluster_DriveMode_OUT_t *Instrumetcluster_DriveMode_OUT = &(CAN_MSG_DB[CAN_18FFB632].CAN_Data[4]);
eps_status_t *eps_status = &eps_n[can_0x1E5].can_matrix[0];

void Process_State1_Inputs(void)
{
	static bool init_once = 1;
	Process_Io_exp_U24();

	if(Vcu_OutPuts.IGNITION_1_OUT)
	{
		//Process_Io_exp_U25();
		Process_cluster_indicators();
		Process_drive_mode();
		Process_faciaaswitches();
		if(init_once)
		{
			init_hw();
			init_once = 0;
		}
	}
	else if(!(Vcu_OutPuts.IGNITION_1_OUT))
	{
		all_Ig1_Inputs_off();
		cluster_indicators_off();
		init_once = 1;
	}
}

void hazzard(void)
{
	/* for hazzard */
	if((Vcu_OutPuts.IGNITION_1_OUT == 0) && (Combi_Switch_IN.left_indicator_IN && Combi_Switch_IN.right_indicator_IN))
	{
		Relay_Control_Switch_OUT.left_indicator_OUT = true;
		Relay_Control_Switch_OUT.right_indicator_OUT = true;
	}

	else if(((Combi_Switch_IN.left_indicator_IN == 0) && (Combi_Switch_IN.right_indicator_IN == 0)))
	{
		Relay_Control_Switch_OUT.left_indicator_OUT = false;
		Relay_Control_Switch_OUT.right_indicator_OUT = false;
	}
	/* end */

	else if(Vcu_OutPuts.IGNITION_1_OUT)
	{
		Relay_Control_Switch_OUT.left_indicator_OUT = Combi_Switch_IN.left_indicator_IN;
		Relay_Control_Switch_OUT.right_indicator_OUT = Combi_Switch_IN.right_indicator_IN;
	}

}

void Process_Io_exp_U24(void)
{
	Relay_Control_Switch_OUT.low_beam_OUT = Combi_Switch_IN.low_beam_IN;
	Relay_Control_Switch_OUT.high_beam_OUT = Combi_Switch_IN.high_beam_IN;
	Relay_Control_Switch_OUT.pos_light_OUT = Combi_Switch_IN.pos_light_IN;

	hazzard();
}

void Process_Io_exp_U25(void)
{
	Relay_Control_Switch_OUT.ac_blower1_OUT = Hvac_IN.blower_speed1_IN;
	Relay_Control_Switch_OUT.ac_blower2_OUT = Hvac_IN.blower_speed2_IN;
	//Relay_Control_Switch_OUT.ac_blower3_OUT = Hvac_IN.blower_speed3_IN;

}

void Process_cluster_indicators(void)
 {
	static int i_counter = 0;
	/*if(Combi_Switch_IN.left_indicator_IN || Combi_Switch_IN.right_indicator_IN)
	{
		 INTERRUPT_Enable(&INTERRUPT_0);
	}
	else
	{
		Instrument_Cluster_OUT.set_left_indicator = 0;
		Instrument_Cluster_OUT.set_right_indicator = 0;
		INTERRUPT_Disable(&INTERRUPT_0);
	}*/
	/*
if(((i_counter >= 0) && (i_counter <= 25)) && (Combi_Switch_IN.left_indicator_IN || Combi_Switch_IN.right_indicator_IN))
{
	 Instrument_Cluster_OUT.set_left_indicator = Combi_Switch_IN.left_indicator_IN;
	 Instrument_Cluster_OUT.set_right_indicator = Combi_Switch_IN.right_indicator_IN;
	 i_counter++;

}
else if(((i_counter >= 25) && (i_counter <= 26)) && (Combi_Switch_IN.left_indicator_IN || Combi_Switch_IN.right_indicator_IN))
{
	Instrument_Cluster_OUT.set_left_indicator = 0;//Combi_Switch_IN.left_indicator_IN;
	Instrument_Cluster_OUT.set_right_indicator = 0;//Combi_Switch_IN.right_indicator_IN;
		i_counter++;

}
else
{
	Instrument_Cluster_OUT.set_left_indicator = 0;//Combi_Switch_IN.left_indicator_IN;
	Instrument_Cluster_OUT.set_right_indicator = 0;//Combi_Switch_IN.right_indicator_IN;

	i_counter = 0;
}
*/
	Instrument_Cluster_OUT.set_left_indicator = Combi_Switch_IN.left_indicator_IN;
	Instrument_Cluster_OUT.set_right_indicator = Combi_Switch_IN.right_indicator_IN;
	 //Instrument_Cluster_OUT.set_low_beam = Relay_Control_Switch_OUT.low_beam_OUT;
	 Instrument_Cluster_OUT.set_high_beam = Relay_Control_Switch_OUT.high_beam_OUT;
	 Instrument_Cluster_OUT.set_low_beam = Relay_Control_Switch_OUT.pos_light_OUT;//There is no indicator for low beam there is for position
	 Instrument_Cluster_OUT.set_brake_oil = Switch_Ios_IN.brake_oil_IN;

	// Instrument_Cluster_OUT.eps_status = 1;//default value to show eps failure
	 Instrument_Cluster_OUT.eps_status = eps_status-> Power_Steering_Fault_Indication_On_EPS;///////eps failure

	 Instrument_Cluster_OUT.aux_vtg_critical;////////
	 Instrument_Cluster_OUT.battery_temp_exceeded;/////////
	 /*instrument_clustor_buzzer-> charging_connected = */Instrument_Cluster_OUT.charging_connected = charger_on();//Vcu_InPuts.charger_connect_IN;
	 /*instrument_clustor_indicators-> generic_alarm;////////*/
	 Instrument_Cluster_OUT.regen_enabled = Irp_Mcu_drive_states_29bit-> Regen_On_Throttle_Realese || Irp_Mcu_drive_states_29bit-> Regen_On_Brake;
	 instrument_clustor_indicators-> parking_brake_light = !Switch_Ios_IN.handbrake_sw_IN;////////
	 Seat_Belt_OUT.seat_occupied = (!(/*Seat_Switch_IN.seat_belt_d_IN &&*/ Seat_Switch_IN.seat_belt_p_IN));

	 if(vspeed >=10)
	 {
		 instrument_clustor_buzzer-> seat_belt_warning = Seat_Belt_OUT.seat_occupied;
	 }
	 else
	 {
		 instrument_clustor_buzzer-> seat_belt_warning = false;
	 }
	 // instrument_clustor_indicators-> overspeed = 1;
 }

void cluster_indicators_off(void)
 {
	Instrument_Cluster_OUT.set_left_indicator = false;
	Instrument_Cluster_OUT.set_right_indicator = false;
	Instrument_Cluster_OUT.set_low_beam = false;
	Instrument_Cluster_OUT.set_high_beam = false;
	Instrument_Cluster_OUT.set_brake_oil = false;//////
	//Instrument_Cluster_OUT.;///////eps failure
	Instrument_Cluster_OUT.aux_vtg_critical = false;////////
	Instrument_Cluster_OUT.battery_temp_exceeded = false;/////////
	Instrument_Cluster_OUT.charging_connected = false;/////////////
	/*instrument_clustor_indicators-> generic_alarm;////////*/
	Instrument_Cluster_OUT.regen_enabled = false;
	/*instrument_clustor_indicators-> parking_brake_light;////////*/
	instrument_clustor_indicators-> seat_belt = false;
 }

void process_instrument_cluster_door(void)
{

}

void cluster_gear(void)
{

}

void all_Ig1_Inputs_off(void)
{
	/* IO_EXP U24 */
	/*Relay_Control_Switch_OUT.low_beam_OUT = false;
	Relay_Control_Switch_OUT.high_beam_OUT = false;
	Relay_Control_Switch_OUT.pos_light_OUT = false;*/

	//Relay_Control_Switch_OUT.left_indicator_OUT = false;
	//Relay_Control_Switch_OUT.right_indicator_OUT = false;

	/* IO EXP U25 */
}

void Process_drive_mode(void)
{
	static bool prev_input = 0;
	static uint8_t ModeCounter_MCU = eco_mode_mcu, ModeCounter_Cluster = eco_mode_cluster, counter = 1;

	switch (Switch_Ios_IN.gear_sw2_IN )
	{
		case 1:
				if((prev_input == 0 ) && (Hvac_IN.blower_speed2_IN)) // mode switch is connected to Hvac_IN.blower_speed2_IN
				{
					ModeCounter_Cluster++;
					if(ModeCounter_Cluster == invalid_data_cluster)
						ModeCounter_Cluster = eco_mode_cluster;

					prev_input = 1;
				}
				else if(Hvac_IN.blower_speed2_IN == 0)
				{
					prev_input = 0;
				}
		break;

		default:
				ModeCounter_MCU = eco_mode_mcu;
				ModeCounter_Cluster = eco_mode_cluster;
		break;
	}
/* this is for gtake */
	if(Switch_Ios_IN.gear_sw2_IN)
	{
		ModeCounter_MCU = 3 - ModeCounter_Cluster;
	}
	else
	{
		ModeCounter_MCU = eco_mode_mcu;
		ModeCounter_Cluster = eco_mode_cluster;
	}
/***** for gtake end  **********/

	Process_cluster_drivemode(ModeCounter_Cluster);
	Process_motordrive_mode(ModeCounter_Cluster); //for gtake pass ModeCounter_MCU, and for irp pass ModeCounter_Cluster

}

void Process_cluster_drivemode(uint8_t mode)
{
	if(!Lights_OUT.brake_switch_out_d)
		Instrumetcluster_DriveMode_OUT ->DriveMode = mode;
}
void Process_motordrive_mode(uint8_t mode)
{
	//motordrive_mode_Gtake(uint8_t mode);
	motordrive_mode_irp(mode);
}
void motordrive_mode_Gtake(uint8_t mode)
{
	if(!Lights_OUT.brake_switch_out_d)
		Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = mode;
}

void motordrive_mode_irp(uint8_t mode)
{
	if(!Lights_OUT.brake_switch_out_d)
		Irp_Mcu_drive_states_29bit->Driving_Profile = mode;
}

void Process_Regen_Control(void)
{
	static bool prev_input = 0;

	if((prev_input == 0 ) && (Hvac_IN.blower_speed3_IN)) // regen switch is connected to Hvac_IN.blower_speed3_IN
	{
		Relay_Control_Switch_OUT.ac_blower3_OUT = !Relay_Control_Switch_OUT.ac_blower3_OUT;
		prev_input = 1;
		//Irp_Mcu_drive_states_29bit-> Regen_On_Brake = 0x0;
		//if(Relay_Control_Switch_OUT.ac_blower3_OUT)
		{
			//enable region cmd
			Irp_Mcu_drive_states_29bit-> Regen_On_Brake = Relay_Control_Switch_OUT.ac_blower3_OUT;
			Irp_Mcu_drive_states_29bit-> Regen_On_Throttle_Realese = Relay_Control_Switch_OUT.ac_blower3_OUT;
		}
	}
	else if(Hvac_IN.blower_speed3_IN == 0)
	{
		prev_input = 0;
	}

}

void Process_RearDefogger(void)
{
	static bool prev_input = 0;

	if((prev_input == 0 ) && (Hvac_IN.ac_solenoid)) // reardefogger switch is connected to Hvac_IN.ac_solenoid
	{
		Relay_Control_Switch_OUT.ac_sol_pwr_out = !Relay_Control_Switch_OUT.ac_sol_pwr_out;

		prev_input = 1;
	}
	else if(Hvac_IN.ac_solenoid == 0)
	{
		prev_input = 0;
	}

}

void Process_FogLamp(void)
{
	static bool prev_input = 0;

	if((prev_input == 0 ) && (Hvac_IN.circulation_on_off)) // fog lamp switch is connected to Hvac_IN.circulation_on_off
	{
		Relay_Control_Switch_OUT.ac_radiator_pwr_out = !Relay_Control_Switch_OUT.ac_radiator_pwr_out; //ac blower speed3 out

		prev_input = 1;
	}
	else if(Hvac_IN.circulation_on_off == 0)
	{
		prev_input = 0;
	}

}


void Process_PowerLatch(void)
{
	static bool prev_input = 0;

	if((prev_input == 0 ) && (Door_Switch_IN.hatch_IN)) // regen switch is connected to door sw hatch in
	{
		Door_Switch_OUT.hatch_OUT = !Door_Switch_OUT.hatch_OUT;

		prev_input = 1;
	}
	else if(Door_Switch_IN.hatch_IN == 0)
	{
		prev_input = 0;
	}

}

void Process_eps_status(void)
{

}


void Process_faciaaswitches(void)
{
	Process_Regen_Control();
	//Process_RearDefogger();
	//Process_FogLamp();
	//Process_PowerLatch();
}

void Flasher(void)
{
/*	if(Combi_Switch_IN.left_indicator_IN)
		{
			Instrument_Cluster_OUT.set_left_indicator = !Instrument_Cluster_OUT.set_left_indicator;
		}
		else if(Combi_Switch_IN.right_indicator_IN)
		{
			Instrument_Cluster_OUT.set_right_indicator = !Instrument_Cluster_OUT.set_right_indicator;
		}*/
	//INTERRUPT_Disable(&INTERRUPT_0);
}

