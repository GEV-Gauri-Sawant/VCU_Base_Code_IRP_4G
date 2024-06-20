#include "DAVE.h"
#include "can_matrix.h"


speed_cluster_t speed_db[] =
{
		/*5th*/    /*6th*/
		{0x00,		0x00},
		{0x2C,		0x01},
		{0x2C,		0x01},
		{0x90,		0x01},
		{0x90,		0x01},
		{0x58,		0x02},
		{0x20,		0x03},
		{0x20,		0x03},
		{0x84,		0x03},
		{0x84,		0x03},
		{0xE8,		0x03},
		{0x14,		0x05},
		{0xDC,		0x05},
		{0xDC,		0x05},
		{0xDC,		0x05},
		{0xA4,		0x06},
		{0x6C,		0x07},
		{0x34, 		0x08},
		{0x34, 		0x08},
		{0x34, 		0x08},
		{0xFC,		0x08},
		{0xC4,		0x09},
		{0x8C,		0x0A},
		{0x8C,		0x0A},
		{0x8C,		0x0A},
		{0xF0,		0x0A},
		{0xB8,		0x0B},
		{0x1C,		0x0C},
		{0x1C,		0x0C},
		{0x1C,		0x0C},
		{0x12,		0x0D},
		{0xAC,		0x0D},
		{0x74,		0x0E},
		{0x74,		0x0E},
		{0x74,		0x0E},
		{0x3C,		0x0F},
		{0x04,		0x10},
		{0x04,		0x10},
		{0x68,		0x10},
		{0x68,		0x10},
		{0x30,		0x11},
		{0xF8,		0x11},
		{0xF8,		0x11},
		{0x5C,		0x12},
		{0x5C,		0x12},
		{0x24,		0x13},
		{0xEC,		0x13},
		{0x50,		0x14},
		{0x50,		0x14},
		{0x50,		0x14},
		{0x18,		0x15},
		{0xE0,		0x15},
		{0xA8,		0x16},
		{0xA8,		0x16},
		{0xA8,		0x16},
		{0x70,		0x17},
		{0x38,		0x18},
		{0x38,		0x18},
		{0x9C,		0x18},
		{0x9C,		0x18},
		{0x64,		0x19},
		{0x2C,		0x1A},
		{0x2C,		0x1A},
		{0xF4,		0x1A},
		{0xF4,		0x1A},
		{0xBC,		0x1B},
		{0x84,		0x1C},
		{0xE8,		0x1C},
		{0xE8,		0x1C},
		{0xE8,		0x1C},
		{0x14,		0x1E},
		{0Xdc,		0x1E},
		{0Xdc,		0x1E},
		{0X72,		0X1F},
		{0X72,		0X1F},
		{0X08,		0X20},
		{0xd0,		0x20},
		{0xd0,		0x20},
		{0x98,		0x21},
		{0x98,		0x21},
		{0xfc,		0x21},
		{0xc4,		0x22},
		{0xc4,		0x22},
		{0x8c,		0x23},
		{0x8c,		0x23},
		{0xf0,		0x23},
		{0x7A,		0x24},
		{0x7A,		0x24},
		{0xb8,		0x24},
		{0xb8,		0x24},
		{0x1C,		0x25},
		{0xb2,		0x25},
		{0xb2,		0x25},
		{0x16,		0x26},
		{0x16,		0x26},
		{0x48,		0x26},
		{0xac,		0x26},
		{0xac,		0x26},
		{0x10,		0x27},
		{0x10,		0x27},
		{0x10,		0x27},
};



CAN_MSG_t CAN_MSG_DB_MC[CAN_MC_MAX] =
{
//		{0x00 ,	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
//		{0x626, 0x00, 0x49, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00},
//		{0x226, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
//		{0x326, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
//		{0x80 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x1A6, {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48}},
		{0x2A6, {0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56}},
		{0xA6 , {0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56}},
};

void CAN_MotorController_init(void)
{
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	XMC_CAN_MO_t *MO_Ptr;

	CAN_NODE_STATUS_t mo_tranmit_status;
	CAN_NODE_STATUS_t status;
	uint16_t msg_count;


	/* Shoot CAN messages on CAN bus */
	for(msg_count = CAN_TX_MO_MC_INIT_BASE; msg_count < CAN_TX_MO_MC_INIT_TOP; msg_count++)
	{
		MO_Ptr = HandlePtr1->lmobj_ptr[msg_count]->mo_ptr;

		mo_tranmit_status = CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[msg_count]);
		if (mo_tranmit_status == CAN_NODE_STATUS_SUCCESS)
		{
			//message object transmission success.
			// read the TXOK status bit
			status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[msg_count]);

			if (status &  XMC_CAN_MO_STATUS_TX_PENDING)
			{
				//Clear the transmit OK flag
				XMC_CAN_MO_ResetStatus(MO_Ptr,XMC_CAN_MO_RESET_STATUS_TX_PENDING);
			}

//			delay(100); //100ms delay

		}
		else
		{
			// message object failed to transmit.
		}
	}
};

void Read_CAN_0x1A6(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_RX_MO_MC_BASE + CAN_0x1A6;

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
}

void Read_CAN_0x2A6(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_RX_MO_MC_BASE + CAN_0x2A6;

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
}

void Read_CAN_0xA6(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_RX_MO_MC_BASE + CAN_0xA6;

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
}

void CAN_NODE_MO_ReadData(const CAN_NODE_LMO_t *const lmo_ptr, uint8_t *array_data)
{
  uint8_t i;

  XMC_ASSERT("CAN_NODE_MO_UpdateData: lmo_ptr null", lmo_ptr != NULL);

  for (i=0; i<8; i++)
  {
	  array_data[i] = lmo_ptr->mo_ptr->can_data_byte[i];
  }
}

void process_Read_CAN_0x1A6(void)
{

	/* 	INT_MIN -32767
		INT_MAX +32767
	*/

	uint8_t mo_index, *tempData;
	uint8_t CAN_rawData[8];
	int16_t TempRPM;
	uint16_t VehSpeed;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_RX_MO_MC_BASE + CAN_0x1A6;
//	tempData = &CAN_MSG_DB_MC[CAN_0x1A6].CAN_Data[ZERO_BYTE];

	tempData = &CAN_rawData[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
	TempRPM = CAN_rawData[5];
	TempRPM = ((TempRPM << 8) | CAN_rawData[4]);

	//calculate speed here from motor RPM
	VehSpeed = calculate_speed(TempRPM);

	if(VehSpeed > 100)
		VehSpeed = 100;

	/*
	CAN_MSG_DB[CAN_18FF0921].CAN_Data[FIFTH_BYTE] = (uint8_t)(speed_db[VehSpeed].speed_5th_byte);
	CAN_MSG_DB[CAN_18FF0921].CAN_Data[SIXTH_BYTE] = (uint8_t)(speed_db[VehSpeed].speed_6th_byte);
	*/

	VehSpeed = 104.11* VehSpeed + 226.99;
	CAN_MSG_DB[CAN_18FF0921].CAN_Data[FIFTH_BYTE] = (VehSpeed);
	CAN_MSG_DB[CAN_18FF0921].CAN_Data[SIXTH_BYTE] = (VehSpeed >> 8U);

}

void process_Read_CAN_0x2A6(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_TX_MO_COUNT_CLUSTER + CAN_0x2A6;

	tempData = &CAN_MSG_DB_MC[CAN_0x2A6].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x2A6();
}

void process_Read_CAN_0xA6(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_TX_MO_COUNT_CLUSTER + CAN_0xA6;

	tempData = &CAN_MSG_DB_MC[CAN_0xA6].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
	process_CAN_0xA6();
}

uint8_t calculate_speed(int16_t motor_rpm)
{
	const float PI = 3.14;
	float kmph;
	uint8_t TempSpeed;
	float wheel_rpm;
	float MPS;

	float final_drive_ratio = 9.887;    //drive train ration 9.916 , 9.89109;
	float SLR = 0.267; //static load radius

//	float wheel_dia_meters = 0.55;// for tyre under load
//	float wheel_circumference_meters = wheel_dia_meters * PI; // 0.001727-> wheel diameter = 0.55 meters
//	float wheel_circumference_km = wheel_circumference_meters / 1000.0;

	motor_rpm = abs(motor_rpm);

		/*wheel_rpm = motor_rpm / final_drive_ratio;
		MPS = (2 * (PI) * wheel_rpm * SLR)/60;
		kmph = MPS * 3.6;

		TempSpeed = (uint8_t) kmph;*/

	motor_rpm = motor_rpm + (motor_rpm * (0.05));
	motor_rpm *= 0.010988;/* constant given by mukul*/
	TempSpeed = motor_rpm;

		return TempSpeed;
}
