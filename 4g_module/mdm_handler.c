/*
 * mdm_handler.c
 *
 *  Created on: 14-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#include <4g_module/at_handler.h>
#include <4g_module/mdm_handler.h>
#include <4g_module/ssl_cert_keys.h>
#include <DIGITAL_IO/digital_io.h>
#include <DIGITAL_IO/digital_io_extern.h>
#include <stdlib.h>
#include "DAVE.h"
#include "at_handler.h"
#include "mdm_handler.h"
#include "timer_manager/timer_manager.h"
#include "pb_encode.h"
#include "pb_common.h"
#include "Vcu_Config.h"
#include "V26_10sec_fleet.pb.h"
#include "sd_card.h"
#include "GPS.h"

#define NEW_LINE					"\r\n"
#define OK_RSP						"OK\r\n"
#define NULL_STR					"\0"
#define ERROR_STR					"ERROR"
#define CME_ERROR					"+CME ERROR"
#define CMS_ERROR					"+CMS ERROR"
#define QMTOPEN						"+QMTOPEN:"
#define QMTCONN						"+QMTCONN:"
#define QMTPUBEX					"+QMTPUBEX:"
#define QMTDISC						"+QMTDISC:"
#define	QMTSUB						"+QMTSUB:"
#define QMTSTAT						"+QMTSTAT:"
#define QMTRECV						"+QMTRECV:"
#define QFUPL						"+QFUPL:"
#define PWR_DWN						"POWERED DOWN\r\n"
#define READY						"RDY\r\n"
#define QMSIMSTATE					"+QSIMSTAT:"
#define PRODCUT_NAME				"Quectel\r\n"
#define SSL_MODE					"\"SSL\",0,1,2\r\n"
#define CA_CERT_PATH				"\"cacert\",2,\"cacert.pem\"\r\n"
#define CC_CERT_PATH				"\"clientcert\",2,\"clientcert.pem\"\r\n"
#define CK_CERT_PATH				"\"clientkey\",2,\"clientkey.pem\"\r\n"
#define SSL_AUTH					"\"seclevel\",2,2\r\n"
#define SSL_VERSION					"\"sslversion\",2,4\r\n"
#define SSL_CIPHER_SUITE			"\"ciphersuite\",2,0xFFFF\r\n"
#define SSL_IGNORE_LOCAL_TIME		"\"ignorelocaltime\",2,1\r\n"
#define MQTT_OPEN_HOST_PORT			"\"ay7oqexbk25sl-ats.iot.ap-south-1.amazonaws.com\",8883\r\n"
#define MQTT_CONNECT_CLINT_ID		"smartKit"
#define MQTT_PUBLISH_PARA			"0,1,1,0,\"Test\",9\r\n"
#define MQTT_PUBLISH_TOPIC			"\"/Gev3/fleet\""
#define MQTT_CONNECTED_MSG			"Connected"
#define MQTT_SUB_TOPIC				"\"SubTest\""
#define MQTT_SSL_CA_FILENAME		"\"cacert.pem\""
#define MQTT_SSL_CC_FILENAME		"\"clientcert.pem\""
#define MQTT_SSL_CK_FILENAME		"\"clientkey.pem\""
#define MQTT_PUBLISH_QOS			0
#define MQTT_SUB_QOS				0

#define TIMEOUT_300MS				300
#define TIMEOUT_1S					1000
#define TIMEOUT_3S					3000
#define TIMEOUT_5S					5000
#define TIMEOUT_8S					8000
#define TIMEOUT_10S					10000
#define TIMEOUT_15s					15000
#define TIMEOUT_30s					30000
#define TIMEOUT_180S				180000
#define TIMEOUT_120S				120000

#define AT_RESP_MAX_BUFFER_SIZE		64
#define SEND_AT_CMD_BUFF			1032
#define CMD_BUFF					1536
#define AT_CMD_RETYR_MAX_CNT		3
#define PWR_DOWN_SIZE				16
#define RDY_SIZE					7
#define QSIMSTATE_SIZE				22
#define PRO_REVISION_SIZE			19
#define IMEI_SIZE					15
#define CCID_SIZE					20
#define PHONE_SIZE					13
#define TIME_SIZE					20
#define OPERATOR_SIZE				20

extern vcu_fleet_fleet_10_sec TD1;
extern uint8_t Eventbuffer_4Gcomm[512];
static uint8_t gu8_signalQuality = 0;
static uint8_t gu8arr_respBuffer[AT_RESP_MAX_BUFFER_SIZE];
static uint8_t gu8arr_productRevision[PRO_REVISION_SIZE];
static uint8_t gu8arr_IMEINum[IMEI_SIZE];
static uint8_t gu8arr_CCIDNum[CCID_SIZE];
static uint8_t gu8arr_phoneNum[PHONE_SIZE];
static uint8_t gu8_operatorName[OPERATOR_SIZE];
static uint8_t gu8_dataTime[TIME_SIZE];
uint8_t gu8arr_sendMsgBuff[20];
static uint8_t sgu8_respCount = 0;
static uint8_t sgu8_mqttClientId = 0;
static uint16_t sgu16_cmeError = 0;
static uint16_t sgu16_cmsError = 0;
static en_4gModuleRunState_t sen_4gRunState = E_SET_URC_PORT_STATE;
static en_sendCmdGetRspState_t sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
static en_simStatusState_t sen_simStatusState = E_SIM_ENABLE_SIM_DETECTION_STATE;
static en_openMqttState_t sen_openMqttState = E_MQTT_SSL_UPLD_CA_CERT_STATE;
static en_publishDataState_t sen_publishDataState = E_PUBLISH_CMD_STATE;
static en_modemResetState_t sen_modemResetState = E_RST_DISABLE_FUNCTION;
static en_10sPacektPubState_t sen_10sPacektPubState = E_PREPARE_PACKET_STATE;
static en_sslFileUploadState_t sen_sslFileUpldState = E_SSL_UPLD_CMD_STATE;
static en_gpsProcessState_t sen_gpsProcessState = E_EXTRACT_GPS_DATA_STATE;
static en_4gProcessState_t sen_4gProcessState = E_GPS_PROCESS_STATE;

static bool sgb_packetFlag = false;
static bool sgb_flag4g = false;
static bool sgb_flagGps = false;

/* for error set and status */
st_deviceStatus_t gst_deviceStatus = {
		.mb_isSimInserted = false,
		.mb_ismodemPwrDwn = true,
		.men_networkRegStatus = E_REG_NONE,
		.men_mqttOpenErrorCodes = E_MQTT_OPN_NONE,
		.men_mqttCloseErrorCodes = E_MQTT_CLOSE_NONE,
		.men_mqttConnectErrorCodes = E_MQTT_CON_NONE,
		.men_mqttDisconErrorCodes = E_MQTT_DISCON_NONE,
		.men_mqttPublishErrorCode = E_PUB_NONE,
		.men_mqttSubErrorCode = E_SUB_NONE
};

/* command table */
st_ATCmdTable_t gcst_ATCmdTable[E_IDX_MAX] = {
		  //Send command		Response string		OtherResponseString		Error String	Response timeout
//Power ON/OFF
		{ 	"DUMMY_DATA", 				READY, 				NULL_STR, 				NULL_STR, 		TIMEOUT_300MS 	},	//	E_IDX_POWER_ON
		{ 	"AT+QPOWD=1", 				OK_RSP, 			PWR_DWN, 				NULL_STR, 		TIMEOUT_300MS 	},	//	E_IDX_POWER_OFF

//Port config
		{	"AT+QURCCFG=\"urcport\",", 	OK_RSP,				NULL_STR,				ERROR_STR,		TIMEOUT_300MS	},	//	E_IDX_SET_URC_PRT

//Echo Off
		{ 	"ATE0", 					OK_RSP, 			NULL_STR, 				NULL_STR, 		TIMEOUT_300MS 	},	//	E_IDX_ECHO_OFF

//set flow control
		{ 	"AT+IFC=", 					OK_RSP, 			"+IFC:", 				NULL_STR, 		TIMEOUT_300MS 	},	//	E_IDX_HW_FLWCTRL

//Product info
		{ 	"ATI", 						OK_RSP, 			PRODCUT_NAME, 			NULL_STR, 		TIMEOUT_300MS 	},	//	E_EXTRACT_MODULE_INFO_STATE

//SIM status
		{ 	"AT+QSIMDET=", 				OK_RSP, 			"+QSIMDET:", 			ERROR_STR, 		TIMEOUT_300MS 	},	//	E_IDX_ENABLE_SIM_DETECTION
		{ 	"AT+QSIMSTAT=", 			OK_RSP, 			NULL_STR, 				ERROR_STR, 		TIMEOUT_300MS 	},	//	E_IDX_ENABLE_SIM_STATUS
		{ 	"AT+QSIMSTAT?", 			OK_RSP, 			"+QSIMSTAT:", 			ERROR_STR, 		TIMEOUT_300MS 	},	//	E_IDX_CHECK_SIM_STATUS
		{ 	"AT+CPIN?", 				OK_RSP, 			"+CPIN:", 				NULL_STR, 		TIMEOUT_5S 		},	//	E_IDX_CPIN_CHECK
		{ 	"AT+GSN", 					OK_RSP, 			NULL_STR, 				NULL_STR, 		TIMEOUT_300MS 	},	//	E_IDX_GET_IMEI
		{ 	"AT+QCCID", 				OK_RSP, 			"+QCCID:", 				ERROR_STR,	 	TIMEOUT_300MS 	},	//	E_IDX_GET_CCID
		{ 	"AT+CNUM", 					OK_RSP, 			"+CNUM:", 				ERROR_STR, 		TIMEOUT_300MS 	},	//	E_IDX_GET_NUM
		{ 	"AT+COPS?", 				OK_RSP, 			"+COPS:", 				CME_ERROR, 		TIMEOUT_180S 	},	//	E_IDX_GET_OPERATOR
		{ 	"AT+CREG?", 				OK_RSP, 			"+CREG:", 				CME_ERROR, 		TIMEOUT_300MS 	},	//	E_IDX_CREG
		{ 	"AT+CSQ", 					OK_RSP, 			"+CSQ:", 				CME_ERROR, 		TIMEOUT_300MS 	},	//	E_IDX_SIGNAL_QLTY
		{ 	"AT+CCLK?", 				OK_RSP, 			"+CCLK:", 				CME_ERROR, 		TIMEOUT_300MS 	},	//	E_IDX_CCLK

//MQTT
		{ 	"AT+QMTCFG=", 				OK_RSP, 			"+QMTCFG:", 			ERROR_STR, 		TIMEOUT_1S 		},	//	E_IDX_MQTT_CFG
		{ 	"AT+QSSLCFG=", 				OK_RSP, 			"+QSSLCFG:", 			ERROR_STR, 		TIMEOUT_300MS 	},	//	E_IDX_MQTT_SSL_CFG
		{ 	"AT+QMTOPEN=", 				"XXXX", 			"+QMTOPEN:", 			ERROR_STR, 		TIMEOUT_120S 	},	//	E_IDX_MQTT_OPEN
		{ 	"AT+QMTCONN=", 				"XXXX", 			"+QMTCONN:", 			ERROR_STR, 		TIMEOUT_5S 		},	//	E_IDX_MQTT_CONNECT
		{ 	"AT+QMTPUBEX=", 			">", 				"+QMTPUBEX:", 			ERROR_STR, 		TIMEOUT_15s 	},	//	E_IDX_MQTT_PUBLISH
		{ 	"", 						"XXXX", 			"+QMTPUBEX:", 			ERROR_STR, 		TIMEOUT_15s 	},	//	E_IDX_MQTT_PUBLISH_DATA
		{ 	"AT+CFUN=", 				OK_RSP, 			NULL_STR, 				CME_ERROR, 		TIMEOUT_15s 	},	//	E_IDX_MQTT_DISBALE_ENABLE_MODEM
		{ 	"AT+QMTSUB=", 				"XXXX", 			"+QMTSUB:", 			ERROR_STR, 		TIMEOUT_15s 	},	//	E_IDX_MQTT_SUBSCRIBE
		{ 	"AT+QMTUNS=", 				OK_RSP, 			"+QMTUNS:", 			ERROR_STR, 		TIMEOUT_15s 	},	//	E_IDX_MQTT_UNSUBSCRIBE
		{	"AT+QFUPL=",				"CONNECT",			"+QFUPL:",				CME_ERROR,		TIMEOUT_30s		},	//	E_IDX_FILE_UPLOAD_CMD
		{	"",							OK_RSP,				"A",					CME_ERROR,		TIMEOUT_30s		},	//	E_IDX_UPLOAD_FILE_CONTENT
		{	"AT+QFDEL=",				OK_RSP,				NULL_STR,				CME_ERROR,		TIMEOUT_300MS	},	//	E_IDX_FILE_DELETE
		{ 	"AT+QMTDISC=", 				OK_RSP, 			"+QMTDISC:", 			ERROR_STR, 		TIMEOUT_30s 	},	//	E_IDX_MQTT_DISCONNECT
		{ 	"AT+QMTCLOSE=", 			"XXXX", 			"+QMTCLOSE:",	 		ERROR_STR, 		TIMEOUT_30s 	},	//	E_IDX_MQTT_CLOSE
//GPS
		{ 	"AT+QGPSCFG=", 				OK_RSP, 			"+QGPSCFG:", 			ERROR_STR, 		TIMEOUT_300MS 	},	// 	E_IDX_GPS_CFG
		{ 	"AT+QGPS=1", 				OK_RSP, 			NULL_STR, 				ERROR_STR, 		TIMEOUT_300MS 	},	// 	E_IDX_ENABLE_GNSS
		{ 	"AT+QGPSLOC=1", 			OK_RSP, 			"+QGPSLOC:", 			CME_ERROR, 		TIMEOUT_300MS 	} 	// 	E_IDX_GET_GPS_DATA
};

/* Blocking delay function */
static void delay(uint32_t delay_ms)
{
	uint32_t delay_cnt;

	TIMER_ClearEvent(&TIMER_0);

	delay_cnt = delay_ms * 100000;	//TIMER_DELAY_MUL_FACTOR;

	TIMER_SetTimeInterval(&TIMER_0, delay_cnt);

	TIMER_Start(&TIMER_0);

	while (!TIMER_GetInterruptStatus(&TIMER_0))
		;

	TIMER_Stop(&TIMER_0);
}

/**************************************************************************
 * Function Name	:	mod_enable4gModule
 *
 * Description   	:	This function enables the Module
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void mod_enable4gModule(void)
{
	DIGITAL_IO_SetOutputHigh(&MODULE_4G_EN_OUT_D);
	DIGITAL_IO_SetOutputLow(&DIGITAL_IO_PWRKEY);
	delay(3000);

	DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_PWRKEY);
	delay(3000);

	gb_isMqttConnected = false;
//	DIGITAL_IO_SetOutputLow(&DIGITAL_IO_PWR_KEY);
}

/**************************************************************************
 * Function Name	:	mod_disable4gModule
 *
 * Description   	:	This function disable the Module
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void mod_disable4gModule(void)
{
	DIGITAL_IO_SetOutputLow(&MODULE_4G_EN_OUT_D);
	DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_PWRKEY);
	delay(3000);

	DIGITAL_IO_SetOutputLow(&DIGITAL_IO_PWRKEY);
	delay(3000);

//	DIGITAL_IO_SetOutputLow(&DIGITAL_IO_PWR_KEY);
}

/**************************************************************************
 * Function Name	:	mod_open4gModPort
 *
 * Description   	:	This function opens the module port
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t
 *
 ****************************************************************************/
en_responseRetCodes_t mod_open4gModPort(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	/* Initialize the UART port */
	len_retStatus = at_initInterface();
	if (E_RET_SUCCESS == len_retStatus)
	{
		/* Do something after successful initialization */
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_receiveRsp
 *
 * Description   	:	This function reads data from port
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void mod_receiveRsp(void)
{
	if (at_isRxBuffEmpty() != true)
	{
		uint8_t lu8_rcvdByte = 0;

		lu8_rcvdByte = at_readPort();
		if (lu8_rcvdByte != 0)
		{
			gu8arr_respBuffer[sgu8_respCount++] = lu8_rcvdByte;
			lu8_rcvdByte = 0;

			if (NULL != strstr((const char*) gu8arr_respBuffer, (const char*) QMTSTAT))
			{
				uint8_t *lu8p_saveptr = (uint8_t *) strchr(
						(const char *) gu8arr_respBuffer, ':');

				if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
				{
					lu8p_saveptr += 2;

					uint8_t lu8_result = atoi((char *) lu8p_saveptr);
					if (sgu8_mqttClientId == lu8_result)	//check client Idx
					{
						lu8p_saveptr += 2;
						lu8_result = atoi((char *) lu8p_saveptr);	//check error code
						/* 1 --> Connection is closed or reset by a peer end
						 * 2 --> Sending PINGREQ packet timed out or failed
						 * 3 --> Sending CONNECT packet timed out or failed
						 * 4 --> Receiving CONNACK packet timed out or failed
						 * 6 --> The client closes MQTT connection due to packet sending failure all the time
						 * */
						if ((1 == lu8_result) || (2 == lu8_result) || (3 == lu8_result)
								|| (4 == lu8_result) || (6 == lu8_result))
						{
							if (gb_isMqttConnected == true)
							{
								sen_4gRunState = E_MQTT_OPEN_STATE;
								gb_isMqttConnected = false;
							}
						}
						else if (8 == lu8_result)//The client closes the MQTT connection
						{
							if (gb_isMqttConnected == true)
							{
								sen_4gRunState = E_MQTT_CONNECT_STATE;
								gb_isMqttConnected = false;
							}
						}
					}
				}
			}
			else if ((NULL
					!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTRECV)))
			{
				uint8_t *lu8p_saveptr = (uint8_t *) strchr(
						(const char *) gu8arr_respBuffer, ':');

				if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
				{
					sgu8_respCount = 0;
					memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
				}
			}
			else if (sgu8_respCount == 1)
			{
				if ((gu8arr_respBuffer[0] == 0xFF) || (gu8arr_respBuffer[0] == '\n'))
				{
					sgu8_respCount = 0;
					memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
				}
			}
			else if ((NULL
					!= strstr((const char*) gu8arr_respBuffer,
							(const char*) "QIND: SMS DONE\r\n")))
			{
				gst_deviceStatus.mb_ismodemPwrDwn = false;
				sgu8_respCount = 0;
				memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
				sen_4gRunState = E_SET_URC_PORT_STATE;
				delay(2000);
			}
			else if (RDY_SIZE == sgu8_respCount)
			{
				if ((NULL != strstr((const char*) gu8arr_respBuffer, (const char*) READY)))
				{
					gst_deviceStatus.mb_ismodemPwrDwn = false;
					sgu8_respCount = 0;
					memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
					sen_4gRunState = E_ECHO_OFF_STATE;
					delay(2000);
				}
			}
			else if (PWR_DOWN_SIZE == sgu8_respCount)
			{
				if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) PWR_DWN)))
				{
					gst_deviceStatus.mb_ismodemPwrDwn = true;
					sgu8_respCount = 0;
					memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
				}
			}
		}
	}
}

/**************************************************************************
 * Function Name	:	mod_sendCmd
 *
 * Description   	:	This function sends data from port
 *
 * Arguments     	:	uint8_t *lu8p_data
 * 						uint16_t lu16_len
 *
 * Return values 	: 	en_responseRetCodes_t
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_sendCmd(uint8_t *lu8p_data, uint16_t lu16_len)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t lu8_ret = 0;

	lu8_ret = at_writePort(lu8p_data, lu16_len);
	if (E_SUCCESS == lu8_ret)
	{
		len_retStatus = E_RET_SUCCESS;
	}
	else
	{
		len_retStatus = E_RET_WRITE_ERROR;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_sendCmdGetRsp
 *
 * Description   	:	This function sends command and get response
 *
 * Arguments     	:	en_ATCommandList_t -
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ***************************************************************************/
static en_responseRetCodes_t mod_sendCmdGetRsp(en_ATCommandIdx_t len_ATCmdIdx,
		uint8_t *lu8p_cmdParam)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t lu8arr_sendCmdBuff[SEND_AT_CMD_BUFF];
	uint16_t lu16_BufferSize = 0;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t *lu8p_saveptr = NULL;

	switch (sen_sendCmdGetRespState)
	{
		case E_AT_CMD_IDLE_STATE:
			sgu8_respCount = 0;
			memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
			sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
		break;

		case E_AT_CMD_SEND_INPROG_STATE:
			memset(lu8arr_sendCmdBuff, 0, sizeof(lu8arr_sendCmdBuff));

			strncpy((char *) lu8arr_sendCmdBuff,
					(char *) gcst_ATCmdTable[len_ATCmdIdx].mu8arr_cmdString,
					strlen((char *)gcst_ATCmdTable[len_ATCmdIdx].mu8arr_cmdString));

			if (NULL != lu8p_cmdParam)
			{
				strcat((char *) lu8arr_sendCmdBuff, (char *) lu8p_cmdParam);
			}

			lu16_BufferSize = strlen((char *) lu8arr_sendCmdBuff);
			len_retStatus = mod_sendCmd(lu8arr_sendCmdBuff, lu16_BufferSize);
			if (E_RET_SUCCESS == len_retStatus)
			{
				memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
				sgu8_respCount = 0;
				tm_setResponseTime(gcst_ATCmdTable[len_ATCmdIdx].mu32_respTimeoutInMs);
				len_retStatus = E_RET_INPROGRESS;
				sen_sendCmdGetRespState = E_AT_CMD_RECV_INPROG_STATE;
			}
		break;

		case E_AT_CMD_RECV_INPROG_STATE:
			if (sgu8_respCount > 0)
			{
				if ((NULL
						!= strstr((const char*) gu8arr_respBuffer,
								(const char*) gcst_ATCmdTable[len_ATCmdIdx].mu8arr_respString)))
				{
					sgu8_respCount = 0;
					tm_clearResponseTime();
					len_retStatus = E_RET_SUCCESS;
					sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
				}

				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTOPEN)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');
					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
//				else if ((NULL
//						!= strstr((const char*) gu8arr_respBuffer, (const char*) "+QGPSLOC:")))
//				{
//					if(sgu8_respCount > 64)
//					{
//						sgu8_respCount = 0;
//						memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
//						at_clearBuff();
//					}
//				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTPUBEX)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');
					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTCONN)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');
					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTDISC)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');

					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTSUB)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');

					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer, (const char*) QMTRECV)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');

					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer,
								(const char*) CME_ERROR)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');

					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						lu8p_Ptr = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
								(const char *) ":", (char **) &lu8p_saveptr);
						lu8p_saveptr++;

						sgu16_cmeError = (uint16_t) atoi((const char *) lu8p_saveptr);

						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_CME_ERROR;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						!= strstr((const char*) gu8arr_respBuffer,
								(const char*) CMS_ERROR)))
				{
					lu8p_saveptr = (uint8_t *) strchr((const char *) gu8arr_respBuffer,
							':');

					if (NULL != strchr((const char *) lu8p_saveptr, '\n'))
					{
						lu8p_Ptr = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
								(const char *) ":", (char **) &lu8p_saveptr);
						lu8p_saveptr++;

						sgu16_cmsError = (uint16_t) atoi((const char *) lu8p_saveptr);

						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_CMS_ERROR;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if (E_IDX_UPLOAD_FILE_CONTENT == len_ATCmdIdx)
				{
					if ((NULL
							!= strstr((const char*) gu8arr_respBuffer,
									(const char*) "A")))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
						len_retStatus = E_RET_SUCCESS;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}
				}
				else if ((NULL
						== strstr((const char*) NULL_STR,
								(const char*) gcst_ATCmdTable[len_ATCmdIdx].mu8arr_errString)))
				{
					if ((NULL
							!= strstr((const char*) gu8arr_respBuffer,
									(const char*) gcst_ATCmdTable[len_ATCmdIdx].mu8arr_errString)))
					{
						sgu8_respCount = 0;
						tm_clearResponseTime();
//						tm_stopTimer();
						len_retStatus = E_RET_RSP_ERROR;
						sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
					}

				}
			}
			else
			{
				if (tm_getResponseTimeValue() == 0)
				{
					sgu8_respCount = 0;
					memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
					tm_clearResponseTime();
					len_retStatus = E_RET_TIMEOUT_ERROR;
					sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
				}
			}
		break;

		default:
			sen_sendCmdGetRespState = E_AT_CMD_SEND_INPROG_STATE;
			len_retStatus = E_RET_INPROGRESS;
		break;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_echoOff
 *
 * Description   	:	This function sets echo OFF
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_echoOff(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_ECHO_OFF, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}
/**************************************************************************
 * Function Name	:	mod_setUrcPort
 *
 * Description   	:	This function sets URC output
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_setUrcPort(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[10] = "\"usbat\"\r\n";

	len_retStatus = mod_sendCmdGetRsp(E_IDX_SET_URC_PRT, lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_setFlowCtrl
 *
 * Description   	:	This function sets the flow control of the port
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_setFlowCtrl(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[10] = "0,0\r\n";	//0,0 ---> none, none
	//uint8_t lu8arr_param[10] = "2,2\r\n";	//0,0 ---> RTS, CTS

	len_retStatus = mod_sendCmdGetRsp(E_IDX_HW_FLWCTRL, lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_extractModInfo
 *
 * Description   	:	This function extract the module info
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractModInfo(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_temp = NULL;
	uint8_t *lu8p_saveptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_FEATCH_MOD_INFO, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		if ((NULL != strstr((const char*) gu8arr_respBuffer, (const char*) PRODCUT_NAME)))
		{
			lu8p_temp = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
					(const char *) ":", (char **) &lu8p_saveptr);
			lu8p_saveptr++;
			if (NULL != lu8p_temp)
			{
				memcpy(gu8arr_productRevision, lu8p_saveptr, PRO_REVISION_SIZE);
			}
			else
			{
				len_retStatus = E_RET_FAILED;
			}
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_getModuleInfo
 *
 * Description   	:	This function gets the module info
 *
 * Arguments     	:	uint8_t * Pointer points to an array
 *
 * Return values 	:	uint8_t - length
 *
 ****************************************************************************/
uint8_t mod_getModuleInfo(uint8_t *lu8p_data)
{
	uint8_t lu8_ret = 0;

	if (NULL != lu8p_data)
	{
		memcpy(lu8p_data, gu8arr_productRevision, PRO_REVISION_SIZE);
		lu8_ret = PRO_REVISION_SIZE;
	}

	return lu8_ret;
}

/**************************************************************************
 * Function Name	:	mod_enableSimDetection
 *
 * Description   	:	This function enables the SIM detection
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_enableSimDetection(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[10] = "1,0\r\n";

	len_retStatus = mod_sendCmdGetRsp(E_IDX_ENABLE_SIM_DETECTION, lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_enableSimStatusReport
 *
 * Description   	:	This function enables the SIM status report
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_enableSimStatusReport(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[10] = "1\r\n";

	len_retStatus = mod_sendCmdGetRsp(E_IDX_ENABLE_SIM_STATUS, lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_checkSimStatus
 *
 * Description   	:	This function checks the status of the SIM
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_checkSimStatus(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_temp = NULL;
	uint8_t *lu8p_saveptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_CHECK_SIM_STATUS, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		if ((NULL
				!= strstr((const char*) gu8arr_respBuffer,
						(const char*) gcst_ATCmdTable[E_IDX_CHECK_SIM_STATUS].mu8arr_otherRspString)))
		{
			lu8p_temp = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
					(const char *) ":", (char **) &lu8p_saveptr);
			if (NULL != lu8p_temp)
			{
				lu8p_temp = (uint8_t *) strchr((const char*) lu8p_saveptr, ',');
				if (NULL != lu8p_temp)
				{
					lu8p_temp = (uint8_t *) strtok_r(NULL, (const char *) ",",
							(char **) &lu8p_saveptr);

					gst_deviceStatus.mb_isSimInserted = (uint8_t) atoi(
							(const char*) lu8p_saveptr);

					if (true == gst_deviceStatus.mb_isSimInserted)
					{
						len_retStatus = E_RET_SUCCESS;
					}
					else
					{
						len_retStatus = E_RET_INPROGRESS;
					}
				}
				else
				{
					len_retStatus = E_RET_FAILED;
				}
			}
			else
			{
				len_retStatus = E_RET_FAILED;
			}
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_cpinCheck
 *
 * Description   	:	This function checks the CPIN command
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_cpinCheck(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_CPIN_CHECK, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "READY");
		if (NULL != lu8p_Ptr)
		{
			len_retStatus = E_RET_SUCCESS;
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_extractIMEI
 *
 * Description   	:	This function extract the IMEI number and saves the
 * 						IMEI number to global buffer
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractIMEI(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8_index = 0;
	uint8_t lu8ar_TempIMEI[IMEI_SIZE] = { 0 };

	len_retStatus = mod_sendCmdGetRsp(E_IDX_GET_IMEI, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		memcpy((char *) &lu8ar_TempIMEI[0], (const char *) &gu8arr_respBuffer[2],
		IMEI_SIZE);
		for (lu8_index = 0; lu8_index < IMEI_SIZE; lu8_index++)
		{
			if (!('0' <= lu8ar_TempIMEI[lu8_index] && '9' >= lu8ar_TempIMEI[lu8_index]))
			{
				len_retStatus = E_RET_FAILED;
				break;
			}
		}
		if (lu8_index >= IMEI_SIZE)
		{
			memcpy((char *) &gu8arr_IMEINum, (const char *) &gu8arr_respBuffer[2],
			IMEI_SIZE);	//\r\n skipped
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_getIMEI
 *
 * Description   	:	This function gets the IMEI
 *
 * Arguments     	:	uint8_t* - Pointer points to an array
 *
 * Return values 	:	uint8_t - length
 *
 ****************************************************************************/
uint8_t mod_getIMEI(uint8_t *lu8p_data)
{
	uint8_t lu8_ret = 0;

	if (NULL != lu8p_data)
	{
		memcpy(lu8p_data, gu8arr_IMEINum, IMEI_SIZE);
		lu8_ret = IMEI_SIZE;
	}

	return lu8_ret;
}
/**************************************************************************
 * Function Name	:	mod_extractCCID
 *
 * Description   	:	This function extract the CCID number and saves the
 * 						CCID number to global buffer
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractCCID(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_temp = NULL;
	uint8_t *lu8p_saveptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_GET_CCID, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		if ((NULL
				!= strstr((const char*) gu8arr_respBuffer,
						(const char*) gcst_ATCmdTable[E_IDX_GET_CCID].mu8arr_otherRspString)))
		{
			lu8p_temp = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
					(const char *) ":", (char **) &lu8p_saveptr);
			lu8p_saveptr++;

			if (NULL != lu8p_saveptr)
			{
				memset(gu8arr_CCIDNum, 0, sizeof(gu8arr_CCIDNum));
				memcpy((char *) &gu8arr_CCIDNum, (const char *) lu8p_saveptr, CCID_SIZE);
			}
			else
			{
				len_retStatus = E_RET_FAILED;
			}
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_getCCID
 *
 * Description   	:	This function gets the CCID
 *
 * Arguments     	:	uint8_t* - Pointer points to an array
 *
 * Return values 	:	uint8_t - length
 *
 ****************************************************************************/
uint8_t mod_getCCID(uint8_t *lu8p_data)
{
	uint8_t lu8_ret = 0;

	if (NULL != lu8p_data)
	{
		memcpy(lu8p_data, gu8arr_CCIDNum, CCID_SIZE);
		lu8_ret = CCID_SIZE;
	}

	return lu8_ret;
}

/**************************************************************************
 * Function Name	:	mod_extractNUM
 *
 * Description   	:	This function extract the phone number and saves the
 * 						phone number to global buffer
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractNUM(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_temp = NULL;
	uint8_t *lu8p_saveptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_GET_NUM, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		if ((NULL
				!= strstr((const char*) gu8arr_respBuffer,
						(const char*) gcst_ATCmdTable[E_IDX_GET_NUM].mu8arr_otherRspString)))
		{
			lu8p_temp = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
					(const char *) ":", (char **) &lu8p_saveptr);

			lu8p_saveptr++;
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_getPhoneNum
 *
 * Description   	:	This function gets the Phone Number
 *
 * Arguments     	:	uint8_t* - Pointer points to an array
 *
 * Return values 	:	uint8_t - length
 *
 ****************************************************************************/
uint8_t mod_getPhoneNum(uint8_t *lu8p_data)
{
	uint8_t lu8_ret = 0;

	if (NULL != lu8p_data)
	{
		memcpy(lu8p_data, gu8arr_phoneNum, PHONE_SIZE);
		lu8_ret = PHONE_SIZE;
	}

	return lu8_ret;
}

/**************************************************************************
 * Function Name	:	mod_extractOperator
 *
 * Description   	:	This function extract the SIM operator
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractOperator(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t *lu8p_savePtr = NULL;
	uint8_t *lu8p_dataPtr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_GET_OPERATOR, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		if ((NULL
				!= strstr((const char*) gu8arr_respBuffer,
						(const char*) gcst_ATCmdTable[E_IDX_GET_OPERATOR].mu8arr_otherRspString)))
		{
			lu8p_Ptr = (uint8_t *) strtok_r((char *) gu8arr_respBuffer,
					(const char *) ":", (char **) &lu8p_savePtr);

			if (NULL != lu8p_Ptr)
			{
				lu8p_dataPtr = lu8p_savePtr;
				lu8p_dataPtr = (uint8_t *) strchr((const char*) lu8p_dataPtr, ',');

				if (NULL != lu8p_dataPtr)
				{
					lu8p_Ptr = (uint8_t *) strtok_r(NULL, (const char *) ",",
							(char **) &lu8p_savePtr);

					lu8p_Ptr = (uint8_t *) strtok_r(NULL, (const char *) ",",
							(char **) &lu8p_savePtr);

					lu8p_savePtr++;
					lu8p_Ptr = (uint8_t *) strtok_r(NULL, (const char *) "\"",
							(char **) &lu8p_savePtr);

					if (lu8p_Ptr != NULL)
					{
						memset(gu8_operatorName, 0, sizeof(gu8_operatorName));
						strcpy((char *) &gu8_operatorName, (const char *) lu8p_Ptr);
					}
					else
					{
						len_retStatus = E_RET_FAILED;
					}
				}
				else
				{
					len_retStatus = E_RET_FAILED;
				}
			}
			else
			{
				len_retStatus = E_RET_FAILED;
			}
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_getOperator
 *
 * Description   	:	This function gets the Operator Name
 *
 * Arguments     	:	uint8_t* - Pointer points to an array
 *
 * Return values 	:	uint8_t - length
 *
 ****************************************************************************/
uint8_t mod_getOperator(uint8_t *lu8p_data)
{
	uint8_t lu8_ret = 0;

	if (NULL != lu8p_data)
	{
		memcpy(lu8p_data, gu8_operatorName, OPERATOR_SIZE);
		lu8_ret = OPERATOR_SIZE;
	}

	return lu8_ret;
}

/**************************************************************************
 * Function Name	:	mod_simStatus
 *
 * Description   	:	This function extract the sim info and checks the SIM status
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
en_responseRetCodes_t mod_simStatus(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	switch (sen_simStatusState)
	{
		case E_SIM_ENABLE_SIM_DETECTION_STATE:
			len_retStatus = mod_enableSimDetection();
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_ENABLE_SIM_STATUS_STATE;
			}
		break;

		case E_SIM_ENABLE_SIM_STATUS_STATE:
			len_retStatus = mod_enableSimStatusReport();
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_CHECK_SIM_STATUS_STATE;
			}
		break;

		case E_SIM_CHECK_SIM_STATUS_STATE:
			len_retStatus = mod_checkSimStatus();
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_CPIN_CHECK_STATE;
			}
		break;

		case E_SIM_CPIN_CHECK_STATE:
			len_retStatus = mod_cpinCheck();
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_EXCTRACT_IMEI_STATE;
			}
		break;

		case E_SIM_EXCTRACT_IMEI_STATE:
			len_retStatus = mod_extractIMEI();
			if ((E_RET_SUCCESS == len_retStatus) || (E_RET_INPROGRESS != len_retStatus))
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_EXCTRACT_CCID_STATE;
			}
		break;

		case E_SIM_EXCTRACT_CCID_STATE:
			len_retStatus = mod_extractCCID();
			if ((E_RET_SUCCESS == len_retStatus) || (E_RET_INPROGRESS != len_retStatus))
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_EXTRACT_NUM_STATE;
			}
		break;

		case E_SIM_EXTRACT_NUM_STATE:
			len_retStatus = mod_extractNUM();
			if ((E_RET_SUCCESS == len_retStatus) || (E_RET_INPROGRESS != len_retStatus))
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_simStatusState = E_SIM_EXTRACT_OPERATOR_STATE;
			}
		break;

		case E_SIM_EXTRACT_OPERATOR_STATE:
			len_retStatus = mod_extractOperator();
			if ((E_RET_SUCCESS == len_retStatus) || (E_RET_INPROGRESS != len_retStatus))
			{
				len_retStatus = E_RET_SUCCESS;
				sen_simStatusState = E_SIM_ENABLE_SIM_DETECTION_STATE;
			}
		break;

		default:
			sen_simStatusState = E_SIM_ENABLE_SIM_DETECTION_STATE;
		break;
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_networkStatus
 *
 * Description   	:	This function checks the network status
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_networkStatus(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_CREG, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_INPROGRESS;

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "0,0");
		if (NULL != lu8p_Ptr)
		{
			//Not registered
			gst_deviceStatus.men_networkRegStatus = E_REGISTERED_NONE;
			len_retStatus = E_RET_FAILED;
			return len_retStatus;
		}

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "0,1");
		if (NULL != lu8p_Ptr)
		{
			//home network
			gst_deviceStatus.men_networkRegStatus = E_REGISTERED_HOME;
			len_retStatus = E_RET_SUCCESS;
			return len_retStatus;
		}

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "0,2");
		if (NULL != lu8p_Ptr)
		{
			//Not Registered
			gst_deviceStatus.men_networkRegStatus = E_NOT_REGISTERED;
			len_retStatus = E_RET_FAILED;
			return len_retStatus;
		}

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "0,3");
		if (NULL != lu8p_Ptr)
		{
			//Registration denied
			gst_deviceStatus.men_networkRegStatus = E_REGISTER_DENIED;
			len_retStatus = E_RET_FAILED;
			return len_retStatus;
		}

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "0,4");
		if (NULL != lu8p_Ptr)
		{
			//Unknown
			gst_deviceStatus.men_networkRegStatus = E_UNKNOWN;
			len_retStatus = E_RET_FAILED;
			return len_retStatus;
		}

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer, "0,5");
		if (NULL != lu8p_Ptr)
		{
			//Registered, roaming
			gst_deviceStatus.men_networkRegStatus = E_REGISTERED_ROAMING;
			len_retStatus = E_RET_SUCCESS;
			return len_retStatus;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_signalQuality
 *
 * Description   	:	This function gets the signal quality
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_signalQuality(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_SIGNAL_QLTY, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{

		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) gcst_ATCmdTable[E_IDX_SIGNAL_QLTY].mu8arr_otherRspString);
		if (lu8p_Ptr != NULL)
		{
			lu8p_Ptr += 6;
			gu8_signalQuality = atoi((char *) lu8p_Ptr++);
			lsu8_retryCnt = 0;
			len_retStatus = E_RET_SUCCESS;
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_getSignalQuality
 *
 * Description   	:	This function returns the signal quality
 *
 * Arguments     	:	uint8_t* - Pointer points to an array
 *
 * Return values 	:	uint8_t
 *
 ****************************************************************************/
uint8_t mod_getSignalQuality(void)
{
	return gu8_signalQuality;
}

/**************************************************************************
 * Function Name	:	mod_extractDateTime
 *
 * Description   	:	This function extracts the Date and Time
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractDateTime(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t *lu8p_savePtr = NULL;
	uint8_t lu8arr_tempBuff[50] = { 0 };

	len_retStatus = mod_sendCmdGetRsp(E_IDX_CCLK, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) gcst_ATCmdTable[E_IDX_CCLK].mu8arr_otherRspString);
		if (lu8p_Ptr != NULL)
		{
			lsu8_retryCnt = 0;

			memcpy(lu8arr_tempBuff, gu8arr_respBuffer, 50);
			lu8p_Ptr = (uint8_t *) strtok_r((char *) lu8arr_tempBuff, (const char *) ":",
					(char **) &lu8p_savePtr);
			lu8p_savePtr += 2;
			if (NULL != lu8p_savePtr)
			{
				memset(gu8_dataTime, 0, sizeof(gu8_dataTime));
				strncpy((char *) gu8_dataTime, (const char *) lu8p_savePtr,
				TIME_SIZE);
			}
			len_retStatus = E_RET_SUCCESS;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttConnect
 *
 * Description   	:	This function used connect to the MQTT broker
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttConnect(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[35] = { 0 };
	uint8_t *lu8p_Ptr = NULL;
	short ls_result = E_MQTT_CON_NONE;

	sprintf((char *) lu8arr_param, (const char*) "%d,\"%s_%s\"\r\n",
			sgu8_mqttClientId, MQTT_CONNECT_CLINT_ID, &gu8arr_IMEINum[5]);	//using last 10 digits of IMEI for unique client ID for every VCU

	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_CONNECT, (uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) gcst_ATCmdTable[E_IDX_MQTT_CONNECT].mu8arr_otherRspString);

		if (lu8p_Ptr != NULL)
		{
			lu8p_Ptr += 10;
			ls_result = atoi((char *) lu8p_Ptr);
			if (sgu8_mqttClientId == ls_result)	//check client Idx
			{
				lu8p_Ptr += 2;
				ls_result = atoi((char *) lu8p_Ptr);
				if (0 == ls_result)	//Packet sent successfully and ACK received from server
				{
					lu8p_Ptr += 2;
					ls_result = atoi((char *) lu8p_Ptr);
					if (0 == ls_result)	//Connection Accepted
					{
						gst_deviceStatus.men_mqttConnectErrorCodes =
								E_ACK_RCVD_CONNECT_ACCEPT;

						len_retStatus = E_RET_SUCCESS;
					}
					else
					{
						gst_deviceStatus.men_mqttConnectErrorCodes = E_CON_UNKNOWN_ERROR;
						len_retStatus = E_RET_FAILED;
					}
				}
				else if (1 == ls_result)	//Packet retransmission
				{
					gst_deviceStatus.men_mqttConnectErrorCodes = E_PACKET_RETRANSMISSION;
					len_retStatus = E_RET_INPROGRESS;
				}
				else if (2 == ls_result)	//Failed to send packet
				{
					lu8p_Ptr += 2;
					ls_result = atoi((char *) lu8p_Ptr);
					if (1 == ls_result)	//Connection Refused: Unacceptable Protocol Version
					{
						gst_deviceStatus.men_mqttConnectErrorCodes =
								E_CON_REF_UNACC_PRO_VER;
					}
					else if (2 == ls_result)	//Connection Refused: Identifier Rejected
					{
						gst_deviceStatus.men_mqttConnectErrorCodes = E_CON_REF_ID_REJECT;
					}
					else if (3 == ls_result)	//Connection Refused: Server Unavailable
					{
						gst_deviceStatus.men_mqttConnectErrorCodes =
								E_CON_REF_SERVER_UNAVAIL;
					}
					else if (4 == ls_result)//Connection Refused: Bad User Name or Password
					{
						gst_deviceStatus.men_mqttConnectErrorCodes =
								E_CON_REF_BAD_USR_PASS;
					}
					else if (5 == ls_result) //Connection Refused: Not Authorized
					{
						gst_deviceStatus.men_mqttConnectErrorCodes = E_CON_REF_NOT_AUTH;
					}
					else
					{
						gst_deviceStatus.men_mqttConnectErrorCodes = E_CON_UNKNOWN_ERROR;
					}

					len_retStatus = E_RET_FAILED;
				}
				else
				{
					gst_deviceStatus.men_mqttConnectErrorCodes = E_CON_UNKNOWN_ERROR;
					len_retStatus = E_RET_FAILED;
				}
			}
			else
			{
				len_retStatus = E_RET_FAILED;
			}
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_RSP_ERROR == len_retStatus)
	{
		lsu8_retryCnt = 0;
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) QMTSTAT);
		if (lu8p_Ptr != NULL)
		{
			if (lu8p_Ptr != NULL)
			{
				lu8p_Ptr += 10;
				ls_result = atoi((char *) lu8p_Ptr);
				if (sgu8_mqttClientId == ls_result)	//check client Idx
				{
					lu8p_Ptr += 2;
					ls_result = atoi((char *) lu8p_Ptr);	//check error code
					if (1 == ls_result)
					{
						len_retStatus = E_RET_CONN_CLOSED_ERROR;
					}
					else
					{
						len_retStatus = E_RET_FAILED;
					}
				}
				else
				{
					len_retStatus = E_RET_FAILED;
				}
			}
			else
			{
				len_retStatus = E_RET_FAILED;
			}
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}

	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttDisConnect
 *
 * Description   	:	This function used disconnect to the MQTT broker
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttDisConnect(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[3] = { 0 };
	uint8_t *lu8p_Ptr = NULL;
	short ls_result = E_MQTT_DISCON_NONE;

	sprintf((char *) lu8arr_param, (const char*) "%d\r\n", sgu8_mqttClientId);
	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_DISCONNECT, (uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;

		lu8p_Ptr =
				(uint8_t *) strstr((const char *) gu8arr_respBuffer,
						(const char *) gcst_ATCmdTable[E_IDX_MQTT_DISCONNECT].mu8arr_otherRspString);

		if (lu8p_Ptr != NULL)
		{
			lu8p_Ptr += 14;
			ls_result = atoi((char *) lu8p_Ptr);
			if (sgu8_mqttClientId == lu8p_Ptr)
			{
				lu8p_Ptr += 2;
				ls_result = atoi((char *) lu8p_Ptr);
				if (E_MQTT_FAILED_TO_CLOSE_CONN == ls_result)
				{
					gst_deviceStatus.men_mqttDisconErrorCodes = E_MQTT_FAILED_TO_CLOSE_CONN;
					len_retStatus = E_RET_FAILED;
				}
				else if(E_MQTT_CONN_CLOSE_SUCCESS == ls_result)
				{
					gst_deviceStatus.men_mqttDisconErrorCodes = E_MQTT_CONN_CLOSE_SUCCESS;
					len_retStatus = E_RET_SUCCESS;
				}
			}
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttEnableFunctionality
 *
 * Description   	:	This function enable the modem
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttEnableFunctionality(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[3] = { 0 };

	sprintf((char *) lu8arr_param, (const char*) "1\r\n");
	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_DISBALE_ENABLE_MODEM,
			(uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_SUCCESS;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttDisableFunctionality
 *
 * Description   	:	This function disable the modem
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttDisableFunctionality(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[3] = { 0 };

	sprintf((char *) lu8arr_param, (const char*) "4\r\n");
	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_DISBALE_ENABLE_MODEM,
			(uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_SUCCESS;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttDisableEnableFunctionality
 *
 * Description   	:	This function used disable and enable the module
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttDisableEnableFunctionality(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	switch (sen_modemResetState)
	{
		case E_RST_DISABLE_FUNCTION:
			len_retStatus = mod_mqttDisableFunctionality();
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_modemResetState = E_RST_ENALBE_FUNCTION;
				tm_setResetTimer(5000);
			}
		break;

		case E_RST_ENALBE_FUNCTION:
			if (tm_getResetTimerValue() == 0)
			{
				len_retStatus = mod_mqttEnableFunctionality();
				if (E_RET_SUCCESS == len_retStatus)
				{
					len_retStatus = E_RET_INPROGRESS;
					sen_modemResetState = E_RST_WAIT_FUNCTION;
					tm_setResetTimer(5000);
				}
			}
		break;

		case E_RST_WAIT_FUNCTION:
			if (tm_getResetTimerValue() == 0)
			{
				sen_modemResetState = E_RST_DISABLE_FUNCTION;
				len_retStatus = E_RET_SUCCESS;
			}
		break;

		default:
		break;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttClose
 *
 * Description   	:	This function used close the MQTT broker
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttClose(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[3] = { 0 };
	uint8_t *lu8p_Ptr = NULL;
	short ls_result = E_MQTT_CLOSE_NONE;

	sprintf((char *) lu8arr_param, (const char*) "%d\r\n", sgu8_mqttClientId);
	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_CLOSE, (uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) gcst_ATCmdTable[E_IDX_MQTT_CLOSE].mu8arr_otherRspString);

		if (lu8p_Ptr != NULL)
		{
			lu8p_Ptr += 14;
			ls_result = atoi((char *) lu8p_Ptr);
			if(sgu8_mqttClientId == lu8p_Ptr)
			{
				lu8p_Ptr += 2;
				ls_result = atoi((char *) lu8p_Ptr);
				if(E_MQTT_FAILED_TO_CLOSE_NW == ls_result)
				{
					gst_deviceStatus.men_mqttCloseErrorCodes = E_MQTT_FAILED_TO_CLOSE_NW;
					len_retStatus = E_RET_FAILED;
				}
				else if(E_MQTT_NW_CLOSE_SUCCESS == ls_result)
				{
					gst_deviceStatus.men_mqttCloseErrorCodes = E_MQTT_NW_CLOSE_SUCCESS;
					len_retStatus = E_RET_SUCCESS;
				}
			}
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
* Function Name	:	mod_mqttPublishData
*
* Description   	:	This function used to the MQTT broker
*
* Arguments     	:	uint8_t * - Data to be publish
*						uint16_t - Data length
*						uint8_t * - Topic to publish
*
* Return values 	:	en_responseRetCodes_t - return status
*
****************************************************************************/
static en_responseRetCodes_t mod_mqttPublishData(uint8_t * lu8p_data, uint16_t lu16_len, uint8_t* lu8p_topic)
{
	static uint8_t lsu8_retryCnt = 0;
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t lu8arr_param[50] = { 0 };
	short ls_result = 0;
	uint64_t lu64_totalTime = 0;
 
	switch (sen_publishDataState)
	{
		case E_PUBLISH_CMD_STATE:
 
			sprintf((char *) lu8arr_param, (const char*) "%d,1,%d,0,%s,%d\r\n",
					sgu8_mqttClientId, MQTT_PUBLISH_QOS, lu8p_topic, lu16_len);
 
			len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_PUBLISH,
					(uint8_t *) lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				lu8p_Ptr =
						(uint8_t *) strstr((const char *) gu8arr_respBuffer,
								(const char *) gcst_ATCmdTable[E_IDX_MQTT_PUBLISH].mu8arr_respString);
				if (NULL != lu8p_Ptr)
				{
					lsu8_retryCnt = 0;
 
					memset(gcst_ATCmdTable[E_IDX_MQTT_PUBLISH_DATA].mu8arr_cmdString, 0,
							sizeof(gcst_ATCmdTable[E_IDX_MQTT_PUBLISH_DATA].mu8arr_cmdString));
 
					strncpy(
							(char *) gcst_ATCmdTable[E_IDX_MQTT_PUBLISH_DATA].mu8arr_cmdString,
							(char *) lu8p_data, lu16_len);
 
					gcst_ATCmdTable[E_IDX_MQTT_PUBLISH_DATA].mu8arr_cmdString[lu16_len++] =
							'\0';
 
					sen_publishDataState = E_PUBLISH_DATA_STATE;
					len_retStatus = E_RET_INPROGRESS;
				}
 
				sgu8_respCount = 0;
				memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
			}
			else if(E_RET_CME_ERROR == len_retStatus)
			{
				if(sgu16_cmeError == 58)
				{
					len_retStatus = E_RET_CME_ERROR;
				}
			}
			else if (E_RET_RSP_ERROR == len_retStatus)
			{
				lsu8_retryCnt = 0;
				lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
						(const char *) QMTSTAT);
				if (lu8p_Ptr != NULL)
				{
					if (lu8p_Ptr != NULL)
					{
						lu8p_Ptr += 10;
						ls_result = atoi((char *) lu8p_Ptr);
						if (sgu8_mqttClientId == ls_result)	//check client Idx
						{
							lu8p_Ptr += 2;
							ls_result = atoi((char *) lu8p_Ptr);	//check error code
							if (1 == ls_result)
							{
								len_retStatus = E_RET_CONN_CLOSED_ERROR;
							}
							else
							{
								len_retStatus = E_RET_FAILED;
							}
						}
						else
						{
							len_retStatus = E_RET_FAILED;
						}
					}
					else
					{
						len_retStatus = E_RET_FAILED;
					}
				}
				else
				{
					len_retStatus = E_RET_FAILED;
				}
 
				sgu8_respCount = 0;
				memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
 
			}
			else if (E_RET_INPROGRESS != len_retStatus)
			{
				lsu8_retryCnt++;
				if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
				{
					len_retStatus = E_RET_INPROGRESS;
				}
				else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
				{
					lsu8_retryCnt = 0;
					len_retStatus = E_RET_TIMEOUT_ERROR;
				}
			}
		break;
 
		case E_PUBLISH_DATA_STATE:
			len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_PUBLISH_DATA, NULL);
			if (E_RET_SUCCESS == len_retStatus)
			{
				lu8p_Ptr =
						(uint8_t *) strstr((const char *) gu8arr_respBuffer,
								(const char *) gcst_ATCmdTable[E_IDX_MQTT_PUBLISH_DATA].mu8arr_otherRspString);
				if (NULL != lu8p_Ptr)
				{
					lu8p_Ptr += 11;
					ls_result = atoi((const char *) lu8p_Ptr);
					if (sgu8_mqttClientId == ls_result)
					{
						lu8p_Ptr += 2;
						ls_result = atoi((const char *) lu8p_Ptr);
						if (1 == ls_result)	//msg id
						{
							lu8p_Ptr += 2;
							ls_result = atoi((const char *) lu8p_Ptr);
							if (E_PUB_SUCCESS == ls_result)	//Packet sent successfully and ACK received
							{
								gst_deviceStatus.men_mqttPublishErrorCode = E_PUB_SUCCESS;
								len_retStatus = E_RET_SUCCESS;
								sen_publishDataState = E_PUBLISH_CMD_STATE;
							}
							else if(E_PUB_PACK_RETRAN == ls_result)	//Packet retransmission
							{
								gst_deviceStatus.men_mqttPublishErrorCode = E_PUB_PACK_RETRAN;
								len_retStatus = E_RET_INPROGRESS;
							}
							else if(E_PUB_FAILED_SEND_PACK == ls_result)	//Failed to send packet
							{
								gst_deviceStatus.men_mqttPublishErrorCode = E_PUB_FAILED_SEND_PACK;
								len_retStatus = E_RET_FAILED;
							}
							else
							{
								gst_deviceStatus.men_mqttPublishErrorCode = E_PUB_UNKNOWN_ERROR;
								len_retStatus = E_RET_FAILED;
							}
						}
					}
				}
 
				sgu8_respCount = 0;
				memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
			}
			else if (E_RET_RSP_ERROR == len_retStatus)
			{
				lsu8_retryCnt = 0;
				lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
						(const char *) QMTSTAT);
				if (lu8p_Ptr != NULL)
				{
					if (lu8p_Ptr != NULL)
					{
						lu8p_Ptr += 10;
						ls_result = atoi((char *) lu8p_Ptr);
						if (sgu8_mqttClientId == ls_result)	//check client Idx
						{
							lu8p_Ptr += 2;
							ls_result = atoi((char *) lu8p_Ptr);	//check error code
							if (1 == ls_result)
							{
								len_retStatus = E_RET_CONN_CLOSED_ERROR;
							}
							else
							{
								len_retStatus = E_RET_FAILED;
							}
						}
						else
						{
							len_retStatus = E_RET_FAILED;
						}
					}
					else
					{
						len_retStatus = E_RET_FAILED;
					}
				}
				else
				{
					len_retStatus = E_RET_FAILED;
				}
 
				sgu8_respCount = 0;
				memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
 
				sen_publishDataState = E_PUBLISH_CMD_STATE;
			}
			else if (E_RET_INPROGRESS != len_retStatus)
			{
				lsu8_retryCnt++;
				if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
				{
					len_retStatus = E_RET_INPROGRESS;
				}
				else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
				{
					lsu8_retryCnt = 0;
					len_retStatus = E_RET_TIMEOUT_ERROR;
				}
				sen_publishDataState = E_PUBLISH_CMD_STATE;
			}
		break;
 
		default:
			len_retStatus = E_RET_SUCCESS;
		break;
	}
 
	return len_retStatus;
}


/**************************************************************************
* Function Name	:	mod_mqttSubscribe
*
* Description   	:	This function used to subscribe the given topic
*
* Arguments     	:	uint8_t* - topic to subscribe
*
* Return values 	:	en_responseRetCodes_t - return status
*
****************************************************************************/
static en_responseRetCodes_t mod_mqttSubscribe(uint8_t * lpu8_topic)
{
	static uint8_t lsu8_retryCnt = 0;
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t lu8arr_param[50] = { 0 };
	short ls8_result = 0;
 
	sprintf((char *) lu8arr_param, "%d,1,%s,%d\r\n", sgu8_mqttClientId, lpu8_topic,
			MQTT_SUB_QOS);
	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_SUBSCRIBE, (uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
 
		lsu8_retryCnt = 0;
		lu8p_Ptr =
				(uint8_t *) strstr((const char *) gu8arr_respBuffer,
						(const char *) gcst_ATCmdTable[E_IDX_MQTT_SUBSCRIBE].mu8arr_otherRspString);
 
		if (NULL != lu8p_Ptr)
		{
			lu8p_Ptr += 13;
			ls8_result = atoi((const char *) lu8p_Ptr);
			if (sgu8_mqttClientId == ls8_result)
			{
				lu8p_Ptr += 2;
				ls8_result = atoi((const char *) lu8p_Ptr);
				if(1 == ls8_result)
				{
					lu8p_Ptr += 2;
					ls8_result = atoi((const char *) lu8p_Ptr);
					if(E_SUB_ACK_RCVD_CONN_ACCEPT == ls8_result)
					{
						gst_deviceStatus.men_mqttSubErrorCode = E_SUB_ACK_RCVD_CONN_ACCEPT;
						len_retStatus = E_RET_SUCCESS;
					}
					else if(E_SUB_RETRAN == ls8_result)
					{
						gst_deviceStatus.men_mqttSubErrorCode = E_SUB_RETRAN;
						len_retStatus = E_RET_INPROGRESS;
					}
					else if(E_SUB_FAILED_TO_SEND_PACK == ls8_result)
					{
						gst_deviceStatus.men_mqttSubErrorCode = E_SUB_FAILED_TO_SEND_PACK;
						len_retStatus = E_RET_FAILED;
					}
				}
			}
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
			len_retStatus = E_RET_TIMEOUT_ERROR;
		}
	}
	return len_retStatus;
}


/**************************************************************************
 * Function Name	:	mod_getCurrentTime
 *
 * Description   	:	This function used to get the current time
 *
 * Arguments     	:	uint8_t* - Pointer points to an array
 *
 * Return values 	:	uint8_t
 *
 ****************************************************************************/
uint8_t mod_getCurrentTime(uint8_t *lu8p_data)
{
	uint8_t lu8_ret = 0;

	if (NULL != lu8p_data)
	{
		memcpy(lu8p_data, gu8_dataTime, TIME_SIZE);
		lu8_ret = TIME_SIZE;
	}

	return lu8_ret;
}
/**************************************************************************
 * Function Name	:	mod_mqttSslMode
 *
 * Description   	:	This function Configure MQTT session into SSL mode.
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttSslMode(uint8_t *lu8p_param)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_CFG, lu8p_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_SUCCESS;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttSslConfgi
 *
 * Description   	:	This function Configure SSL
 *
 * Arguments     	:	uint8_t *
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttSslConfgi(uint8_t *lu8p_param)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_SSL_CFG, lu8p_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_SUCCESS;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttSslCertUpload
 *
 * Description   	:	This function uploads SSL certificates
 *
 * Arguments     	:	en_sslFile_t - SSL files
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttSslCertUpload(en_sslFile_t len_sslFile)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[50] = { 0 };
	static uint8_t *slu32_pos = NULL;
	static uint16_t lu16_totalFileSize = 0;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t *lu8p_saveptr = NULL;

	switch (sen_sslFileUpldState)
	{
		case E_SSL_UPLD_CMD_STATE:

			if(E_CA_CERT_FILE == len_sslFile)
			{
				slu32_pos = sgu8arr_caCert;
				lu16_totalFileSize = sizeof(sgu8arr_caCert);
				sprintf((char *) lu8arr_param, "%s,%d,60,1\r\n", MQTT_SSL_CA_FILENAME,
						lu16_totalFileSize);
			}
			else if(E_CC_CERT_FILE == len_sslFile)
			{
				slu32_pos = sgu8arr_ccCert;
				lu16_totalFileSize = sizeof(sgu8arr_ccCert);

				sprintf((char *) lu8arr_param, "%s,%d,60,1\r\n", MQTT_SSL_CC_FILENAME,
						lu16_totalFileSize);
			}
			else if(E_CK_CERT_FILE == len_sslFile)
			{
				slu32_pos = sgu8arr_ckCert;
				lu16_totalFileSize = sizeof(sgu8arr_ckCert);

				sprintf((char *) lu8arr_param, "%s,%d,60,1\r\n", MQTT_SSL_CK_FILENAME,
						lu16_totalFileSize);
			}

			len_retStatus = mod_sendCmdGetRsp(E_IDX_FILE_UPLOAD_CMD,
					(uint8_t *) lu8arr_param);

			if (E_RET_SUCCESS == len_retStatus)
			{
				lu8p_Ptr =
						(uint8_t *) strstr((const char *) gu8arr_respBuffer,
								(const char *) gcst_ATCmdTable[E_IDX_FILE_UPLOAD_CMD].mu8arr_respString);

				if (NULL != lu8p_Ptr)
				{
					memset(gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString, 0,
							sizeof(gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString));

					if (lu16_totalFileSize > 1024)
					{
						strncpy(
								(char *) gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString,
								(char *) slu32_pos, 1024);
//						gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString[1024] = '\0';
					}
					else
					{
						strncpy(
								(char *) gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString,
								(char *) slu32_pos, sizeof(sgu8arr_caCert));
//						gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString[sizeof(sgu8arr_caCert)+1] = '\0';
					}

					sen_sslFileUpldState = E_SSL_UPLD_FILE_CONTENT_STATE;
					len_retStatus = E_RET_INPROGRESS;
				}
				else
				{
					len_retStatus = E_RET_FAILED;
				}
			}
			else if(E_RET_CME_ERROR == len_retStatus)
			{
				if(407 == sgu16_cmeError)	//File already exists
				{
					len_retStatus = E_RET_SUCCESS;
				}
				if(421 == len_retStatus)	//Time out
				{
					len_retStatus = E_RET_INPROGRESS;
				}
			}
		break;

		case E_SSL_UPLD_FILE_CONTENT_STATE:
			len_retStatus = mod_sendCmdGetRsp(E_IDX_UPLOAD_FILE_CONTENT, NULL);
			if (E_RET_SUCCESS == len_retStatus)
			{
				lu8p_Ptr =
						(uint8_t *) strstr((const char *) gu8arr_respBuffer,
								(const char *) gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_otherRspString);

				if (NULL != lu8p_Ptr)
				{
					lu16_totalFileSize -= 1024;
					slu32_pos += 1024;

					memset(gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString, 0,
							sizeof(gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString));

					if(lu16_totalFileSize > 1024)
					{
						strncpy(
								(char *) gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString,
								(char *) slu32_pos, 1024);
					}
					else
					{
						strncpy(
								(char *) gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_cmdString,
								(char *) slu32_pos, lu16_totalFileSize);
					}
					memset(gu8arr_respBuffer, 0, sizeof(gu8arr_respBuffer));
					len_retStatus = E_RET_INPROGRESS;
				}

				lu8p_Ptr =
						(uint8_t *) strstr((const char *) gu8arr_respBuffer,
								(const char *) gcst_ATCmdTable[E_IDX_UPLOAD_FILE_CONTENT].mu8arr_respString);

				if (NULL != lu8p_Ptr)
				{
					sen_sslFileUpldState = E_SSL_UPLD_CMD_STATE;
					len_retStatus = E_RET_SUCCESS;
				}
			}
		break;

		default:
		break;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttSslCertDelete
 *
 * Description   	:	This function deletes SSL certificates
 *
 * Arguments     	:	uint8_t *
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttSslCertDelete(en_sslFile_t len_sslFile)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t lu8arr_param[50] = { 0 };

	if (E_CA_CERT_FILE == len_sslFile)
	{
		sprintf((char *) lu8arr_param, "%s\r\n", MQTT_SSL_CA_FILENAME);
	}
	else if (E_CC_CERT_FILE == len_sslFile)
	{
		sprintf((char *) lu8arr_param, "%s\r\n", MQTT_SSL_CC_FILENAME);
	}
	else if (E_CK_CERT_FILE == len_sslFile)
	{
		sprintf((char *) lu8arr_param, "%s\r\n", MQTT_SSL_CK_FILENAME);
	}

	len_retStatus = mod_sendCmdGetRsp(E_IDX_FILE_DELETE, (uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		len_retStatus = E_RET_SUCCESS;
	}
	else if(E_RET_INPROGRESS != len_retStatus)
	{
		len_retStatus = E_RET_FAILED;
	}

	return len_retStatus;
}
/**************************************************************************
 * Function Name	:	mod_mqttOpen
 *
 * Description   	:	This function MQTT Open
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttOpen(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t lu8arr_param[57] = { 0 };
	uint8_t *lu8p_Ptr = NULL;
	short ls_result = E_MQTT_OPN_NONE;

//	for(lu8_clientIdx = 0; lu8_clientIdx < 6; lu8_clientIdx++)
//	{
	sprintf((char *) lu8arr_param, "%d,%s", sgu8_mqttClientId, MQTT_OPEN_HOST_PORT);
	len_retStatus = mod_sendCmdGetRsp(E_IDX_MQTT_OPEN, lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) gcst_ATCmdTable[E_IDX_MQTT_OPEN].mu8arr_otherRspString);

		if (lu8p_Ptr != NULL)
		{
			lu8p_Ptr += 12;
			ls_result = atoi((char *) lu8p_Ptr);

			if (E_NW_OPENED_SUCCESSFULLY == ls_result)	//Network opened successfully
			{
				gst_deviceStatus.men_mqttOpenErrorCodes = E_NW_OPENED_SUCCESSFULLY;
				len_retStatus = E_RET_SUCCESS;
				//break;
			}
			else if(E_WRONG_PARAMETER == ls_result)	//Wrong parameter
			{
				/* set VCU DTC and change the return status */
				gst_deviceStatus.men_mqttOpenErrorCodes = E_WRONG_PARAMETER;
				len_retStatus = E_RET_FAILED;
			}
			else if(E_MQTT_ID_OCCUPIED == ls_result)	//MQTT identifier is occupied
			{
				gst_deviceStatus.men_mqttOpenErrorCodes = E_MQTT_ID_OCCUPIED;
				sgu8_mqttClientId++;
				if (sgu8_mqttClientId > 5)
				{
					len_retStatus = E_RET_FAILED;
					sgu8_mqttClientId = 0;
				}
				else
				{
					len_retStatus = E_RET_FAILED_TRY_DIFF_ID;
				}
			}
			else if(E_FAILED_TO_OPEN_NW == ls_result)	//-1 -> Failed to open network
			{
				gst_deviceStatus.men_mqttOpenErrorCodes = E_FAILED_TO_OPEN_NW;
				len_retStatus = E_RET_FAILED;
			}
			else if(E_FAILED_TO_ACTIVATE_PDP == ls_result)	//3  -> Failed to activate PDP
			{
				gst_deviceStatus.men_mqttOpenErrorCodes = E_FAILED_TO_ACTIVATE_PDP;
				len_retStatus = E_RET_FAILED;
			}
			else if(E_FAILED_TO_PARSE_DOMAIN_NAME == ls_result)	//Failed to parse domain name
			{
				gst_deviceStatus.men_mqttOpenErrorCodes = E_FAILED_TO_PARSE_DOMAIN_NAME;
				/* set VCU DTC and change the return status */
				len_retStatus = E_RET_FAILED;
			}
			else if(E_NW_CONNECTION_ERROR == ls_result)	//5  -> Network connection error
			{
				gst_deviceStatus.men_mqttOpenErrorCodes = E_NW_CONNECTION_ERROR;
				len_retStatus = E_RET_CONN_ERROR;
			}
			else	//other return values
			{
				len_retStatus = E_RET_INPROGRESS;
			}
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
//	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_mqttOpenConfig
 *
 * Description   	:	This function MQTT Open and config
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_mqttOpenConfig()
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	uint8_t lu8arr_param[34] = { 0 };
	switch (sen_openMqttState)
	{
		case E_MQTT_SSL_UPLD_CA_CERT_STATE:
			len_retStatus = mod_mqttSslCertUpload(E_CA_CERT_FILE);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_SSL_UPLD_CC_CERT_STATE;
			}
		break;

		case E_MQTT_SSL_UPLD_CC_CERT_STATE:
			len_retStatus = mod_mqttSslCertUpload(E_CC_CERT_FILE);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_SSL_UPLD_CK_CERT_STATE;
			}
		break;

		case E_MQTT_SSL_UPLD_CK_CERT_STATE:
			len_retStatus = mod_mqttSslCertUpload(E_CK_CERT_FILE);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_CA_CERT_STATE;
			}
		break;

		case E_MQTT_SSL_DELE_CA_CERT_STATE:
			len_retStatus = mod_mqttSslCertDelete(E_CA_CERT_FILE);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_SSL_DELE_CC_CERT_STATE;
			}
		break;

		case E_MQTT_SSL_DELE_CC_CERT_STATE:
			len_retStatus = mod_mqttSslCertDelete(E_CC_CERT_FILE);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_SSL_DELE_CK_CERT_STATE;
			}
		break;

		case E_MQTT_SSL_DELE_CK_CERT_STATE:
			len_retStatus = mod_mqttSslCertDelete(E_CK_CERT_FILE);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_SSL_UPLD_CA_CERT_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_CA_CERT_STATE:
			strcpy((char *) lu8arr_param, (const char *) CA_CERT_PATH);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_CC_CERT_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_CC_CERT_STATE:
			strcpy((char *) lu8arr_param, (const char *) CC_CERT_PATH);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_CK_CERT_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_CK_CERT_STATE:
			strcpy((char *) lu8arr_param, (const char *) CK_CERT_PATH);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_SSL_AUTH_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_SSL_AUTH_STATE:
			strcpy((char *) lu8arr_param, (const char *) SSL_AUTH);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_SSL_VER_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_SSL_VER_STATE:
			strcpy((char *) lu8arr_param, (const char *) SSL_VERSION);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_CIPHER_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_CIPHER_STATE:
			strcpy((char *) lu8arr_param, (const char *) SSL_CIPHER_SUITE);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_CFG_IGR_AUTH_STATE;
			}
		break;

		case E_MQTT_OPN_CFG_IGR_AUTH_STATE:
			strcpy((char *) lu8arr_param, (const char *) SSL_IGNORE_LOCAL_TIME);
			len_retStatus = mod_mqttSslConfgi(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				sgu8_mqttClientId = 0;
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_SSL_CFG_STATE;
			}
		break;

		case E_MQTT_OPN_SSL_CFG_STATE:
			sprintf((char *) lu8arr_param, (const char *) "\"SSL\",%d,1,2\r\n",
					sgu8_mqttClientId);
			len_retStatus = mod_mqttSslMode(lu8arr_param);
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_OPN_STATE;
			}
		break;

		case E_MQTT_OPN_STATE:
			len_retStatus = mod_mqttOpen();
			if (E_RET_SUCCESS == len_retStatus)
			{
				len_retStatus = E_RET_SUCCESS;
				sen_openMqttState = E_MQTT_OPN_CFG_CA_CERT_STATE;
			}
			else if (E_RET_FAILED_TRY_DIFF_ID == len_retStatus)
			{
				sen_openMqttState = E_MQTT_OPN_SSL_CFG_STATE;
			}
			else if (E_RET_FAILED == len_retStatus)
			{
				sen_openMqttState = E_MQTT_OPN_CFG_CA_CERT_STATE;
			}
			else if(E_RET_CONN_ERROR == len_retStatus)
			{
				len_retStatus = E_RET_INPROGRESS;
				sen_openMqttState = E_MQTT_SSL_DELE_CA_CERT_STATE;
			}
		break;

		default:
		break;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_gpsCfg
 *
 * Description   	:	This function used to configure the GPS
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_gpsCfg(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;
	uint8_t lu8arr_param[] = "\"outport\",\"none\"\r\n";

	len_retStatus = mod_sendCmdGetRsp(E_IDX_GPS_CFG, (uint8_t *) lu8arr_param);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		lu8p_Ptr = (uint8_t *) strstr((const char *) gu8arr_respBuffer,
				(const char *) gcst_ATCmdTable[E_IDX_GPS_CFG].mu8arr_respString);
		if(NULL != lu8p_Ptr)
		{

			len_retStatus = E_RET_SUCCESS;
		}
		else
		{
			len_retStatus = E_RET_FAILED;
		}
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_gpsEnable
 *
 * Description   	:	This function used to enable the GPS
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_gpsEnable(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_ENABLE_GNSS, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_SUCCESS;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_extractGpsData
 *
 * Description   	:	This function used to extract the GPS data
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
static en_responseRetCodes_t mod_extractGpsData(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCnt = 0;
	uint8_t *lu8p_Ptr = NULL;

	len_retStatus = mod_sendCmdGetRsp(E_IDX_GET_GPS_DATA, (uint8_t *) NEW_LINE);
	if (E_RET_SUCCESS == len_retStatus)
	{
		lsu8_retryCnt = 0;
		len_retStatus = E_RET_SUCCESS;
	}
	else if (E_RET_INPROGRESS != len_retStatus)
	{
		lsu8_retryCnt++;
		if (lsu8_retryCnt < AT_CMD_RETYR_MAX_CNT)
		{
			len_retStatus = E_RET_INPROGRESS;
		}
		else if (lsu8_retryCnt > AT_CMD_RETYR_MAX_CNT)
		{
			lsu8_retryCnt = 0;
		}
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_4gHandler
 *
 * Description   	:	This function has different states for initialization of
 * 						components, MQTT config, MQTT open, MQTT connect and it
 * 						also handles network recovery mechanisms.
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void mod_4gHandler(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lsu8_retryCount = 0;
//	mod_receiveRsp();	//read and saved received byte in global buffer

	if (gst_deviceStatus.mb_ismodemPwrDwn != true)
	{
		switch (sen_4gRunState)
		{
			case E_MOD_IDLE_STATE:
			break;

			case E_SET_URC_PORT_STATE:
				len_retStatus = mod_setUrcPort();
				if ((E_RET_SUCCESS == len_retStatus)
						|| (E_RET_INPROGRESS != len_retStatus))
				{
					mod_disable4gModule();
					gst_deviceStatus.mb_ismodemPwrDwn = true;
					mod_enable4gModule();
					sen_4gRunState = E_ECHO_OFF_STATE;
				}
			break;

			case E_ECHO_OFF_STATE:
				len_retStatus = mod_echoOff();
				if ((E_RET_SUCCESS == len_retStatus)
						|| (E_RET_INPROGRESS != len_retStatus))
				{
					sen_4gRunState = E_SET_FLOW_CTRL_STATE;
				}
			break;

			case E_SET_FLOW_CTRL_STATE:
				len_retStatus = mod_setFlowCtrl();
				if ((E_RET_SUCCESS == len_retStatus)
						|| (E_RET_INPROGRESS != len_retStatus))
				{
					sen_4gRunState = E_EXTRACT_MODULE_INFO_STATE;
				}
			break;

			case E_EXTRACT_MODULE_INFO_STATE:
				len_retStatus = mod_extractModInfo();
				if ((E_RET_SUCCESS == len_retStatus)
						|| (E_RET_INPROGRESS != len_retStatus))
				{
					sen_4gRunState = E_SIM_STATUS_STATE;
				}
			break;

			case E_SIM_STATUS_STATE:
				len_retStatus = mod_simStatus();
				if ((E_RET_SUCCESS == len_retStatus)
						|| (E_RET_INPROGRESS != len_retStatus))
				{
					sen_4gRunState = E_NETWORK_STATUS_STATE;
				}
			break;

			case E_NETWORK_STATUS_STATE:
				len_retStatus = mod_networkStatus();
				if (E_RET_SUCCESS == len_retStatus)
				{
					sen_4gRunState = E_SIGNAL_QUALITY_STATE;
				}
				else if (E_RET_FAILED == len_retStatus)
				{
					lsu8_retryCount++;
					gb_isMqttConnected = false;
					if (lsu8_retryCount >= 6)
					{
						lsu8_retryCount = 0;
						sen_4gRunState = E_MOD_RESET_STATE;
					}
					else
					{
						tm_set4gRunTimer(TIMER_5S);
						sen_4gRunState = E_MOD_WAIT_STATE;
					}
				}
			break;

			case E_SIGNAL_QUALITY_STATE:
				len_retStatus = mod_signalQuality();
				if (E_RET_SUCCESS == len_retStatus)
				{
					sen_4gRunState = E_EXTRACT_TIME_DATE_STATE;
				}
			break;

			case E_EXTRACT_TIME_DATE_STATE:
				len_retStatus = mod_extractDateTime();
				if (E_RET_SUCCESS == len_retStatus)
				{
					//SuperLooptime_End();
					//SuperLooptime_Start();
					set_RTC();
					sen_4gRunState = E_MQTT_OPEN_STATE;
				}
			break;

			case E_MQTT_OPEN_STATE:
				len_retStatus = mod_mqttOpenConfig();
				if (E_RET_SUCCESS == len_retStatus)
				{
					sen_4gRunState = E_MQTT_CONNECT_STATE;
				}
				else if (E_RET_INPROGRESS != len_retStatus)
				{
					sen_4gRunState = E_MOD_RESET_STATE;
				}
			break;

			case E_MQTT_CONNECT_STATE:
				len_retStatus = mod_mqttConnect();
				if (E_RET_SUCCESS == len_retStatus)
				{
//					gb_isMqttConnected = true;
//					sen_4gRunState = E_MOD_IDLE_STATE;
					sen_4gRunState = E_GPS_CFG_STATE;
				}
				else if(E_RET_FAILED_TRY_DIFF_ID == len_retStatus)
				{
					sgu8_mqttClientId++;
					if (sgu8_mqttClientId > 5)
					{
						sgu8_mqttClientId = 0;
					}
					sen_openMqttState = E_MQTT_OPN_SSL_CFG_STATE;
					sen_4gRunState = E_MQTT_OPEN_STATE;
				}
				else if (E_RET_CONN_CLOSED_ERROR == len_retStatus)
				{
					sen_4gRunState = E_MQTT_OPEN_STATE;
				}
				else if (E_RET_INPROGRESS != len_retStatus)
				{
					sen_4gRunState = E_MOD_RESET_STATE;
				}
			break;

			case E_GPS_CFG_STATE:
				len_retStatus = mod_gpsCfg();
				if (E_RET_SUCCESS == len_retStatus)
				{
					sen_4gRunState = E_GPS_ENABLE_STATE;
				}
			break;

			case E_GPS_ENABLE_STATE:
				len_retStatus = mod_gpsEnable();
				if (E_RET_SUCCESS == len_retStatus)
				{
					gb_isMqttConnected = true;
					sen_4gRunState = E_SET_URC_PORT_STATE;
				}
			break;

			case E_GET_GPS_DATA_STATE:

			break;

			case E_MOD_RESET_STATE:
				len_retStatus = mod_mqttDisableEnableFunctionality();
				if ((E_RET_SUCCESS == len_retStatus)
						|| (E_RET_INPROGRESS != len_retStatus))
				{
					sen_4gRunState = E_NETWORK_STATUS_STATE;
				}
			break;

			case E_MOD_WAIT_STATE:
				if (tm_get4gRunTimerValue() == 0)
				{
					sen_4gRunState = E_NETWORK_STATUS_STATE;
				}

			break;

			default:
			break;
		}
	}
}


/**************************************************************************
 * Function Name	:	mod_pub10sPackExtractGps
 *
 * Description   	:	This function used to send 10s packet and Extract GPS data
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
/*en_responseRetCodes_t mod_pub10sPackExtractGps(void)
 {
	static uint8_t lu8_retryCont = 0;
	char size[sizeof(int) * 8 + 1];
	const char *filename = "data.txt";

	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	switch (sen_10sPacektPubState) {
	case E_PREPARE_PACKET_STATE:
		 In this state prepare the send packet
		epoch_time();
		Process_4G_Event_Data();

		memset(Eventbuffer_4Gcomm, 0, 512);					//change to 512

		pb_ostream_t stream1;

		stream1 = pb_ostream_from_buffer(Eventbuffer_4Gcomm,
				sizeof(Eventbuffer_4Gcomm));
		pb_encode(&stream1, vcu_fleet_fleet_10_sec_fields, &TD1);
		writePacketsToFile(filename, Eventbuffer_4Gcomm,strlen(Eventbuffer_4Gcomm));
		sen_10sPacektPubState = E_PUB_10S_PACKET_STATE;
		break;

	case E_PUB_10S_PACKET_STATE:
		len_retStatus = mod_mqttPublishData(Eventbuffer_4Gcomm,
				strlen((char*) Eventbuffer_4Gcomm),(uint8_t*) MQTT_PUBLISH_TOPIC);

		if (E_RET_SUCCESS == len_retStatus) {
			lu8_retryCont = 0;
			//tm_set4gRunTimer(TIMEOUT_10S);
			//SuperLooptime_End();
			//SuperLooptime_Start();
			sen_10sPacektPubState = E_WAIT_POST_PUB_STATE;
		}
		else if(E_RET_CME_ERROR == len_retStatus)
		{
			if(sgu16_cmeError == 58)
			{
				lu8_retryCont = 0;
				gb_isMqttConnected = false;
				sen_10sPacektPubState = E_PREPARE_PACKET_STATE;
				sen_4gRunState = E_MOD_RESET_STATE;
			}
		}
		else if (E_RET_INPROGRESS != len_retStatus) {
			lu8_retryCont++;
			if (3 > lu8_retryCont) {
				lu8_retryCont = 0;
				gb_isMqttConnected = false;
				sen_10sPacektPubState = E_PREPARE_PACKET_STATE;
				sen_4gRunState = E_MQTT_OPEN_STATE;
			}
		}
		break;

	case E_WAIT_POST_PUB_STATE:
		 In this state wait for timeout and after timeout change the state
		RTC_GetTime(&current_time);
		if (current_time.seconds%10 == 0U) {
			sen_10sPacektPubState = E_PREPARE_PACKET_STATE;
			//print_struct_uart(&TD1);
		}

		if (current_time.seconds%3 == 0U)
		{
			Get_CurrentLocation();
		}
		break;

	default:
		break;
	}

	return len_retStatus;
}*/

en_responseRetCodes_t mod_pub10sPackExtractGps(void)
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	static uint8_t lu8_retryCont = 0;

	RTC_GetTime(&current_time);

	if ((current_time.seconds % 3 == 0U) && (sgb_flagGps == false) && (sgb_packetFlag == false))
	{
		Get_CurrentLocation();
		sgb_flagGps = true;
	}
	else if ((sgb_flagGps == true) && (current_time.seconds % 3) != 0U)
	{
		sgb_flagGps = false;
	}

	if ((current_time.seconds % 10 == 0U) && (sgb_flag4g == false))
	{
		epoch_time();
		Process_4G_Event_Data();
		memset(Eventbuffer_4Gcomm, 0, 512);
		pb_ostream_t stream1;
		stream1 = pb_ostream_from_buffer(Eventbuffer_4Gcomm, sizeof(Eventbuffer_4Gcomm));
		pb_encode(&stream1, vcu_fleet_fleet_10_sec_fields, &TD1);
		sgb_packetFlag = true;
		sgb_flag4g = true;
	}
	else if ((sgb_flag4g == true) && (current_time.seconds % 10 != 0U))
	{
		sgb_flag4g = false;
	}

	if (sgb_packetFlag == true)
	{
		len_retStatus = mod_mqttPublishData(Eventbuffer_4Gcomm,
				strlen((char*) Eventbuffer_4Gcomm),(uint8_t*) MQTT_PUBLISH_TOPIC);

		if (E_RET_SUCCESS == len_retStatus)
		{
			sgb_packetFlag = false;
		}
		else if (E_RET_INPROGRESS != len_retStatus)
		{
			lu8_retryCont++;
			if (3 > lu8_retryCont)
			{
				lu8_retryCont = 0;

				//write to SD card

				sgb_packetFlag = false;
				gb_isMqttConnected = false;
				sen_4gRunState = E_MQTT_OPEN_STATE;
			}
		}
	}
}
/**************************************************************************
 * Function Name	:	mod_3sGpsProcess
 *
 * Description   	:	This function used to get GPS data at every 3 sec
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
en_responseRetCodes_t mod_3sGpsProcess()
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	switch(sen_gpsProcessState)
	{
		case E_EXTRACT_GPS_DATA_STATE:
//			len_retStatus = mod_extractGpsData();
//			if (E_RET_SUCCESS == len_retStatus)
//			{
			Get_CurrentLocation();
			len_retStatus = E_RET_SUCCESS;
				/* GPS Parsing from gu8arr_respBuffer */
				tm_set3s4gRunTimer(TIMEOUT_3S);
				sen_gpsProcessState = E_WAIT_POST_EXTRACTION_STATE;
//			}
		break;

		case E_WAIT_POST_EXTRACTION_STATE:
			/* In this state wait for timeout and after timeout change the state */
			if (tm_get3s4gRunTimerValue() == 0)
			{
				sen_gpsProcessState = E_EXTRACT_GPS_DATA_STATE;
			}
		break;
		default:
			break;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	mod_4gProcess
 *
 * Description   	:	This function used to process the 4G module
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void mod_4gProcess()
{
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;
	switch(sen_4gProcessState)
	{
	case E_GPS_PROCESS_STATE:
		len_retStatus = mod_3sGpsProcess();
		if (E_RET_SUCCESS == len_retStatus) {
			sen_4gProcessState = E_10S_PACKET_PROCESS_STATE;
		}
		break;

	case E_10S_PACKET_PROCESS_STATE:
		len_retStatus = mod_pub10sPackExtractGps();
		if((E_RET_SUCCESS == len_retStatus) || (E_RET_IN_WAIT == len_retStatus)){
			sen_4gProcessState = E_GPS_PROCESS_STATE;
		}
		break;
	default:
		break;
	}
}
