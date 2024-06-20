/*
 * State_1.c
 *
 *  Created on: 28-Jun-2023
 *      Author: Suchit Sawant
 */
#include "Vcu_Out.h"
#include "Vcu_Config.h"
#include "DAVE.h"
#include "Vcu_Init.h"
#include "can_matrix.h"
#include "ADS7961_LIB_2.h"

/*instrument_clustor_indicators_t *instrument_clustor_indicators = &CAN_MSG_DB[CAN_18FFB632];*/


void State_1(void)
{
	if(Vcu_OutPuts.IGNITION_1_OUT)
	{
		/* ignition 1 on state */
		ignition1_d_on();
		faciaaswitches();
		Can_Outputs_State1();
		cluster_indicators_Out();
	}
	else if(!(Vcu_OutPuts.IGNITION_1_OUT))
	{
		//check battery voltage and turn on/off DC to DC converter
		dc_dc_state_update(); //test this later
		/* ignition 1 off state */
		ignition1_d_off();
		all_direct_controlled_relay_off();
	}

	VcuOut_IoExp_U24();
	VcuOut_IoExp_U25();

}
void ignition1_d_on()
 {
	uart_debugg("in ig1_d_on");
	/*CAN_MSG_DB[CAN_18FF0921].CAN_Data[5] = 0x1c;
	CAN_MSG_DB[CAN_18FF0921].CAN_Data[6] = 0x0c;

	CAN_MSG_DB[CAN_0CF00400].CAN_Data[3] = 0x48;
	CAN_MSG_DB[CAN_0CF00400].CAN_Data[4] = 0x71;*/

 	DIGITAL_IO_SetOutputHigh(&CIGARETTE_LIGHTER_PWR_OUT_D);//
 	DIGITAL_IO_SetOutputHigh(&INFOTAINMENT_PWR_OUT_D); // check infotainment port & pin
 	DIGITAL_IO_SetOutputHigh(&INSTRUMENT_CON_PWR_OUT_D);
 	DIGITAL_IO_SetOutputHigh(&WIPER_PWR_OUT_D);

 	DIGITAL_IO_SetOutputHigh(&CABIN_LIGHT_OUT_D);

 	//IOExp_SetPIN_LOW(&I2C_MASTER_1, 0x40, 0, 0);
 	digital_io_setoutputhigh(&AC_BLOWER_SPEED1_OUT_D); /// turn on HVAC(CPIS)
 	digital_io_setoutputhigh(&AC_BLOWER_SPEED2_OUT_D); /// turn on COMPRESSOR PWR.

 	DIGITAL_IO_SetOutputHigh(&PWR_WINDOW_OUT_D);

 	//digital_io_setoutputhigh(&SUNROOF_PWR_OUT_D);//irp_12v supply
 	/*  active low */
 	//digital_io_setoutputlow(&AUX_EFUSE_4_OUT_D);

 	uart_debugg("exit ig1_d_on");
 }

 void ignition1_d_off()
 {

	 /*CAN_MSG_DB[CAN_18FF0921].CAN_Data[5] = 0x00;
	  CAN_MSG_DB[CAN_18FF0921].CAN_Data[6] = 0x00;*/
//for(volatile int i = 0; i<0xffff*80; i++);
	  /*CAN_MSG_DB[CAN_0CF00400].CAN_Data[3] = 0x38;
	  CAN_MSG_DB[CAN_0CF00400].CAN_Data[4] = 0x18;*/
	 uart_debugg("in ig1_d_off");
 	DIGITAL_IO_SetOutputLow(&CIGARETTE_LIGHTER_PWR_OUT_D);//
 	DIGITAL_IO_SetOutputLow(&INFOTAINMENT_PWR_OUT_D);
 	DIGITAL_IO_SetOutputLow(&INSTRUMENT_CON_PWR_OUT_D);
 	DIGITAL_IO_SetOutputLow(&WIPER_PWR_OUT_D);

 	//DIGITAL_IO_SetOutputLow(&CABIN_LIGHT_OUT_D);

 	DIGITAL_IO_SetOutputLow(&PWR_WINDOW_OUT_D);

 	digital_io_setoutputlow(&AC_BLOWER_SPEED1_OUT_D); /// turn off HVAC(CPIS)
 	digital_io_setoutputlow(&AC_BLOWER_SPEED2_OUT_D); /// turn off COMPRESSOR PWR.
 	DIGITAL_IO_SetOutputLow(&AC_RADIATOR_OUT_D);

 	/* active low */
 	digital_io_setoutputlow(&AUX_EFUSE_4_OUT_D);

 	//digital_io_setoutputlow(&SUNROOF_PWR_OUT_D);//irp_12v supply

 	uart_debugg("in ig1_d_off");

 }

 void all_direct_controlled_relay_off(void)
 {
	 DIGITAL_IO_SetOutputLow(&MC_CONTACTOR_RELAY_OUT_D);
 }

  void Can_Outputs_State1(void)
 {
 	CAN_OUTPUT_COMPRESSOR();
 	CAN_OUTPUT_CLUSTER();
 	//CAN_OUTPUT_EPS();
 }

 void cluster_indicators_Out(void)
 {
	instrument_clustor_indicators-> left_indicator = Instrument_Cluster_OUT.set_left_indicator;
  	instrument_clustor_indicators-> right_indicator = Instrument_Cluster_OUT.set_right_indicator;
  	instrument_clustor_indicators-> low_beam = Instrument_Cluster_OUT.set_low_beam;
  	instrument_clustor_indicators-> high_beam = Instrument_Cluster_OUT.set_high_beam;
  	instrument_clustor_indicators-> brake_fluid_flow = Instrument_Cluster_OUT.set_brake_oil;
  	instrument_clustor_indicators-> eps_failure = Instrument_Cluster_OUT.eps_status;///////
  	instrument_clustor_indicators-> aux_battery_low = Instrument_Cluster_OUT.aux_vtg_critical;
  	instrument_clustor_indicators-> battery_high_temp = Instrument_Cluster_OUT.battery_temp_exceeded;
  	instrument_clustor_indicators-> charging_on = Instrument_Cluster_OUT.charging_connected;
  	instrument_clustor_indicators-> generic_alarm;/////////
  	instrument_clustor_indicators-> regen = Instrument_Cluster_OUT.regen_enabled;///////////
  	instrument_clustor_indicators-> parking_brake_light = !Switch_Ios_IN.handbrake_sw_IN;
  	instrument_clustor_indicators-> seat_belt = Seat_Belt_OUT.seat_occupied;
  }

 void VcuOut_IoExp_U24(void)
 {
	 uart_debugg("in U24");
	 if(Relay_Control_Switch_OUT.low_beam_OUT)
	 {
		 DIGITAL_IO_SetOutputHigh(&LOW_BEAM_OUT_D);
		// Gtake_Mcu_drive_states_additional_29bit->Hill_hold_assist = 1;
	 }
	 else
	 {
		 DIGITAL_IO_SetOutputLow(&LOW_BEAM_OUT_D);
		// Gtake_Mcu_drive_states_additional_29bit->Hill_hold_assist = 0;
	 }

	 if(Relay_Control_Switch_OUT.high_beam_OUT)
	 {
		 DIGITAL_IO_SetOutputHigh(&HIGH_BEAM_OUT_D);
	 }
	 else
	 {
		 DIGITAL_IO_SetOutputLow(&HIGH_BEAM_OUT_D);
	 }

	 if(Relay_Control_Switch_OUT.pos_light_OUT) /// pos light
	 {
		 DIGITAL_IO_SetOutputHigh(&POS_OUT_D);
		 //digital_io_setoutputhigh(&AUX_EFUSE_4_OUT_D);
	 }
	 else
	 {
		 DIGITAL_IO_SetOutputLow(&POS_OUT_D);
		// digital_io_setoutputlow(&AUX_EFUSE_4_OUT_D);
	 }

	 if(Relay_Control_Switch_OUT.left_indicator_OUT)
	 {
		 DIGITAL_IO_SetOutputHigh(&LEFT_INDICATOR_OUT_D);
	 }
	 else
	 {
		 DIGITAL_IO_SetOutputLow(&LEFT_INDICATOR_OUT_D);
	 }

	 if(Relay_Control_Switch_OUT.right_indicator_OUT)
	 {
		 DIGITAL_IO_SetOutputHigh(&RIGHT_INDICATOR_OUT_D);
	 }
	 else
	 {
		 DIGITAL_IO_SetOutputLow(&RIGHT_INDICATOR_OUT_D);
	 }

	 uart_debugg("exit U24");
 }

 void VcuOut_IoExp_U25(void)
  {

 	 if(Relay_Control_Switch_OUT.ac_blower1_OUT)
 	 {
 		// DIGITAL_IO_SetOutputHigh(&LOW_BEAM_OUT_D);
 	 }
 	 else
 	 {
 		 //DIGITAL_IO_SetOutputLow(&LOW_BEAM_OUT_D);
 	 }

 	 if(Relay_Control_Switch_OUT.ac_blower2_OUT)
 	 {
 		// DIGITAL_IO_SetOutputHigh(&HIGH_BEAM_OUT_D);
 	 }
 	 else
 	 {
 		// DIGITAL_IO_SetOutputLow(&HIGH_BEAM_OUT_D);
 	 }

 }

 void VcuOut_IoExp_U38(void)
 {

 }

 void VcuOut_IoExp_U48(void)
 {

 }

 void faciaaswitches(void)
 {
	 if(Relay_Control_Switch_OUT.pos_light_OUT) /// pos light
	{
		digital_io_setoutputhigh(&AUX_EFUSE_4_OUT_D);
	}
	else
	{
		digital_io_setoutputlow(&AUX_EFUSE_4_OUT_D);
	}

 }

 //check 12V battery voltage, if less than 12.5V then start DC to DC converter and 48V battery and if greater than 13.5 then turn off DC to DC converter and 48V battery
//only in ignition off mode as in ignition on mode DC to DC and 48V battery is always ON.
//we can also add a flag to check if DC to DC converter is already on or not
void dc_dc_state_update(void)
{
	static bool dc_dc_started = false;

	DROPPED_IN_12_volt(); //update voltage value
	if (DROPPED_IN_12V < 12.50f)
//	if (DROPPED_IN_12V > 12.0f && DROPPED_IN_12V < 12.50f) //added for testing
	{
		//AUX_EFUSE_3_OUT_D output is connected to 48V battery input
		digital_io_setoutputhigh(&AUX_EFUSE_3_OUT_D); //48V battery
		//DIGITAL_IO_SetOutputLow(&DC_DC_EN_OUT_D); //FOR TRIPHASE DC TO DC converter
		DIGITAL_IO_SetOutputHigh(&DC_DC_EN_OUT_D); //for Madhura DC TO DC converter
		dc_dc_started = true;
	}
	else if (DROPPED_IN_12V > 13.50f)
	{
		//AUX_EFUSE_3_OUT_D output is connected to 48V battery input
		digital_io_setoutputlow(&AUX_EFUSE_3_OUT_D); //48V battery
		//DIGITAL_IO_SetOutputHigh(&DC_DC_EN_OUT_D); //FOR TRIPHASE DC TO DC converter
		DIGITAL_IO_SetOutputLow(&DC_DC_EN_OUT_D); //for Madhura DC TO DC converter
		dc_dc_started = false;
	}
	//when DC to DC is not started
	else if (dc_dc_started == false)
	{
		//if voltage is within range then do not turn on 48V battery as well as DC to DC converter
		digital_io_setoutputlow(&AUX_EFUSE_3_OUT_D);
		DIGITAL_IO_SetOutputLow(&DC_DC_EN_OUT_D);
	}
}
