#include "DAVE.h"
#include "can_matrix.h"

CAN_MSG_t CAN_MSG_DB_BMS[CAN_BMS_MAX] =
{
		{0x102,	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0x103, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0x104, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0x105, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0x113, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0x114, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{0x116, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
};

void process_Read_CAN_0x102(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x102;

	tempData = &CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x102();
}

void process_Read_CAN_0x103(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_MSG_DB_BMS[CAN_0x103].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x104(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x104;

	tempData = &CAN_MSG_DB_BMS[CAN_0x104].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x105(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x105;

	tempData = &CAN_MSG_DB_BMS[CAN_0x105].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x113(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x113;

	tempData = &CAN_MSG_DB_BMS[CAN_0x113].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x114(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x114;

	tempData = &CAN_MSG_DB_BMS[CAN_0x114].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x116(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x116;

	tempData = &CAN_MSG_DB_BMS[CAN_0x116].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void Read_CAN_0x102(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x102;

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

	process_Read_CAN_0x102();
}

void Read_CAN_0x103(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x103;

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

	process_Read_CAN_0x103();
}

void Read_CAN_0x104(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x104;

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

	process_Read_CAN_0x104();
}

void Read_CAN_0x105(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x105;

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

	process_Read_CAN_0x105();
}

void Read_CAN_0x113(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x113;

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
	process_Read_CAN_0x113();
}

void Read_CAN_0x114(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x114;

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

	process_Read_CAN_0x114();
}

void Read_CAN_0x116(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_BMS_BASE + CAN_0x116;

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

	process_Read_CAN_0x116();
}

/*****************************************************************************************************************************************/


/*************************************************************** 250kbps ***********************************************************/


void process_Read_CAN_0x102_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id102_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x102();
}

void process_Read_CAN_0x103_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id103_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x103].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x104_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id104_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x104].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x105_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id105_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x105].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x113_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id113_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x113].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x114_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id114_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x114].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}

void process_Read_CAN_0x116_250kbps(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id116_250kbps;

	tempData = &CAN_MSG_DB_BMS[CAN_0x116].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//perform the conversion and then store
//	process_CAN_0x103();
}



void Read_CAN_0x102_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id102_250kbps;

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

	process_Read_CAN_0x102_250kbps();
}

void Read_CAN_0x103_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id103_250kbps;

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

	process_Read_CAN_0x103_250kbps();
}

void Read_CAN_0x104_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id104_250kbps;

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

	process_Read_CAN_0x104_250kbps();
}

void Read_CAN_0x105_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id105_250kbps;

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

	process_Read_CAN_0x105_250kbps();
}

void Read_CAN_0x113_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id113_250kbps;

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
	process_Read_CAN_0x113_250kbps();
}

void Read_CAN_0x114_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id114_250kbps;

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

	process_Read_CAN_0x114_250kbps();
}

void Read_CAN_0x116_250kbps(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = CAN_id116_250kbps;

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

	process_Read_CAN_0x116_250kbps();
}




void Read_CAN_BMS(void)
{
	///// 500kbps ////
   /*Read_CAN_0x102();
	 Read_CAN_0x103();
	 Read_CAN_0x104();
	 Read_CAN_0x105();
	 Read_CAN_0x113();
	 Read_CAN_0x114();
	 Read_CAN_0x116();*/

	//// 250kbps ////
	 Read_CAN_0x102_250kbps();
	 Read_CAN_0x103_250kbps();
	 Read_CAN_0x104_250kbps();
	 Read_CAN_0x105_250kbps();
	 Read_CAN_0x113_250kbps();
	 Read_CAN_0x114_250kbps();
	 Read_CAN_0x116_250kbps();

}
