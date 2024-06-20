/*
 * can_matrix_obc.c
 *
 *  Created on: 26-Jun-2023
 *      Author: Suchit Sawant
 */



#include "DAVE.h"

#include "can_matrix.h"

obc_triphase_t obc_triphase_n[obc_total_id]=
{
		{0x0391, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x0388, 0, 0, 0, 0, 0, 0, 0, 0},

};

void update_id0x0391(void)
{
	CAN_NODE_STATUS_t status;
		    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;
		   // uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
		    uint8_t *array_data;

		    obc_triphase_n[can_0x0391].can_matrix[0] = 0x01;

		    obc_triphase_n[can_0x0391].can_matrix[1] = 0x28;


		    obc_triphase_n[can_0x0391].can_matrix[2] = 0x32;

		    obc_triphase_n[can_0x0391].can_matrix[3] = 0x00;


		    obc_triphase_n[can_0x0391].can_matrix[4] = 0x03;


		    array_data = &obc_triphase_n[can_0x0391].can_matrix[0];

		 //  update data for the MO to transmit
		       status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[12],array_data);

		       if (status == CAN_NODE_STATUS_SUCCESS)
		       {
		         // message object data updated.

		         // transmit the data
		         CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[12]);
		       }
		       else
		       {
		         // message object failed to update.
		       }

}

void Process_CAN_0x0388(void)
{
	uint8_t *tempData, mo_index;
		const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

		mo_index = 13;

		tempData = &obc_triphase_n[can_0x0388].can_matrix[0];

		//read data to external buffer
		CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

		if(obc_triphase_n[can_0x0388].can_matrix[7] & 0x01)
		{

		}
	//7.0,7.1
}

void Read_CAN_0x0388(void)
{

	uint8_t test;
		CAN_NODE_STATUS_t status, receive_status;
		XMC_CAN_MO_t *MO_Ptr;
		uint8_t mo_index;
		const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

		mo_index = 13;//CAN_RX_MO_BMS_BASE + CAN_0x116;

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

	Process_CAN_0x0388();
}


