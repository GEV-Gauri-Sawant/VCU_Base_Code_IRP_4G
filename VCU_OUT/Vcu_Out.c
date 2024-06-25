/*
 * Vcu_Out.C
 *
 *  Created on: 27-Jun-2023
 *      Author: Suchit Sawant
 */
#include "Vcu_Out.h"
#include "Vcu_Config.h"
#include "Vcu_Init.h"
#include "can_matrix.h"
#include "ADS7961_LIB_2.h"

void OutPutAction_Update(void)
{
	ALL_CONDITION_ON();

	SPI_ADC_ReadAllData(1);

	can_outputs_allState();

	State_1();
	State_2();
	//Can_Outputs_State1();

	/* light */
	Lights_on_off();



	VcuOut_MotorController_IRPbrakes();

	door_en_cabin_light();
}

void charger_tx(void)
{
	/*  obc set v and i */
	Update_CAN_id0x1806E5F4();
}

void Lights_on_off()
{
	/* light */
	if(Lights_OUT.brake_switch_out_d)
	{
		DIGITAL_IO_SetOutputHigh(&BRAKE_LIGHT_OUT_D);
		Gtake_Mcu_drive_states_additional_29bit->Brake_cmd = 1;
	}
	else
	{
		DIGITAL_IO_SetOutputLow(&BRAKE_LIGHT_OUT_D);
		Gtake_Mcu_drive_states_additional_29bit->Brake_cmd = 0;
	}
}

void VcuOut_MotorController_IRPbrakes(void)
{
	Irp_Mcu_drive_states_29bit->Brake_Command = Lights_OUT.brake_switch_out_d;

	Irp_Mcu_drive_states_29bit->Handbrake_Command = !Relay_Control_Switch_OUT.elec_handbrake_pwr_out;
}

void door_en_cabin_light(void)
{
	if((!Door_Switch_OUT.passenger_door_OUT) || (!Door_Switch_OUT.driver_door_OUT) || /*(!Door_Switch_OUT.bonnet_OUT) ||*/ (!Door_Switch_OUT.hatch_OUT))
	{
		digital_io_setoutputhigh(&AC_COMPRESSOR_OUT_D); // for cabin light on doors on/off
	}
	else
	{
		digital_io_setoutputlow(&AC_COMPRESSOR_OUT_D);
	}

}
/*
void cluster_door_out(void)
{
	//cluster_door_out = cluster_door_in;
}
*/
void ALL_CONDITION_ON()
 {
	 DIGITAL_IO_SetOutputHigh(&DOOR_LOCK_PWR_OUT_D);//check j4 -> f1
	 DIGITAL_IO_SetOutputHigh(&LIGHTS_PWR_OUT_D); // Check j4 -> k1
	 DIGITAL_IO_SetOutputHigh(&HORN_PWR_OUT_D);
//	 DIGITAL_IO_SetOutputHigh(&DC_DC_EN_OUT_D); not set here
	 DIGITAL_IO_SetOutputHigh(&HEADLAMPS_ADJ_PWR_OUT_D);
	 DIGITAL_IO_SetOutputHigh(&CABIN_LIGHT_OUT_D);


	// DIGITAL_IO_SetOutputHigh(&AUX_EFUSE_1_OUT_D);//instrument cluster 12v as battery(constant 12v)
	 //digital_io_setoutputhigh(&AUX_EFUSE_3_OUT_D);//bms 12v
	 //digital_io_setoutputhigh(&AUX_EFUSE_2_OUT_D);//GB/T that is for super charge charging connector
	 //digital_io_setoutputhigh(&AUX_EFUSE_5_OUT_D);//obc 12v
 }

 void ALL_CONDITION_OFF()
 {
	 DIGITAL_IO_SetOutputLow(&DOOR_LOCK_PWR_OUT_D);
	 DIGITAL_IO_SetOutputLow(&LIGHTS_PWR_OUT_D);
	 DIGITAL_IO_SetOutputLow(&HORN_PWR_OUT_D);
	 DIGITAL_IO_SetOutputLow(&DC_DC_EN_OUT_D);
	 DIGITAL_IO_SetOutputLow(&HEADLAMPS_ADJ_PWR_OUT_D);
	 DIGITAL_IO_SetOutputLow(&CABIN_LIGHT_OUT_D);


	 //DIGITAL_IO_SetOutputHigh(&AUX_EFUSE_1_OUT_D);//instrument cluster 12v as battery(constant 12v)
	 //digital_io_setoutputlow(&AUX_EFUSE_3_OUT_D);//bms 12v
	 //digital_io_setoutputlow(&AUX_EFUSE_2_OUT_D);//GB/T that is for super charge charging connector
	 //digital_io_setoutputlow(&AUX_EFUSE_5_OUT_D);//obc 12v
 }

void charger_connected_inVoff(void)
{
	if(charger_on())
	{
		Update_CAN_0x18FFB632();
	}
}

void can_outputs_allState(void)
{
	//charger_tx(); // charger can tx
	charger_connected_inVoff();
	OBDII_CAN_Tx();
}

int limphome_Mode(void)
{
	if((Bms_SOC < 10) || (Mcu_Temp > 120))
	{
		Gtake_Mcu_drive_states_29bit ->Drive_mode_cmd = limphome_mode_mcu;
		return 0;
	}
	else
	{
		return 1;
	}

	return 0;
}

int limphome_Mode_IRP(void)
{
	if((Mapped_BMS_SOC < 10) /*|| (Mcu_Temp_Irp > 90)*/)
	{
		Irp_Mcu_drive_states_29bit ->Driving_Profile = Limp_Crawl_irp;
		return 0;
	}
	else
	{
		return 1;
	}

	return 0;
}
