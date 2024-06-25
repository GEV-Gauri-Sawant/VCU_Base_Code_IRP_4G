/*
 * can_matrix_mc_irp.c
 *
 *  Created on: 10-Jan-2024
 *  Author: Suchit Sawant
 */
#include "DAVE.h"
#include "can_matrix.h"

CAN_MSG_t CAN_IRP_29bit[CAN_IRP_Total_id29bit] =
{
		{0x10,{0x00}},
		{0x11,{0x00}},
		{0x12,{0x00}},
		{0x13,{0x00}},
		{0x20,{0x00}},
		{0x21,{0x00}},
		{0x30,{0x00}},
		{0x31,{0x00}},
		{0x32,{0x00}},
		{0x33,{0x00}},
		{0x55,{0x00}}
};

void CAN_Tx_id0x10(void)
{
	    CAN_NODE_STATUS_t status;
	    XMC_CAN_MO_t *MO_Ptr;
	    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;
	    MO_Ptr = HandlePtr1->lmobj_ptr[16]->mo_ptr;

	    uint8_t *array_data;

	    array_data = &CAN_IRP_29bit[CAN_id0x10].CAN_Data[0];


	      //  update data for the MO to transmit
	      status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[16],array_data);

	      if (status == CAN_NODE_STATUS_SUCCESS)
	      {
	        // message object data updated.

	        // transmit the data
	    	  status = CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[16]);
	    	  if (status == CAN_NODE_STATUS_SUCCESS)
	    	  {
	    	       status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[16]);

	    	        if (status &  XMC_CAN_MO_STATUS_TX_PENDING)
	    	        {
	    	          //Clear the transmit OK flag
	    	          XMC_CAN_MO_ResetStatus(MO_Ptr,XMC_CAN_MO_RESET_STATUS_TX_PENDING);
	    	        }
	    	  }
	      }
	      else
	      {
	        // message object failed to update.
	      }

}

void CAN_Tx_id0x20(void)
{
	    CAN_NODE_STATUS_t status;
	    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	    uint8_t *array_data;

	    array_data = &CAN_IRP_29bit[CAN_id0x20].CAN_Data[0];


	      //  update data for the MO to transmit
	      status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[17],array_data);

	      if (status == CAN_NODE_STATUS_SUCCESS)
	      {
	        // message object data updated.

	        // transmit the data
	        CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[17]);
	      }
	      else
	      {
	        // message object failed to update.
	      }

}

void CAN_Tx_id0x21(void)
{
	    CAN_NODE_STATUS_t status;
	    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	    uint8_t *array_data;

	    array_data = &CAN_IRP_29bit[CAN_id0x21].CAN_Data[0];


	      //  update data for the MO to transmit
	      status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[18],array_data);

	      if (status == CAN_NODE_STATUS_SUCCESS)
	      {
	        // message object data updated.

	        // transmit the data
	    	  status = CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[18]);
	        if (status == CAN_NODE_STATUS_SUCCESS)
	        {
	        }
	      }
	      else
	      {
	        // message object failed to update.
	      }

}

void CAN_Rx_id0x13(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

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


    process_Rx_CAN_0x13();
}


void CAN_Rx_id0x12(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

    mo_index = 20;//CAN_RX_MO_GTAKE_BASE + CAN_0x211;

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


    process_Rx_CAN_0x12();
}


void CAN_Rx_id0x30(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

    mo_index = 21;//CAN_RX_MO_GTAKE_BASE + CAN_0x211;

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


    process_Rx_CAN_0x30();
}


void process_Rx_CAN_0x13(void)
{
    int8_t mo_index, *tempData;
    uint8_t CAN_rawData[8];
    uint16_t ThrottlePercentage = 6;
    uint16_t VehSpeed;
    int16_t c = 0, c2 = 0;
    int16_t c1 = 0, c3 = 0;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

    mo_index = 19;//CAN_TX_MO_COUNT_GTAKE + CAN_0x211;

    //unnecessary, but keep for the moment
    tempData = &CAN_IRP_29bit[CAN_id0x13].CAN_Data[ZERO_BYTE];
    Irp_Mcu_Torques_29bit->Speed_rpm = 0;
   // Irp_Mcu_Torques_29bit->DC_Current = 0;
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

    RPM = Irp_Mcu_Torques_29bit->Speed_rpm;
    Torque_Estimation = Irp_Mcu_Torques_29bit ->Torque_Estimation;
    //DC_Current_irp = (int)Irp_Mcu_Torques_29bit->DC_Current;
   // c = (int)Irp_Mcu_Torques_29bit->DC_Voltage;
   // c1 = (uint16_t)Irp_Mcu_Torques_29bit->DC_Voltage;
    //DC_Voltage_irp = Irp_Mcu_Torques_29bit->DC_Voltage;
   // DC_Current_irp = ((((uint8_t)tempData[3]) >> 4) | ((int)(tempData[4] & 0x7f) << 4));
    DC_Current_irp = (int)(((int16_t)(tempData[4] & 0x7f) << 4) | (((int16_t)tempData[3] >> 4)) & 0x0f);
    c2 = DC_Current_irp;//(tempData[3] >> 4);
    c3 = ((uint16_t)((uint8_t)tempData[4] & 0x7f) << 4);
    if(c2 < 0)
    {
    	int a;
    	a++;
        //c3 = ((int16_t)((int16_t)tempData[4] & 0x7f) << 4) | 0xffffffff;
    }

    c = c3 | c2;
    DC_Voltage_irp = ((((uint16_t)tempData[6] & 0x0f) << 9) | (((uint16_t)tempData[5] << 1) | 0/*((uint16_t)tempData[4] >> 7) & 0x01*/))/10;

    MotorPower_Irp = DC_Current_irp * DC_Voltage_irp;
    if(c < -1)
    {
    	int a;
    	   a++;

    }
    if(Torque_Estimation > 1)
    {
    	int a;
    	a++;
    }
    if(Torque_Estimation < -5)
    {
    	int a;
    	a++;

    }
    Regenration_flag = 0;
if((DC_Current_irp > 0) && (DC_Current_irp <= 50))
{
	int a;
	a++;
}
else if(DC_Current_irp == 0)
{
//Regenration_flag = 1;
}
else if(DC_Current_irp > 2000)
{
	int a;
	a++;
	Regenration_flag = 1;
}
    VehSpeed = calculate_speed(RPM);

    speed_4g=VehSpeed;

    if(VehSpeed > 100)
        VehSpeed = 100;

    ThrottlePercentage =  map(VehSpeed, 0, 100, 6200, 64000);
    OBDII_CAN[can_0x04].CAN_Data[3] = CAN_MSG_DB[CAN_0CF00400].CAN_Data[THIRD_BYTE] = ThrottlePercentage;
    OBDII_CAN[can_0x04].CAN_Data[2] = CAN_MSG_DB[CAN_0CF00400].CAN_Data[FOURTH_BYTE] = (ThrottlePercentage >> 8);

    VehicleSpeedglb = VehSpeed;

    if(VehSpeed)
    	VehSpeed = 104.11* VehSpeed + 226.99;

    OBDII_CAN[can_0x04].CAN_Data[5] = CAN_MSG_DB[CAN_18FF0921].CAN_Data[FIFTH_BYTE] = (VehSpeed);
    OBDII_CAN[can_0x04].CAN_Data[4] = CAN_MSG_DB[CAN_18FF0921].CAN_Data[SIXTH_BYTE] = (VehSpeed >> 8U);

    //VehicleSpeedglb = VehSpeed;
}

void process_Rx_CAN_0x12(void)
{
    uint8_t mo_index, *tempData;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

    mo_index = 20;//CAN_TX_MO_COUNT_GTAKE + CAN_0x211;

    //unnecessary, but keep for the moment
    tempData = &CAN_IRP_29bit[CAN_id0x12].CAN_Data[ZERO_BYTE];
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

    Mcu_Temp_Irp = Irp_MCU_Status_29bit->MCU_temp;
    Motor_Temp_Irp = Irp_MCU_Status_29bit->Motor_temp;
}

void process_Rx_CAN_0x30(void)
{
    uint8_t mo_index, *tempData;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

    mo_index = 21;//CAN_TX_MO_COUNT_GTAKE + CAN_0x211;

    //unnecessary, but keep for the moment
    tempData = &CAN_IRP_29bit[CAN_id0x30].CAN_Data[ZERO_BYTE];
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);
}


void Irp_Tx_29bit(void)
{
	CAN_Tx_id0x10();
	CAN_Tx_id0x20();
	CAN_Tx_id0x21();
}

void Irp_Rx_29bit(void)
{
	CAN_Rx_id0x13();
	CAN_Rx_id0x12();
	CAN_Rx_id0x30();
}
