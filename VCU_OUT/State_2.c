/*
 * State_2.c
 *
 *  Created on: 28-Jun-2023
 *      Author: Suchit Sawant
 */

#include "Vcu_Out.h"
#include "Vcu_Config.h"
#include "can_matrix.h"
#include "Vcu_Init.h"

Gear_OUT_t *Gear_OUT = (Gear_OUT_t *) &(CAN_MSG_DB[CAN_18FFC621].CAN_Data[4]);
Gtake_Mcu_tx_id0x121_t *Gtake_Mcu_drive_states = (Gtake_Mcu_tx_id0x121_t *)&(CAN_MSG_DB_GTAKE[CAN_0x121].CAN_Data[0]);
Gtake_tx_0x8000121_t *Gtake_Mcu_drive_states_29bit = (Gtake_tx_0x8000121_t *)&(CAN_Gtake_29bit[CAN_id0x8000121].CAN_Data[0]);
Gtake_tx_0x8000111_t *Gtake_Mcu_drive_states_additional_29bit = (Gtake_tx_0x8000111_t *)&(CAN_Gtake_29bit[CAN_id0x8000111].CAN_Data[0]);
IRP_Mcu_tx_id0x10_t *Irp_Mcu_drive_states_29bit = (IRP_Mcu_tx_id0x10_t *)&CAN_IRP_29bit[CAN_id0x10].CAN_Data[0];
IRP_Mcu_tx_id0x20_t *Irp_Mcu_BMS_states_29bit = (IRP_Mcu_tx_id0x20_t *)&CAN_IRP_29bit[CAN_id0x20].CAN_Data[0];
IRP_Mcu_tx_id0x21_t *Irp_Mcu_BMS_Currents_29bit = (IRP_Mcu_tx_id0x21_t *)&CAN_IRP_29bit[CAN_id0x21].CAN_Data[0];
IRP_Mcu_rx_id0x13_t *Irp_Mcu_Torques_29bit = (IRP_Mcu_rx_id0x13_t *)&CAN_IRP_29bit[CAN_id0x13].CAN_Data[0];
IRP_Mcu_rx_id0x12_t *Irp_MCU_Status_29bit = (IRP_Mcu_rx_id0x12_t *)&CAN_IRP_29bit[CAN_id0x12].CAN_Data[0];


enum Gearchange_Sequence_forHzaard_t{not_allowed, allowed };


void State_2(void)
{
	if(Vcu_OutPuts.IGNITION_2_OUT)
	{

		/* ignition 2 on state */
		ignition2_d_on();
		VcuOut_MotorController();

		Can_Outputs_State2();




		//State2_Lights();

	}
	else if(!(Vcu_OutPuts.IGNITION_2_OUT))
	{

		/* ignition 2 off state */
		ignition2_d_off();


		VcuOut_MotorController_off();
	}

	State2_Lights();
}


void ignition2_d_on()
{
	/* ignition 2 by default on */
	digital_io_setoutputhigh(&SUNROOF_PWR_OUT_D);//irp_12v supply
	//ignition_default_state_MC();
	DIGITAL_IO_SetOutputHigh(&PWR_STEERING_OUT_D);/// power steering// check
	DIGITAL_IO_SetOutputHigh(&VACUUM_PUMP_OUT_D); // check

	//DIGITAL_IO_SetOutputHigh(&MC_RELAY_PWR_OUT_D); // common for everything giving 12v to mc every relay IN VCU13(IN 14 DIRCTLY GOES TO OCNTROLLER FAN)
	DIGITAL_IO_SetOutputHigh(&MC_RELAY_PWR_OUT_D);

	DIGITAL_IO_SetOutputHigh(&AUX_EFUSE_1_OUT_D); // common for everything giving 12v to mc every relay IN VCU14

	DIGITAL_IO_SetOutputHigh(&MC_REGEN_RELAY_OUT_D); // on relay, relay_driver_pin as output

	DIGITAL_IO_SetOutputHigh(&MC_ELOCK_RELAY_OUT_D); // start relay , relay_driver_pin as output

	DIGITAL_IO_SetOutputHigh(&MC_FAN_PWR_OUT_D);  // start, on, fwd, rev relay output side

	DIGITAL_IO_SetOutputHigh(&MC_REV_RELAY_OUT_D);//in irp contactor +ve is coming from harness and -ve controlled by rev
	//digital_io_setoutputhigh(&SUNROOF_PWR_OUT_D);//irp_12v supply
	Irp_Mcu_drive_states_29bit->Ignition_Key_indicator = 1;
}

void ignition2_d_off()
{
	DIGITAL_IO_SetOutputLow(&PWR_STEERING_OUT_D);/// power steering
	DIGITAL_IO_SetOutputLow(&VACUUM_PUMP_OUT_D);

	//DIGITAL_IO_SetOutputLow(&MC_RELAY_PWR_OUT_D);

	DIGITAL_IO_SetOutputLow(&MC_ELOCK_RELAY_OUT_D);

	DIGITAL_IO_SetOutputLow(&MC_REGEN_RELAY_OUT_D);

	DIGITAL_IO_SetOutputLow(&MC_FAN_PWR_OUT_D);

	DIGITAL_IO_SetOutputLow(&AUX_EFUSE_1_OUT_D); // common for everything giving 12v to mc every relay IN VCU14

	DIGITAL_IO_SetOutputLow(&MC_RELAY_PWR_OUT_D);

	DIGITAL_IO_SetOutputLow(&REV_LIGHT_OUT_D);

	DIGITAL_IO_SetOutputLow(&MC_REV_RELAY_OUT_D);//in irp contactor +ve is coming from harness and -ve controlled by rev
	digital_io_setoutputlow(&SUNROOF_PWR_OUT_D);//irp_12v supply
	Irp_Mcu_drive_states_29bit->Ignition_Key_indicator = 0;
}

void all_ig2_direct_controlled_off(void)
{

}

void Can_Outputs_State2(void)
{
	CAN_OUTPUT_EPS();
	//Gtake_Tx_29bit();

	Irp_Tx_29bit();

	//Tx_CAN_0x121();
}

void VcuOut_MotorController(void)
{
	//VcuOut_MotorController_Gtake();
	VcuOut_MotorController_IRP();
}

void VcuOut_MotorController_Gtake(void)
{

static enum Gearchange_Sequence_forHzaard_t Gearchange_Sequence_forHzaard = not_allowed;

	if(Lights_OUT.brake_switch_out_d && (!VehicleSpeedglb)/*&& (limphome_Mode())*/)
	{
		//Gearchange_Sequence_forHzaard = not_allowed;
		if(Motor_controller_OUT.forward_Relay )
		{
			if(Gearchange_Sequence_forHzaard)
			{
				/*DIGITAL_IO_SetOutputHigh(&MC_FWD_RELAY_OUT_D);
				DIGITAL_IO_SetOutputLow(&MC_REV_RELAY_OUT_D);
				DIGITAL_IO_SetOutputLow(&MC_PARK_RELAY_OUT_D);*/

				Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = 1; // see drive mode
				Gtake_Mcu_drive_states_29bit ->Motor_direction_cmd = fwd;
				//Gtake_Mcu_drive_states -> Drive_mode_cmd = 2;
				//Gtake_Mcu_drive_states -> Motor_direction_cmd = 000;
				Gear_OUT-> forward = 0x00;
			}
			Gearchange_Sequence_forHzaard = not_allowed;
		}
		else if (Motor_controller_OUT.reverse_relay)
		{
			if(Gearchange_Sequence_forHzaard)
			{
				/*DIGITAL_IO_SetOutputHigh(&MC_REV_RELAY_OUT_D);
				DIGITAL_IO_SetOutputLow(&MC_FWD_RELAY_OUT_D);
				DIGITAL_IO_SetOutputLow(&MC_PARK_RELAY_OUT_D);*/

				//Gtake_Mcu_drive_states -> Drive_mode_cmd = 2;
				Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = 1;
				Gtake_Mcu_drive_states_29bit ->Motor_direction_cmd = rev;
				//Gtake_Mcu_drive_states -> Motor_direction_cmd = 001;

				Gear_OUT-> reverse = 0x03;
			}
			Gearchange_Sequence_forHzaard = not_allowed;
		}
		else if (Motor_controller_OUT.park_relay)
		{
			/*DIGITAL_IO_SetOutputHigh(&MC_PARK_RELAY_OUT_D);
			DIGITAL_IO_SetOutputLow(&MC_FWD_RELAY_OUT_D);
			DIGITAL_IO_SetOutputLow(&MC_REV_RELAY_OUT_D);*/

			if(Gear_OUT-> reverse == 0x03)
				Gtake_Mcu_drive_states_29bit ->Motor_direction_cmd = 00;

			Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = 0;
			Gear_OUT-> park = 0x02;
		}
		else if(Motor_controller_OUT.neutral)
		{

			/*DIGITAL_IO_SetOutputLow(&MC_FWD_RELAY_OUT_D);
			DIGITAL_IO_SetOutputLow(&MC_REV_RELAY_OUT_D);
			DIGITAL_IO_SetOutputLow(&MC_PARK_RELAY_OUT_D);*/

			//Gtake_Mcu_drive_states -> Drive_mode_cmd = 0x000;
			if(Gear_OUT-> reverse == 0x03)
				Gtake_Mcu_drive_states_29bit ->Motor_direction_cmd = 00;

			Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = 0; //00;
			Gear_OUT-> neutral = 0x01;

			//Gearchange_Sequence_forHzaard = not_allowed;
			//if(Lights_OUT.brake_switch_out_d && (!VehicleSpeedglb))
			Gearchange_Sequence_forHzaard = allowed;
		}
	}
	else
	{
		Gearchange_Sequence_forHzaard = not_allowed;
	}
	//limphome_Mode();
}


void VcuOut_MotorController_IRP(void)
{

	static enum Gearchange_Sequence_forHzaard_t Gearchange_Sequence_forHzaard = not_allowed;

	VcuOut_MotorController_IRP_BMS_Status();

	if(Lights_OUT.brake_switch_out_d && (!VehicleSpeedglb)/*&& (limphome_Mode_IRP())*/)
	{
		//Gearchange_Sequence_forHzaard = not_allowed;
		if(Motor_controller_OUT.forward_Relay )
		{
			if(Gearchange_Sequence_forHzaard)
			{
				Irp_Mcu_drive_states_29bit->FNR = Forward_Irp;
				Gear_OUT-> forward = 0x00;
			}
			Gearchange_Sequence_forHzaard = not_allowed;
		}
		else if (Motor_controller_OUT.reverse_relay)
		{
			if(Gearchange_Sequence_forHzaard)
			{
				Irp_Mcu_drive_states_29bit->FNR = Reverse_Irp;
				Gear_OUT-> reverse = 0x03;
			}
			Gearchange_Sequence_forHzaard = not_allowed;
		}
		else if (Motor_controller_OUT.park_relay)
		{
			Irp_Mcu_drive_states_29bit->FNR = Neutral_Irp; //there is no option for irp
			Gear_OUT-> park = 0x02;
		}
		else if(Motor_controller_OUT.neutral)
		{
			Irp_Mcu_drive_states_29bit->FNR = Neutral_Irp;
			Gear_OUT-> neutral = 0x01;
			Gearchange_Sequence_forHzaard = allowed;
		}
	}
	else
	{
		Gearchange_Sequence_forHzaard = not_allowed;
	}

	limphome_Mode_IRP();

}

void VcuOut_MotorController_off(void)
{
	//VcuOut_MotorController_off_gtake();
	VcuOut_MotorController_off_IRP();

}
void VcuOut_MotorController_off_gtake(void)
{
	DIGITAL_IO_SetOutputLow(&MC_RELAY_PWR_OUT_D);
	DIGITAL_IO_SetOutputLow(&MC_FWD_RELAY_OUT_D);
	DIGITAL_IO_SetOutputLow(&MC_REV_RELAY_OUT_D);
	DIGITAL_IO_SetOutputLow(&MC_PARK_RELAY_OUT_D);

	Gtake_Mcu_drive_states -> Drive_mode_cmd = 0x000;
	Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = 0;
	Gear_OUT-> neutral = 0x01;

}
void VcuOut_MotorController_off_IRP(void)
{
	Irp_Mcu_drive_states_29bit->FNR = Neutral_Irp;
	Irp_Mcu_drive_states_29bit->Throttle_Command = 1023;
	Irp_Mcu_drive_states_29bit->Torque_Command = 0;
	Irp_Mcu_drive_states_29bit->Ignition_Key_indicator = 0;

	Gear_OUT-> neutral = 0x01;

	//Irp_Mcu_drive_states_29bit-> Regen_On_Brake = 0;//(uint8_t )Relay_Control_Switch_OUT.ac_blower3_OUT;
	//Irp_Mcu_drive_states_29bit-> Regen_On_Throttle_Realese = 0;//(uint8_t)Relay_Control_Switch_OUT.ac_blower3_OUT;


	//DIGITAL_IO_SetOutputLow(&MC_REV_RELAY_OUT_D); //in irp contactor +ve is coming from harness and -ve controlled by rev
}

void VcuOut_MotorController_IRP_BMS_Status(void)
{
	//Irp_Mcu_drive_states_29bit -> Driving_Profile = 3;

	Irp_Mcu_BMS_states_29bit->BMS_OperationMode = 5;
	Irp_Mcu_BMS_states_29bit->BMS_Contactor_Status = 1;
	Irp_Mcu_BMS_states_29bit->SOH = Bms_SOH;
	Irp_Mcu_BMS_states_29bit->BMS_SOC = Bms_SOC;

	Irp_Mcu_BMS_Currents_29bit->Battery_Voltage = PackVoltage;//50
	Irp_Mcu_BMS_Currents_29bit->Battery_Current = PackCurrent;//20
	Irp_Mcu_BMS_Currents_29bit->MaxDischargeCurrent = 450;//DischargeCurrentLimit * -1;//20;
	Irp_Mcu_BMS_Currents_29bit->MaxRechargeCurrent = -1 * RegenerativeCurrentLimit;//ChargeCurrentLimit;//0;

}

void State2_Lights(void)
{
	if((Lights_OUT.brake_switch_out_d))
	{
		if((Lights_OUT.reverse_light_out))
		{
			DIGITAL_IO_SetOutputHigh(&REV_LIGHT_OUT_D);
		}
		else
		{
			DIGITAL_IO_SetOutputLow(&REV_LIGHT_OUT_D);
		}
	}
}
