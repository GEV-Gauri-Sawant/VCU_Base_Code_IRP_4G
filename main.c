/*
 * main.c
 *
 *  Created on: 2023 Jun 13 11:11:04
 *  Author: Suchit Sawant
 */


#define XMC_DEBUG_ENABLE 1

#include <stdio.h>
#include <stdarg.h>
#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)

#include "4g_module/sd_card.h"
#include "VCU_OUT/Vcu_Out.h"
#include "InputCapture/InputCapture.h"
#include "VCU_PROCESS/Vcu_Process.h"
#include "Vcu_Init.h"

#include "Vcu_Config.h"

#include "timer_manager/timer_manager.h"
#include "4g_module/mdm_handler.h"
#include "4g_module/4g_data_process.h"

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

void VCU_init_on(void);
void InputCapture(void);
void Process_Inputs(void);
void Vcu_OutPut(void);
void reset_on(void);

uint8_t CState = 4, PreState = 0;

int main(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t super_count = 0;
	//jump :;
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */

	/*  enable here all the relays need to be HIGH at startup  */
	INTERRUPT_Disable(&INTERRUPT_0);
	VCU_init_on();
	reset_on();
	//initialize_sd_card_and_transmit_cid();
	len_retStatus = mod_open4gModPort();
	if (E_RET_SUCCESS == len_retStatus) {
		len_retStatus = tm_setTimerCount(TM_1MS_TIMER_VAL);
		if (E_RET_SUCCESS == len_retStatus) {
			len_retStatus = tm_startTimer();
			if (E_RET_SUCCESS == len_retStatus) {
			}
		}
	}

	mod_enable4gModule();


	while (1U) {
		//SuperLooptime_Start();

	  /* Updating the inputs*/
	  InputCapture();


	  /* processing all inputs */
	  Process_Inputs();

		/* action loop , taking the action */
	  Vcu_OutPut();

		//SuperLooptime_End();

		//SuperLooptime_Start();

		mod_receiveRsp();
		if(false == gb_isMqttConnected)
		{
			mod_4gHandler();
		}
		else if(true == gb_isMqttConnected)
		{
//			mod_4gProcess();
			mod_pub10sPackExtractGps();

		}
//		mod_pub10sPackExtractGps();
		/*RTC_GetTime(&current_time);
		if ((current_time.seconds % 10 == 0U) && (flag4g == false)) {
			epoch_time();
			Process_4G_Event_Data();
			memset(Eventbuffer_4Gcomm, 0, 512);
			pb_ostream_t stream1;
			stream1 = pb_ostream_from_buffer(Eventbuffer_4Gcomm,sizeof(Eventbuffer_4Gcomm));
			pb_encode(&stream1, vcu_fleet_fleet_10_sec_fields, &TD1);
			packetflag = true;
			flag4g = true;
		}
		else if((flag4g == true) && (current_time.seconds % 10 != 0U)){
			flag4g = false;
		}

		if(packetflag == true)
		{
			len_retStatus = mod_mqttPublishData(Eventbuffer_4Gcomm,
					strlen((char*) Eventbuffer_4Gcomm));

			if (E_RET_SUCCESS == len_retStatus) {
				packetflag = false;
			}
			else if (E_RET_INPROGRESS != len_retStatus) {
				lu8_retryCont++;
				if (3 > lu8_retryCont) {
					lu8_retryCont = 0;

					//write to SD card

					packetflag = false;
					gb_isMqttConnected = false;
					sen_4gRunState = E_MQTT_OPEN_STATE;
				}
			}
		}
*/


		/////////////// above for 10 sec ///////////////

		//SuperLooptime_End();

	  /* to reset */
	/* if((DIGITAL_IO_GetInput(&IGNI_POS1_IN_D)))
	 {
		if(super_count == 0)
	  {
			super_count = 1;
		  goto jump;
	  }
	 }
	  else if((!DIGITAL_IO_GetInput(&IGNI_POS1_IN_D)))
	  {
		  super_count = 0;
	  }*/
  }
}

void VCU_init_on(void) {
	/* enable here all the relays need to be HIGH at startup */

		//set_PIN(&COMM_PWR_ENB_D, HIGH);

		/* enable common power to IO */
		DIGITAL_IO_SetOutputHigh(&COMM_3V3_PWR_EN);

		/* 3v3 enable */
		DIGITAL_IO_SetOutputHigh(&INPUTS_3V3_PWR_EN);


		DIGITAL_IO_SetOutputHigh(&SENSOR_3V3_PWR_EN);

	/* comm initialization */
	Io_Exp_Init();

}

void InputCapture(void) {
	uart_debugg(
			"************************in input capture************************\n");
	CState = PreState = 1;
	/* Updating the inputs */
	Input_Capture();
	PreState = 0;
	uart_debugg("************************exit input capture************************\n");
}

void Process_Inputs(void)
{
	uart_debugg("************************in process input************************\n");
	CState = 2;
	/* Updating the outputs */
	Process_VcuOutputs_Update();
	uart_debugg("***********************exit process input**************************\n");
}

void Vcu_OutPut(void)
{
	uart_debugg("***********************in vcu output*****************************\n");
	CState = 3;
	/* Taking the action */
	OutPutAction_Update();
	uart_debugg("************************exit vcu output******************************\n");
}

void reset_on(void)
{
	//WATCHDOG_Stop();
	Delay(100);
	WATCHDOG_Start();
}

void NMI_Handler(void)
{
	//if(!PreState)
	{
		//PreState = CState;
	//uart_debugg("in watchdog");
	WATCHDOG_ClearAlarm();
	//XMC_SCU_cle
	XMC_SCU_INTERRUPT_ClearEventStatus((XMC_SCU_INTERRUPT_EVENT_t)XMC_SCU_INTERRUPT_EVENT_WDT_WARN);
	WATCHDOG_Service();
	//DIGITAL_IO_SetOutputLow(&CABIN_LIGHT_OUT_D);
	//uart_debugg("exit watchdog");
	}
}
