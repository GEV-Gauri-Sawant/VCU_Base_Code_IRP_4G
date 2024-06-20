#include "DAVE.h"
#include "can_matrix.h"
#include "Vcu_Config.h"
//#include <main.h>

volatile uint8_t error_compressor;

CAN_MSG_t CAN_MSG_DB_HVAC[CAN_HVAC_MAX] =
{
		{0x238, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, //Tx
		{0x100, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, //Rx
		{0x248, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, //Rx
		{0x8000250, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, //Rx
		{0x8000530, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0} //Tx
};


void Process_Read_CAN_0x100(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_HVAC_BASE + CAN_0x100;

	tempData = &CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);
}

void Process_Read_CAN_0x248(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_HVAC_BASE + CAN_0x248;

	tempData = &CAN_MSG_DB_HVAC[CAN_0x248].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);
}
void Read_CAN_0x100(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_HVAC_BASE + CAN_0x100;

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

	//copy data from MO object to HVAC DB CAN_MSG_DB_HVAC
	Process_Read_CAN_0x100();
}

void Read_CAN_0x248(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = CAN_RX_MO_HVAC_BASE + CAN_0x248;

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

	//copy data from MO object to HVAC DB CAN_MSG_DB_HVAC
	Process_Read_CAN_0x248();
}

//hifire
void Read_CAN_Hifire_0x8000250(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 8;

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

	//copy data from MO object to HVAC DB CAN_MSG_DB_HVAC
	Process_CAN_Hifire_0x8000250();
}

//hifire
void Process_CAN_Hifire_0x8000250(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	mo_index = 8;

	tempData = &CAN_MSG_DB_HVAC[CAN_0x8000250].CAN_Data[ZERO_BYTE];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	//get the error code
	 uint8_t error_code = (0x0F & (CAN_MSG_DB_HVAC[CAN_0x8000250].CAN_Data[4]));

	if(0x00 != error_code)
	{
		error_compressor = 0x1;
	}
	else
	{
		error_compressor = 0x0;
	}
}

void Process_CAN_0x100(void)
{
	uint16_t rpm=0;
	float pressure_in, voltage_psi;
	float pressure_value;
	uint8_t TempDegreeC;
	uint8_t AC_ON=1;
	static uint8_t condenser_on = 0x00;

	//get the temperature
	TempDegreeC = CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[0];
	//get the pressure
	pressure_in = (float) CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[1];
	//get the AC switch input
	AC_ON_4g = AC_ON = CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[2];

	//AC is ON when AC_ON == 0
	//now ac is on when == 1
	//AC_ON = 1;
	if(0x01 == AC_ON)
	{
		//convert the temperature to rpm
		if(TempDegreeC <= 28)
		{
			rpm = (uint16_t)(((-200) * (int32_t)TempDegreeC) + 9100);        //from line eqn relating temperature to rpm

			if(Vcu_InPuts.IGNITION_1_IN)
			{//ptc turn off//
				//DIGITAL_IO_SetOutputLow(&MC_CONTACTOR_RELAY_OUT_D);
			}
		}
		else if (TempDegreeC > 28)
		{
			rpm = 2500;
			if(Vcu_InPuts.IGNITION_1_IN)
			{
			//ptc turn on//
			//DIGITAL_IO_SetOutputHigh(&MC_CONTACTOR_RELAY_OUT_D);
			}
		}

		//calculate pressure value in megaPascal
		voltage_psi = pressure_in * (5.0/1023.0);
		pressure_value = (voltage_psi - (0.02*5)) / (5*0.29665);

		if(pressure_value >= HIGH_PRESSURE_mP)
		{
			//AC_ON = 0x01; S
			AC_ON = 0x00; //make hole system off

		}
	}

//	//update CAN_MSG_DB_HVAC for 0x238
//	CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[0] = rpm;
//	//CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[1] = (rpm >> 1);
//	CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[1] = (rpm >> 8);

	//update CAN_MSG_DB_HVAC for 0x8000530 //hifire
	CAN_MSG_DB_HVAC[CAN_0x8000530].CAN_Data[3] = rpm;        //hifire
	CAN_MSG_DB_HVAC[CAN_0x8000530].CAN_Data[4] = (rpm >> 8); //hifire

	//error_compressor from 0x8000250
	if((0x01 == AC_ON) && (0x01 != error_compressor))
	{
		if(0x0 == condenser_on)
		{
			//turn on the condenser using digital IO
//			DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
			//DIGITAL_IO_SetOutputHigh(&AC_BLOWER_SPEED_1); // for
		//	if(DIGITAL_IO_GetInput(&IGNI_POS1_IN_D))
			//	DIGITAL_IO_SetOutputHigh(&AC_BLOWER_SPEED_2); // for compressor to on X
		//	if(DIGITAL_IO_GetInput(&IGNI_POS1_IN_D))
					   DIGITAL_IO_SetOutputHigh(&AC_RADIATOR_OUT_D); // for compressor to on

			condenser_on = 0x1;
		}

		//turn AC ON
//		CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[3] = 0x01;	//setting 24th bit of CAN_0x238
		CAN_MSG_DB_HVAC[CAN_0x8000530].CAN_Data[0] = 0x01;	//setting 7th bit of CAN_0x8000530 //hifire
	}
	else
	{
		//turn off the condenser
//		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		//if(0x01 == condenser_on)
	//	{
			//DIGITAL_IO_SetOutputLow(&AC_BLOWER_SPEED_1); // for
			//for(volatile int i = 0; i < 0xffff*4; i++);
		//if(DIGITAL_IO_GetInput(&IGNI_POS2_IN_D))
			//DIGITAL_IO_SetOutputLow(&AC_BLOWER_SPEED_2);
		//if(DIGITAL_IO_GetInput(&IGNI_POS1_IN_D))
			  DIGITAL_IO_SetOutputLow(&AC_RADIATOR_OUT_D);/// for compressor to turn off
		condenser_on = 0x0;
		//}
//		CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[3] = 0x00;
		CAN_MSG_DB_HVAC[CAN_0x8000530].CAN_Data[0] = 0x00; //hifire
	}
}

void Process_CAN_0x248(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t error_code;

	//get the error code
	error_code = (0x0F & (CAN_MSG_DB_HVAC[CAN_0x248].CAN_Data[4]));

	if(0x00 != error_code)
	{
		error_compressor = 0x1;
	}
	else
	{
		error_compressor = 0x0;
	}
}

void Update_CAN_0x238(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	tempData = &CAN_MSG_DB_HVAC[CAN_0x238].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_0x238], tempData);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.
		// transmit the data
		//CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[0]);
	}
	else
	{
		// message object failed to update.
	}
}

void CAN_INPUT_HVAC(void)
{
	//read compressor to check error
	Read_CAN_Hifire_0x8000250();
	Read_CAN_0x100();
	Process_CAN_0x100();
}

//for hifire
void CAN_OUTPUT_COMPRESSOR(void)
{
	CAN_NODE_STATUS_t mo_tranmit_status, status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	uint8_t mo_index = 9;
	XMC_CAN_MO_t *MO_Ptr = HandlePtr1->lmobj_ptr[mo_index]->mo_ptr;

	/* update message's data */
	uint8_t *tempData = &CAN_MSG_DB_HVAC[CAN_0x8000530].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[mo_index], tempData);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.
		// transmit the data
		mo_tranmit_status = CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[mo_index]);
		if (mo_tranmit_status == CAN_NODE_STATUS_SUCCESS)
		{
			//message object transmission success.
			// read the TXOK status bit
			status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[mo_index]);	//msg_count, earlier it was 0 and working

			if (status &  XMC_CAN_MO_STATUS_TX_PENDING)
			{
				//Clear the transmit OK flag
				XMC_CAN_MO_ResetStatus(MO_Ptr,XMC_CAN_MO_RESET_STATUS_TX_PENDING);
			}
		}
		else
		{
			// message object failed to transmit.
		}
	}
	else
	{
		// message object failed to update.
	}
}
