#include "DAVE.h"
#include "can_matrix.h"

CAN_MSG_t CAN_MSG_DB_GTAKE[CAN_MC_GTAKE_MAX] =
{
        {0x121 , {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
        {0x201 , {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}},
        {0x211 , {0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16}},
        {0x221 , {0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24}},
        {0x231 , {0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32}},
};

uint16_t current_rpm;
uint16_t vspeed;

void Tx_CAN_0x121(void)
{
	CAN_NODE_STATUS_t status;
		    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
		   // uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
		    uint8_t *array_data;

		    array_data = &CAN_MSG_DB_GTAKE[CAN_0x121].CAN_Data[0];

		 //  update data for the MO to transmit
		       status = (CAN_NODE_STATUS_t)CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[15],array_data);

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
void Read_CAN_0x201(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_RX_MO_GTAKE_BASE + CAN_0x201;

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

    process_Read_CAN_0x201();
}



void Read_CAN_0x211(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_RX_MO_GTAKE_BASE + CAN_0x211;

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

    process_Read_CAN_0x211();
}



void Read_CAN_0x221(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_RX_MO_GTAKE_BASE + CAN_0x221;

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

    process_Read_CAN_0x221();
}



void Read_CAN_0x231(void)
{
    uint8_t test;
    CAN_NODE_STATUS_t status, receive_status;
    XMC_CAN_MO_t *MO_Ptr;
    uint8_t mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_RX_MO_GTAKE_BASE + CAN_0x231;

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

    process_Read_CAN_0x231();
}

void process_Read_CAN_0x201(void)
{
    uint8_t *tempData, mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_TX_MO_COUNT_GTAKE + CAN_0x201;

    tempData = &CAN_MSG_DB_GTAKE[CAN_0x201].CAN_Data[ZERO_BYTE];

    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

    //perform the conversion and then store
    //process_CAN_0x2A6();
}

void process_Read_CAN_0x221(void)
{
    uint8_t *tempData, mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_TX_MO_COUNT_GTAKE + CAN_0x221;

    tempData = &CAN_MSG_DB_GTAKE[CAN_0x221].CAN_Data[ZERO_BYTE];

    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

    //perform the conversion and then store
    //process_CAN_0x2A6();
}

void process_Read_CAN_0x231(void)
{
    uint8_t *tempData, mo_index;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_TX_MO_COUNT_GTAKE + CAN_0x231;

    tempData = &CAN_MSG_DB_GTAKE[CAN_0x231].CAN_Data[ZERO_BYTE];

    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

    //perform the conversion and then store
    //process_CAN_0x2A6();
}

void process_Read_CAN_0x211(void)
{

    /*  INT_MIN -32767
        INT_MAX +32767
    */

    uint8_t mo_index, *tempData;
    uint8_t CAN_rawData[8];
    int16_t TempRPM;
    uint16_t VehSpeed;
    const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;

    mo_index = CAN_TX_MO_COUNT_GTAKE + CAN_0x211;

    //unnecessary, but keep for the moment
    tempData = &CAN_MSG_DB_GTAKE[CAN_0x211].CAN_Data[ZERO_BYTE];
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

//  tempData = &CAN_MSG_DB_MC[CAN_0x1A6].CAN_Data[ZERO_BYTE];

    tempData = &CAN_rawData[0];
    //read data to external buffer
    CAN_NODE_MO_ReadData(HandlePtr1->lmobj_ptr[mo_index], tempData);

    //perform the conversion and then store
//    TempRPM = CAN_rawData[5]; --> 5 for curtis
//    TempRPM = ((TempRPM << 8) | CAN_rawData[4]);

    TempRPM = CAN_rawData[3];	//--> 3 for gtake
    TempRPM = ((TempRPM << 8) | CAN_rawData[4]);

    ///
    current_rpm = TempRPM;

    ////

    //calculate speed here from motor RPM
    VehSpeed = calculate_speed(TempRPM);

    /////
    vspeed = VehSpeed;
    ///////


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
