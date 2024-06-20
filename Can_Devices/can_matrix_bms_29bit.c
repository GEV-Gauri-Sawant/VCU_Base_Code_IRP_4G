/*
 * can_matrix_bms_29bit.c
 *
 *  Created on: 28-Aug-2023
 *      Author: Suchit Sawant
 */
#include "DAVE.h"
#include "can_matrix.h"

CAN_MSG_t CAN_BMS_29bit[bms_total_id29bit] =
{
		{0x180EA7F3, {0x00}},
		{0X180FA7F3, {0x00}},
		{0X1810A7F3, {0x00}},
		{0X1811A7F3, {0x00}},
		{0X1813A7F3, {0x00}},
		{0X1814A7F3, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0X1815A7F3, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0X180CA7F3, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0X1808A7F3, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0X180AA7F3, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0X180BA7F3, {0x00}}
};


void CAN_Rx_0x1808A7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 12;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X1808A7F3();
}


void CAN_Rx_0x180AA7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 13;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X180AA7F3();
}


void CAN_Rx_0x180BA7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 14;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X180BA7F3();
}


void CAN_Rx_0x180EA7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 20;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X180EA7F3();
}

void CAN_Rx_0x180FA7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 21;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X180FA7F3();
}

void CAN_Rx_0x1810A7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 22;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X1810A7F3();
}

void CAN_Rx_0x1813A7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 23;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X1813A7F3();
}

void CAN_Rx_0x1814A7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 20;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X1814A7F3();
}

void CAN_Rx_0x1815A7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 20;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X1815A7F3();
}


void CAN_Rx_0x180CA7F3(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 24;//CAN_RX_MO_BMS_BASE + CAN_0x103;

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
	process_Rx_CAN_0X180CA7F3();
}


void process_Rx_CAN_0X1810A7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 22;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X1810A7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//charging_started = ((tempData[0]) & 2);

	charge_complete = 0x00;
	if(((tempData[6] >> 4) & 0x01))
		charge_complete = 0x10;
}

void process_Rx_CAN_0X180EA7F3(void)
{
	int8_t *tempData, mo_index;
	static unsigned int charge_count = 0, c4;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 20;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X180EA7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	ChargeCurrentLimit = ((uint16_t)(((uint16_t)tempData[3] << 8) | (uint8_t)tempData[2]))/10;
	DischargeCurrentLimit = ((int)(((int)tempData[5] << 8) | (int)tempData[4]))/10;
	RegenerativeCurrentLimit = ((uint16_t)(((uint16_t)tempData[7] << 8) | (uint8_t)tempData[6]))/10;
//	int d =((uint16_t)((CAN_BMS_29bit[CAN_0X180EA7F3].CAN_Data[1] << 8) | CAN_BMS_29bit[CAN_0X180EA7F3].CAN_Data[0]));
	PackCurrent =  ((int)(((int)tempData[1] << 8) | (int8_t)tempData[0]))/10;

	static int c = 0;// hv_count = 0;
	if((PackCurrent > 1))
	{
		if(charge_count++ > 20)
		{
			charging_started = 1;
			charge_count = 0;
		}

		if(Regenration_flag || RPM)
		{

			//HvBatteryPower = 10 * 58;PackVoltage;
			charge_count = charging_started = 0;
			HvBatteryPower = PackCurrent;
			hv_count = 1;
			if(PackCurrent > c)
				{
				if((hv_count++ < 2))
					c = PackCurrent;
				}
				else if(PackCurrent < HvBatteryPower)
				{
					//HvBatteryPower = c * 58;PackVoltage;
				}
		}
		c4 = 0;

		//charge_count++;
	}
	else if((PackCurrent <= 0))
	{
		charge_count = charging_started = 0;
		HvBatteryPower = c = 0;
	}

if( (hv_count == 1) )
{
	HvBatteryPower = HvBatteryPower * 58;PackVoltage;
	hv_count++;

}
else if(hv_count > 10)
	hv_count = 0;

	//OBDII_CAN[can_0x01].CAN_Data[2] = tempData[1];
	//OBDII_CAN[can_0x01].CAN_Data[3] = tempData[0];
if(PackCurrent < c4)
{
	int a;
	a++;
	c4 = PackCurrent;
}
if(PackCurrent < -10)
{
	int a;
	a++;
}
}

void process_Rx_CAN_0X180FA7F3(void)
{
	int PackCurent = 0;
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 21;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	Bms_SOC = ((uint16_t)tempData[1] << 8) | tempData[0];

	Bms_SOH = (((uint16_t)tempData[3] << 8) | tempData[2]) / 10;

	PackVoltage = (((uint16_t)tempData[7] << 8) | tempData[6])/10;

}

void process_Rx_CAN_0X1813A7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 23;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X1813A7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

}

void process_Rx_CAN_0X1814A7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 23;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X1814A7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

}

void process_Rx_CAN_0X1815A7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 23;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X1815A7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

}


void process_Rx_CAN_0X1808A7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 12;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X1808A7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

}


void process_Rx_CAN_0X180AA7F3(void)
{
	BMS_Avg_temp=0;
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 13;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X180AA7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	BMS_Avg_temp=((int16_t)tempData[1] << 8) | tempData[0] ;
	BMS_Avg_temp += ((int16_t)tempData[3] << 8) | tempData[2];
	BMS_Avg_temp += ((int16_t)tempData[5] << 8) | tempData[4];
	BMS_Avg_temp += ((int16_t)tempData[7] << 8) | tempData[6];

}


void process_Rx_CAN_0X180BA7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 14;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X180BA7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	BMS_Avg_temp +=((int16_t)tempData[1] << 8) | tempData[0] ;
	BMS_Avg_temp += ((int16_t)tempData[3] << 8) | tempData[2];
	BMS_Avg_temp += ((int16_t)tempData[5] << 8) | tempData[4];
	BMS_Avg_temp += ((int16_t)tempData[7] << 8) | tempData[6];

	BMS_Avg_temp=BMS_Avg_temp/8;

}



void process_Rx_CAN_0X180CA7F3(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 24;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[CAN_0X180CA7F3].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	Bms_minTemp = ((int16_t)tempData[1] << 8) | tempData[0];
	Bms_minTemp = Bms_minTemp / 10;
	Bms_maxTemp = ((int16_t)tempData[3] << 8) | tempData[2];
	Bms_maxTemp = Bms_maxTemp / 10;

}

void Read_can_bms_29bit(void)
{
	CAN_Rx_0x1810A7F3();
	CAN_Rx_0x180EA7F3();
	CAN_Rx_0x180FA7F3();
	CAN_Rx_0x1814A7F3();
	CAN_Rx_0x1815A7F3();
	CAN_Rx_0x180CA7F3();
	CAN_Rx_0x1808A7F3();
    CAN_Rx_0x180AA7F3();
    CAN_Rx_0x180BA7F3();
}
