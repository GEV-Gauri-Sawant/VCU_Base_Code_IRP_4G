/*
 * can_matrix_obc_madhura.c
 *
 *  Created on: 20-Jul-2023
 *      Author: Suchit Sawant
 */
#include "DAVE.h"
#include "can_matrix.h"
#include "Vcu_Init.h"
#include "Vcu_Config.h"

CAN_MSG_t obc_madhura[can_obc_max] =
{
	{0x1806E5F4, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x18FF50E5, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
};

bool charging_detect;

void battery_maxpower(void)
{
	static gun_connect;

	 if((BMS_SOC <= 100) && (!charger_on()))
	 {
		gun_connect = 0;
		obc_madhura[can_0x1806E5F4].CAN_Data[0] = 0x15; // high byte

		obc_madhura[can_0x1806E5F4].CAN_Data[1] = 0x7C; // low byte//20
	 }
	else if((BMS_SOC == 100) && (charger_on()))
	{
		gun_connect = 1;
		obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0X00; // high byte

		obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0X00;//low byte//90

		obc_madhura[can_0x1806E5F4].CAN_Data[0] = 0; // high byte

		obc_madhura[can_0x1806E5F4].CAN_Data[1] = 0; // low byte//20

	}
	if(gun_connect)
	{
		BMS_SOC = 100;
	}
	else if(!gun_connect)
	{

	}

}

void Update_CAN_id0x1806E5F4(void)
{
	CAN_NODE_STATUS_t status;
			    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
			    uint8_t *array_data;

			    /* 55.00V//550 FOR 2.3KW, 5500 FOR 3.2KW, 40amp */

			    /* volatage  */
			    obc_madhura[can_0x1806E5F4].CAN_Data[0] = 0x15; // high byte

			    obc_madhura[can_0x1806E5F4].CAN_Data[1] = 0x7C; // low byte//20

			    battery_maxpower();
			    /* current */
			    //obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0x01; // high byte

			   // obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0x90;//low byte//90

			   // obc_madhura[can_0x1806E5F4].CAN_Data[2] = (((uint16_t)map(BMS_SOC, 0, 100, 600, 20)) >> 8); // high byte

			    //obc_madhura[can_0x1806E5F4].CAN_Data[3] = (((uint8_t)map(BMS_SOC, 0, 100, 20, 600)));//low byte//90

			    switch(BMS_SOC)
			    {
			    case 99 ... 100:
								obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0X00; // high byte

							    obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0X14;//low byte//90
							    break;

			    case 96 ... 98:
			    				obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0X00; // high byte

			    				obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0X64;//low byte//90
			    			    break;

			    case 91 ... 95:
			    				obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0X00; // high byte

			    				obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0XC8;//low byte//90
			    				break;

			    case 81 ... 90:
			    				obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0x00; // high byte

			    				obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0xFA;//low byte//90
			    				break;

			    default:
			    				obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0x02; // high byte

			    				obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0x58;//low byte//90

			    }

			  /*  obc_madhura[can_0x1806E5F4].CAN_Data[2] = 0x00; // high byte

			    obc_madhura[can_0x1806E5F4].CAN_Data[3] = 0x64;//low byte//90*/

			    obc_madhura[can_0x1806E5F4].CAN_Data[4] = 0x00;

			    obc_madhura[can_0x1806E5F4].CAN_Data[5] = 0x00;

			    // V    I
			    //0-80 60
			    //80-90 25
			    //90-95 20
			    //95-98 10
			    //90-100 2
			   // Delay(900);

			    array_data = &obc_madhura[can_0x1806E5F4].CAN_Data[0];

			 //  update data for the MO to transmit
			       status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[27],array_data);

			       if (status == CAN_NODE_STATUS_SUCCESS)
			       {
			         // message object data updated.

			         // transmit the data
			         CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[27]);
			       }
			       else
			       {
			         // message object failed to update.
			       }
}


void Process_CAN_id0x18FF50E5(void)
{
	static once = 0, ccount = 200;
	int test = 0;
uint8_t *tempData, mo_index;
		const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

		mo_index = 28;

		tempData = &obc_madhura[can_0x18FF50E5].CAN_Data[0];

		//read data to external buffer
		CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

		//if(((obc_madhura[can_0x18FF50E5].CAN_Data[4] & 0x1f) == 0x00) && (obc_madhura[can_0x18FF50E5].CAN_Data[2]))
		if(charging_started && (!VehicleSpeedglb))
		{
			//if( obc_madhura[can_0x18FF50E5].CAN_Data[2])
			{
				//Vcu_InPuts.charger_connect_IN = 1;
				if(once == 0)
				{
					digital_io_setoutputhigh(&ORVM_PWR_OUT_D);
					Delay(200);
					//Vcu_InPuts.charger_connect_IN = 1;// changed this and added below
					test = 1;
					once = 1;
				}
				else
				{
					digital_io_setoutputlow(&ORVM_PWR_OUT_D);
					//Vcu_InPuts.charger_connect_IN = 0;
				}
			}
			ccount = 200;
		}
		else if((--ccount) <= 0)
		{
			test = 0;
			once = 0;
			digital_io_setoutputlow(&ORVM_PWR_OUT_D);
			//Vcu_InPuts.charger_connect_IN = 0; // change this and add below
			ccount = 200;
		}

	//7.0,7.1
}

void Read_CAN_id0x18FF50E5(void)
{
	static uint64_t count_in = 0;
	uint8_t test;
			CAN_NODE_STATUS_t status, receive_status;
			XMC_CAN_MO_t *MO_Ptr;
			uint8_t mo_index;
			const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

			mo_index = 28;

			MO_Ptr = HandlePtr1->lmobj_ptr[mo_index]->mo_ptr;

			status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[mo_index]);

			//Vcu_InPuts.charger_connect_IN = 0;
			//Check receive pending status
			if (status & XMC_CAN_MO_STATUS_RX_PENDING)
			{
			  // Clear the flag
			  XMC_CAN_MO_ResetStatus(MO_Ptr,XMC_CAN_MO_RESET_STATUS_RX_PENDING);
			  // Read the received Message object
			  receive_status = CAN_NODE_MO_Receive(HandlePtr1->lmobj_ptr[mo_index]);

			  if (receive_status == CAN_NODE_STATUS_SUCCESS)
			  {
			    // message object receive success.
				  test = 1;
				  //Process_CAN_id0x18FF50E5();
				  count_in = 0;
				  charging_detect = 1; // here added
			  }
			  else
			  {
			    // message object failed to receive.
				  test = 0;
			  }
			  count_in = 0;
			  Vcu_InPuts.charger_connect_IN = 1; // here added
			}
			else
			{
				if(count_in++ > 30)
				{
					Vcu_InPuts.charger_connect_IN = 0; // here added
					count_in = 0;
				}
			}

			Process_CAN_id0x18FF50E5();
}
