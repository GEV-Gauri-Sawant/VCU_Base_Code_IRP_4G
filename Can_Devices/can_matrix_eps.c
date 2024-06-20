#include "DAVE.h"

#include "can_matrix.h"

eps_t eps_n[eps_total_id] =
{
		{0x1e5, 0, 0, 0, 0x00/*eps default status for faulse0x10*/, 0, 0, 0, 0},
		{0x605, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x16c, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x120, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x17d, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x4c5, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x36a, 0, 0, 0, 0, 0, 0, 0, 0},
		{0x53d, 0, 0, 0, 0, 0, 0, 0, 0}

};


void Read_CAN_0x1E5(void)
{
	uint8_t test;
	CAN_NODE_STATUS_t status, receive_status;
	XMC_CAN_MO_t *MO_Ptr;
	uint8_t mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = 15;//CAN_RX_MO_HVAC_BASE + CAN_0x248;

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
	Process_Read_CAN_0x1E5();
}


void update_id0x4c5()
{
	CAN_NODE_STATUS_t status;
	    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;
	   // uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	    uint8_t *array_data;

	    eps_n[can_0x4c5].can_matrix[0] = 0x01;

	    eps_n[can_0x4c5].can_matrix[1] = 0x28;


	    array_data = &eps_n[can_0x4c5].can_matrix[0];

	 //  update data for the MO to transmit
	       status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[10],array_data);

	       if (status == CAN_NODE_STATUS_SUCCESS)
	       {
	         // message object data updated.

	         // transmit the data
	         CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[10]);
	       }
	       else
	       {
	         // message object failed to update.
	       }
}

void update_id0x17d()
{
	CAN_NODE_STATUS_t status;
	    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;
	   // uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	    uint8_t *array_data;

	   // current_rpm = 10000;
	    current_rpm = current_rpm * 1 - 16384U;

	    vspeed = 0;
	    //vspeed = (vspeed * 0.015625) *4;
	    vspeed = vspeed*4;


//	    eps_n[can_0x17d].can_matrix[2] =(0x00 | ((vspeed & 0x00ff) >> 1));
//	    eps_n[can_0x17d].can_matrix[3] =(vspeed >> 8);
	    eps_n[can_0x17d].can_matrix[2] =(0x05);
	    	   // eps_n[can_0x17d].can_matrix[3] =(vspeed >> 8);


	    array_data = &eps_n[can_0x17d].can_matrix[0];

	 //  update data for the MO to transmit
	       status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[13],array_data);

	       if (status == CAN_NODE_STATUS_SUCCESS)
	       {
	         // message object data updated.

	         // transmit the data
	         CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[13]);
	       }
	       else
	       {
	         // message object failed to update.
	       }
}


long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	long ans;

  ans = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

  if(ans > out_max)
	  ans = out_max;

  else if(ans < out_min)
	  ans = out_min;

  return ans;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
	float ans;

  ans = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

  if(ans > out_max)
  	  ans = out_max;

  else if(ans < out_min)
  	  ans = out_min;

  return ans;
}


void update_id0x36a()
{
	CAN_NODE_STATUS_t status;
		    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;
		   // uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
		    uint8_t *array_data;

		   // eps_n[can_0x36a].can_matrix[0] = CAN_MSG_DB_BMS[CAN_0x102].CAN_Data[ZERO_BYTE];





		   // current_rpm = 10000;
		    current_rpm = current_rpm * 1 - 16384U;

		  /*  if(30 <= vspeed)
		    {
		    	vspeed = 32000;
		    }
		    else if((27 <= vspeed) && (vspeed < 30) )
		    {
		    	vspeed = 15000;

		    }
		    else
		    {
		    	vspeed = 000;
		    	//vspeed = vspeed * 0.015625;
		    }

		    vspeed = vspeed * 0.015625;*/

		   // map(x, 0, 100, 0, 0x19);

		    eps_n[can_0x36a].can_matrix[1] = 0x5f;


		   /* eps_n[can_0x36a].can_matrix[2] =(0x00 | ((vspeed & 0x00ff) >> 1));
		    eps_n[can_0x36a].can_matrix[3] =(vspeed >> 8);*/
		    eps_n[can_0x36a].can_matrix[2] = map(vspeed, 0, 80, 0, 0x19);
		    eps_n[can_0x36a].can_matrix[3] = 0x00;//(vspeed >> 8);


		    eps_n[can_0x36a].can_matrix[4] = (0x00 | ((current_rpm & 0x00ff) >> 1));
			eps_n[can_0x36a].can_matrix[5] = (current_rpm >> 8);



			eps_n[can_0x36a].can_matrix[6] = 0x40;
			eps_n[can_0x36a].can_matrix[7] = 0x80;

		    array_data = &eps_n[can_0x36a].can_matrix[0];

		 //  update data for the MO to transmit
		       status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[11],array_data);

		       if (status == CAN_NODE_STATUS_SUCCESS)
		       {
		         // message object data updated.

		         // transmit the data
		         CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[11]);
		       }
		       else
		       {
		         // message object failed to update.
		       }
}

void Process_Read_CAN_0x1E5(void)
{
	uint8_t *tempData, mo_index;
	const CAN_NODE_t *HandlePtr1 = &CAN_NODE_1;

	mo_index = 24;//CAN_RX_MO_BMS_BASE + CAN_0x103;

	tempData = &CAN_BMS_29bit[can_0x1E5].CAN_Data[0];

	//read data to external buffer
	CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);
}

void CAN_OUTPUT_EPS(void)
{
	update_id0x4c5();
	//update_id0x17d();
	update_id0x36a();
}

void CAN_Read_EPS(void)
{
	Read_CAN_0x1E5();
}
