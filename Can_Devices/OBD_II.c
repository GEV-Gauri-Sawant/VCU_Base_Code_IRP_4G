/*
 * OBD_II.c

 *
 *  Created on: 23-Nov-2023
 *      Author: Suchit Sawant
 */


#include "DAVE.h"

#include "can_matrix.h"


OBD_CAN_MSG_t OBDII_CAN[can_OBD_max] =
{
		{0x5E1, {0x00}},
		{0x5E2, {0x00}},
		{0x5E3, {0x00}},
		{0x5E4, {0x00}},
		{0x5E5, {0x00}}
};

void OBDII_CAN_Tx(void)
{
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_2;
	uint8_t *array_data;

/*******************************************bms 0x01******************************************/
	OBDII_CAN[can_0x01].CAN_Data[0] = BMS_SOC; // soc

	OBDII_CAN[can_0x01].CAN_Data[1] = Bms_maxTemp; // temp;

	//OBDII_CAN[can_0x01].CAN_Data[2];//packcurrent H;
	//OBDII_CAN[can_0x01].CAN_Data[3];//packcurrent L;

	OBDII_CAN[can_0x01].CAN_Data[4] = CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[7]; //packvoltage H
	OBDII_CAN[can_0x01].CAN_Data[5] = CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[6]; //packvoltage L

/*******************************************eps 0x02******************************************/


/*******************************************hvac 0x03******************************************/
	 OBDII_CAN[can_0x03].CAN_Data[0] = CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[0]; //TempdegreeC
	 OBDII_CAN[can_0x03].CAN_Data[1] = CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[1]; //Pressure

	 OBDII_CAN[can_0x03].CAN_Data[2] = CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[2]; //1: AC switch on,  0: AC switch off,

	 OBDII_CAN[can_0x03].CAN_Data[3] = CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[1]; //AC rpm H
	 OBDII_CAN[can_0x03].CAN_Data[4] = CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[0]; //AC rpm L

	 OBDII_CAN[can_0x03].CAN_Data[5] = CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[3]; //AC ON -> compressor enable bit


/*******************************************gtake 0x04******************************************/

	 //OBDII_CAN[can_0x04].CAN_Data[0]; //rpm H
	 //OBDII_CAN[can_0x04].CAN_Data[1]; //rpm L

	 //OBDII_CAN[can_0x04].CAN_Data[2]; //throttle percentage H
	 //OBDII_CAN[can_0x04].CAN_Data[3]; //throttle percentage L

	//OBDII_CAN[can_0x04].CAN_Data[4]; //speed H
	 //OBDII_CAN[can_0x04].CAN_Data[5]; //speed L

	 OBDII_CAN[can_0x04].CAN_Data[6] = Mcu_Temp;
	 OBDII_CAN[can_0x04].CAN_Data[7] = Motor_Temp;

/*******************************************madhura 0x05******************************************/

	 OBDII_CAN[can_0x05].CAN_Data[0] = obc_madhura[can_0x18FF50E5].CAN_Data[0]; // voltage H
	 OBDII_CAN[can_0x05].CAN_Data[1] = obc_madhura[can_0x18FF50E5].CAN_Data[1]; // voltage L

	 OBDII_CAN[can_0x05].CAN_Data[2] = obc_madhura[can_0x18FF50E5].CAN_Data[2]; // current H
	 OBDII_CAN[can_0x05].CAN_Data[3] = obc_madhura[can_0x18FF50E5].CAN_Data[3]; // current L

	 OBDII_CAN[can_0x05].CAN_Data[4] = obc_madhura[can_0x18FF50E5].CAN_Data[4]; // 0:Charger turned on, 1:Battery Protection, Charger Shutdown Output
	 OBDII_CAN[can_0x05].CAN_Data[5] = obc_madhura[can_0x18FF50E5].CAN_Data[5]; // 0:charging mode, 1:Heating mode while charging, 2: heating mode


	 for(int i = 0; i < can_OBD_max; i++)
	 {
		 array_data = &OBDII_CAN[i].CAN_Data[0];

		 //  update data for the MO to transmit
		 status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[i],array_data);

		 if (status == CAN_NODE_STATUS_SUCCESS)
		 {
		    // message object data updated.

		    // transmit the data
		    CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[i]);
		 }
		 else
		 {
		     // message object failed to update.
		 }
	 }
}





