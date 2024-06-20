#include "DAVE.h"
#include "can_matrix.h"

int hazard_hack;
inline void delay(uint32_t delay_ms)
{
	volatile uint32_t i;

	/* The loop runs for delay_ms * 1000 iterations */
	for(i = 0; i < (delay_ms * 1000); i++)
	{
		/* Delay loop */
	}
}

CAN_MSG_t CAN_MSG_DB[CAN_CLUSTER_MAX] =
{
	{0x18FF0921, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x0CF00400, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x18FFC621, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x18FFB632, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x0CF10121, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x18FEEE00, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x18FF2021, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x18FF2121, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0x18FED911, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

void Update_CAN_0x18FF0921(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	tempData = &CAN_MSG_DB[CAN_18FF0921].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_18FF0921], tempData);

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

void Update_CAN_0x0CF00400(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	if(HvBatteryPower > 0)
	{
		//CAN_MSG_DB[CAN_0CF00400].CAN_Data[FOURTH_BYTE] = (uint8_t)(map(HvBatteryPower, 0, 5256, 0x1500, 0x0898) >> 8);//CAN_MSG_DB_GTAKE[CAN_0x211].CAN_Data[ZERO_BYTE];
		//CAN_MSG_DB[CAN_0CF00400].CAN_Data[THIRD_BYTE] = (uint8_t)map(HvBatteryPower, 0, 5256, 0x1500, 0x0898);
		//HvBatteryPower = 0;
	}
	//HvBatteryPower = 0;
	//throttle percentage to power
//	CAN_MSG_DB[CAN_0CF00400].CAN_Data[FOURTH_BYTE] = CAN_MSG_DB_GTAKE[CAN_0x211].CAN_Data[ZERO_BYTE];
	//CAN_MSG_DB[CAN_0CF00400].CAN_Data[THIRD_BYTE] = 0x0;


	//to update battery temperature
//	CAN_MSG_DB[CAN_18FFB632].CAN_Data[THIRD_BYTE] = POwer;
//	CAN_MSG_DB[CAN_18FFB632].CAN_Data[THIRD_BYTE] = POwer >> 8;


	tempData = &CAN_MSG_DB[CAN_0CF00400].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_0CF00400], tempData);

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

void Update_CAN_0x18FFC621(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	tempData = &CAN_MSG_DB[CAN_18FFC621].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_18FFC621], tempData);

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

void Update_CAN_0x18FFB632(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	/*//to update SOC percentage byte
	CAN_MSG_DB[CAN_18FFB632].CAN_Data[ZERO_BYTE] = CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE];*/

	//to update SOC percentage byte         (0 to 100) to (10 to 100)
		//BMS_SOC = CAN_MSG_DB[CAN_18FFB632].CAN_Data[ZERO_BYTE] = map(CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE], 10, 100, 0, 100);

	//to update SOC percentage byte         (0 to 100) to (10 to 100)
	Mapped_BMS_SOC = BMS_SOC = CAN_MSG_DB[CAN_18FFB632].CAN_Data[ZERO_BYTE] = Bms_SOC;
//	Mapped_BMS_SOC = BMS_SOC = CAN_MSG_DB[CAN_18FFB632].CAN_Data[ZERO_BYTE] = map(Bms_SOC, 10, 100, 0, 100);

	//to update battery temperature
	CAN_MSG_DB[CAN_18FFB632].CAN_Data[SECOND_BYTE] = Bms_maxTemp;

	//indicators
	//CAN_MSG_DB[CAN_18FFB632].CAN_Data[THIRD_BYTE] = instrument_clustor_indicators_t.in_clust_in3;

	//to update drive mode information
	//CAN_MSG_DB[CAN_18FFB632].CAN_Data[FOURTH_BYTE] = CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE];


	tempData = &CAN_MSG_DB[CAN_18FFB632].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_18FFB632], tempData);

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

void Update_CAN_0x0CF10121(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	uint16_t Soc_perc, Dte;

	// TO get the SOC percentage
	//Soc_perc = CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE];
	//calculate DTE
	//Dte = Soc_perc * 2U;
 	Dte = Bms_SOC * 2;
	CAN_MSG_DB[CAN_0CF10121].CAN_Data[FOURTH_BYTE] = Dte;
	CAN_MSG_DB[CAN_0CF10121].CAN_Data[FIFTH_BYTE] = (Dte >> 8);

	tempData = &CAN_MSG_DB[CAN_0CF10121].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_0CF10121], tempData);

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

void Update_CAN_0x18FEEE00(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	tempData = &CAN_MSG_DB[CAN_18FEEE00].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_18FEEE00], tempData);

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

void Update_CAN_0x18FF2021(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	tempData = &CAN_MSG_DB[CAN_18FF2021].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[CAN_18FF2021], tempData);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.
		// transmit the data
		// CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[0]);
	}
	else
	{
		// message object failed to update.
	}
}

void Update_CAN_0x18FF2121(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	tempData = &CAN_MSG_DB[CAN_18FF2121].CAN_Data[ZERO_BYTE];

	 //  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[29],tempData);

		       if (status == CAN_NODE_STATUS_SUCCESS)
		       {
		         // message object data updated.

		         // transmit the data
		         CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[29]);
		       }
		       else
		       {
		         // message object failed to update.
		       }
}

void Update_CAN_0x18FED911(void)
{
	uint8_t *tempData;
	CAN_NODE_STATUS_t status;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

	tempData = &CAN_MSG_DB[CAN_18FED911].CAN_Data[ZERO_BYTE];

	//  update data for the MO to transmit
	status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[15],tempData);

	if (status == CAN_NODE_STATUS_SUCCESS)
	{
		// message object data updated.

		// transmit the data
		CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[15]);
	}
	else
	{
		// message object failed to update.
	}
}


void CAN_OUTPUT_CLUSTER()
{
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
	XMC_CAN_MO_t *MO_Ptr;

	CAN_NODE_STATUS_t mo_tranmit_status;
	CAN_NODE_STATUS_t status;
	uint16_t msg_count;

	/* update all message's data */
	Update_CAN_0x18FF0921();
	Update_CAN_0x0CF00400();
	Update_CAN_0x18FFC621();
	Update_CAN_0x18FFB632();
	Update_CAN_0x0CF10121();
	Update_CAN_0x18FEEE00();
	Update_CAN_0x18FF2021();

/* will update separately */
	Update_CAN_0x18FF2121();
	Update_CAN_0x18FED911();
/*                             */

	/* Shoot CAN messages on CAN bus */
	for(msg_count = 0; msg_count < CAN_TX_MO_COUNT_CLUSTER; msg_count++)
	{
		MO_Ptr = HandlePtr1->lmobj_ptr[msg_count]->mo_ptr;

		mo_tranmit_status = CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[msg_count]);
		if (mo_tranmit_status == CAN_NODE_STATUS_SUCCESS)
		{
			//message object transmission success.
			// read the TXOK status bit
			status = CAN_NODE_MO_GetStatus(HandlePtr1->lmobj_ptr[msg_count]);	//msg_count, earlier it was 0 and working

			if (status &  XMC_CAN_MO_STATUS_TX_PENDING)
			{
				//Clear the transmit OK flag
				XMC_CAN_MO_ResetStatus(MO_Ptr,XMC_CAN_MO_RESET_STATUS_TX_PENDING);
			}

//			delay(10); //10ms delay

		}
		else
		{
			// message object failed to transmit.
		}
	}
}
