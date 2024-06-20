/*
 * InputCapture.c
 *
 *  Created on: 27-Jun-2023
 *      Author: Suchit Sawant
 */

#include "Vcu_Config.h"
#include "InputCapture.h"
#include "can_matrix.h"
#include "InputCapture/IOExp_lib.h"
#define state1

#define curtis 0
#define gtake 0
#define IRP 1
	//if(Vcu_InPuts.IGNITION_1_IN)
//#endif

Vcu_InPuts_t Vcu_InPuts;
void Input_Capture(void)
{

	//Vcu_InPuts.charger_connect_IN = DIGITAL_IO_GetInput(&CHARGER_CONNECTED_IN_D);

	Vcu_InPuts.IGNITION_1_IN = DIGITAL_IO_GetInput(&IGNI_POS1_IN_D);

	Vcu_InPuts.IGNITION_2_IN = DIGITAL_IO_GetInput(&IGNI_POS2_IN_D);

	Switch_Ios_IN.brake_sw_in_d = DIGITAL_IO_GetInput(&BRAKE_SW_IN_D);

	Switch_Ios_IN.handbrake_sw_IN = DIGITAL_IO_GetInput(&HANDBRAKE_IN_D);

	Switch_Ios_IN.electronic_brake_in_d = DIGITAL_IO_GetInput(&ELEC_HANDBRAKE_IN_D);

	Can_Inputs();

	state_1_InputCapture();
	State_2_InputCapture();

	read_temp();

}

void Can_Inputs(void)
{
	uart_debugg("in can_inputs");
	/*charger read */
			Read_CAN_id0x18FF50E5();

	//CAN_MotorController_init();
#if curtis

		Read_CAN_0x1A6();
		process_Read_CAN_0x1A6();

#elif gtake

		//Read_CAN_0x211(); //gtake 11bit
		//process_Read_CAN_0x211();//gtake 11bit
		Gtake_Rx_29bit();

#elif IRP
//		  SuperLooptime_Start();

		Irp_Rx_29bit();

//		  SuperLooptime_End();

#endif


		//Read_CAN_BMS();//11bit
		Read_can_bms_29bit(); //29 bit
		CAN_INPUT_HVAC();
		CAN_Read_EPS();
		//Read_CAN_EPS();

		/*charger read */
		//Read_CAN_id0x18FF50E5();

		//ruff();

		uart_debugg("exit can_inputs");
}

void read_temp(void)
{


	U18_read_temp();



}

void ruff(void)
{
	uint32_t id = 7, new_id = 0x252;
	//CAN_NODE_MO_UpdateID(lmobj_ptr[7], id);

	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	// uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	uint8_t *array_data, ans = 0x65;
	//CAN_NODE_MO_UpdateID(HandlePtr1->lmobj_ptr[id], new_id);

	//array_data = &CAN_Gtake_29bit[CAN_id0x8000121].CAN_Data[0];
	array_data = &ans;
	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[id],array_data);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.

		// transmit the data
		CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[id]);
	}
	else
	{
		// message object failed to update.
	}


}
