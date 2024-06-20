/*
 * can_matrix_mc_gtake_29bit.c
 *
 *  Created on: 24-Aug-2023
 *      Author: Suchit Sawant
 */
#include "DAVE.h"
#include "can_matrix.h"

CAN_MSG_t CAN_Gtake_29bit[CAN_Gtake_Total_id29bit] =
{
	{0x8000201,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000211,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000221,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000230,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000231,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000241,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000121,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x8000111,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
};


void CAN_Tx_id0x8000121(void)
{
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	// uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	uint8_t *array_data;

	array_data = &CAN_Gtake_29bit[CAN_id0x8000121].CAN_Data[0];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[30],array_data);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.

		// transmit the data
		CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[30]);
	}
	else
	{
		// message object failed to update.
	}

}

void CAN_Tx_id0x8000111(void)
{
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	// uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	uint8_t *array_data;

	array_data = &CAN_Gtake_29bit[CAN_id0x8000111].CAN_Data[0];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[31],array_data);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.

		// transmit the data
		CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[31]);
	}
	else
	{
		// message object failed to update.
	}

}

void CAN_Rx_id8000211(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = 17;//CAN_RX_MO_GTAKE_BASE + CAN_0x211;

    MO_Ptr = HandlePtr1->lmobj_ptr[mo_index]->mo_ptr;

    status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[mo_index]);
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
      }
      else
      {
        // message object failed to receive.
          test = 0;
      }
    }


    process_Rx_CAN_0x8000211();
}



void CAN_Rx_id8000221(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = 18;//CAN_RX_MO_GTAKE_BASE + CAN_0x211;

    MO_Ptr = HandlePtr1->lmobj_ptr[mo_index]->mo_ptr;

    status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[mo_index]);
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
      }
      else
      {
        // message object failed to receive.
          test = 0;
      }
    }


    process_Rx_CAN_0x8000221();
}

void CAN_Rx_id8000231(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = 19;//CAN_RX_MO_GTAKE_BASE + CAN_0x211;

    MO_Ptr = HandlePtr1->lmobj_ptr[mo_index]->mo_ptr;

    status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[mo_index]);
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
      }
      else
      {
        // message object failed to receive.
          test = 0;
      }
    }


    process_Rx_CAN_0x8000231();
}


void process_Rx_CAN_0x8000211(void)
{

    /*  INT_MIN -32767
        INT_MAX +32767
    */

    uint8_t mo_index, *tempData;
    uint8_t CAN_rawData[8];
    uint16_t RPM, ThrottlePercentage = 6;
    uint16_t VehSpeed;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = 17;//CAN_TX_MO_COUNT_GTAKE + CAN_0x211;

    //unnecessary, but keep for the moment
    tempData = &CAN_Gtake_29bit[CAN_id0x8000211].CAN_Data[ZERO_BYTE];
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

//  tempData = &CAN_MSG_DB_MC[CAN_0x1A6].CAN_Data[ZERO_BYTE];

  /*  tempData = &CAN_rawData[0];
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);*/

    //perform the conversion and then store
//    TempRPM = CAN_rawData[5]; --> 5 for curtis
//    TempRPM = ((TempRPM << 8) | CAN_rawData[4]);

    //RPM = CAN_rawData[3];	//--> 3 for gtake
    RPM = (((uint16_t)tempData[3] << 8) | tempData[4]);

    OBDII_CAN[can_0x04].CAN_Data[0] = tempData[3];
    OBDII_CAN[can_0x04].CAN_Data[1] = tempData[4];
    ///
    current_rpm = RPM;

    ////

    //calculate speed here from motor RPM
    VehSpeed = calculate_speed(RPM);

    /////
    vspeed = VehSpeed; // dont use 'vspeed' it is getting modify somewhere else
    ///////


    if(VehSpeed > 100)
        VehSpeed = 100;


    //ThrottlePercentage = tempData[0] * 1000 + 15;
    //ThrottlePercentage = 64000;
    ThrottlePercentage =  map(VehSpeed, 0, 100, 6200, 64000);
    OBDII_CAN[can_0x04].CAN_Data[3] = CAN_MSG_DB[CAN_0CF00400].CAN_Data[THIRD_BYTE] = ThrottlePercentage;
    OBDII_CAN[can_0x04].CAN_Data[2] = CAN_MSG_DB[CAN_0CF00400].CAN_Data[FOURTH_BYTE] = (ThrottlePercentage >> 8);

    if(VehSpeed)
    	VehSpeed = 104.11* VehSpeed + 226.99;

    OBDII_CAN[can_0x04].CAN_Data[5] = CAN_MSG_DB[CAN_18FF0921].CAN_Data[FIFTH_BYTE] = (VehSpeed);
    OBDII_CAN[can_0x04].CAN_Data[4] = CAN_MSG_DB[CAN_18FF0921].CAN_Data[SIXTH_BYTE] = (VehSpeed >> 8U);

    VehicleSpeedglb = VehSpeed;
}

void process_Rx_CAN_0x8000221(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 18;//CAN_RX_MO_BMS_BASE + CAN_0x102;

	tempData = &CAN_MSG_DB_BMS[CAN_id0x8000221].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	Mcu_Temp = CAN_MSG_DB_BMS[CAN_id0x8000221].CAN_Data[ZERO_BYTE];
	Motor_Temp = CAN_MSG_DB_BMS[CAN_id0x8000221].CAN_Data[1];

}


void process_Rx_CAN_0x8000231(void)
{
	uint8_t *tempData, mo_index, Temp2;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 19;//CAN_RX_MO_BMS_BASE + CAN_0x102;

	tempData = &CAN_MSG_DB_BMS[CAN_id0x8000231].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	Temp2 = CAN_MSG_DB_BMS[CAN_id0x8000231].CAN_Data[ZERO_BYTE];
	//Motor_Temp = CAN_MSG_DB_BMS[CAN_id0x8000231].CAN_Data[1];

}

void Gtake_Tx_29bit(void)
{
	CAN_Tx_id0x8000121();
	CAN_Tx_id0x8000111();
}

void Gtake_Rx_29bit(void)
{
	CAN_Rx_id8000211();
	CAN_Rx_id8000221();
	CAN_Rx_id8000231();
}
