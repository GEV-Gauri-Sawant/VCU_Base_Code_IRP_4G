/*
 * mdm_handler.h
 *
 *  Created on: 14-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#ifndef MDM_HANDLER_H_
#define MDM_HANDLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "comman.h"

#define CMD_BUFF_SIZE	50
#define SEND_CMD_BUFF_SIZE	1032
typedef enum
{
	//Power ON/OFF
	E_IDX_POWER_ON = 0,
	E_IDX_POWER_OFF,

	E_IDX_SET_URC_PRT,
	E_IDX_ECHO_OFF,
	E_IDX_HW_FLWCTRL,
	E_IDX_FEATCH_MOD_INFO,

	//SIM status
	E_IDX_ENABLE_SIM_DETECTION,
	E_IDX_ENABLE_SIM_STATUS,
	E_IDX_CHECK_SIM_STATUS,
	E_IDX_CPIN_CHECK,
	E_IDX_GET_IMEI,
	E_IDX_GET_CCID,
	E_IDX_GET_NUM,
	E_IDX_GET_OPERATOR,
	E_IDX_CREG,
	E_IDX_SIGNAL_QLTY,
	E_IDX_CCLK,

	//MQTT connection
	E_IDX_MQTT_CFG,
	E_IDX_MQTT_SSL_CFG,
	E_IDX_MQTT_OPEN,
	E_IDX_MQTT_CONNECT,
	E_IDX_MQTT_PUBLISH,
	E_IDX_MQTT_PUBLISH_DATA,
	E_IDX_MQTT_DISBALE_ENABLE_MODEM,
	E_IDX_MQTT_SUBSCRIBE,
	E_IDX_MQTT_UNSUBSCRIBE,
	E_IDX_FILE_UPLOAD_CMD,
	E_IDX_UPLOAD_FILE_CONTENT,
	E_IDX_FILE_DELETE,
	E_IDX_MQTT_DISCONNECT,
	E_IDX_MQTT_CLOSE,
	E_IDX_GPS_CFG,
	E_IDX_ENABLE_GNSS,
	E_IDX_GET_GPS_DATA,
	E_IDX_MAX
}en_ATCommandIdx_t;

typedef enum
{
	E_AT_CMD_IDLE_STATE = 0,
	E_AT_CMD_SEND_INPROG_STATE,
	E_AT_CMD_RECV_INPROG_STATE,
	E_AT_CMD_SEND_GET_RSP_STATE
}en_sendCmdGetRspState_t;

typedef enum
{
	E_MOD_IDLE_STATE = 0,
	E_SET_URC_PORT_STATE,
	E_ECHO_OFF_STATE,
	E_SET_FLOW_CTRL_STATE,
	E_EXTRACT_MODULE_INFO_STATE,
	E_SIM_STATUS_STATE,
	E_NETWORK_STATUS_STATE,
	E_SIGNAL_QUALITY_STATE,
	E_EXTRACT_TIME_DATE_STATE,
	E_MQTT_OPEN_STATE,
	E_MQTT_CLOSE_STATE,
	E_MQTT_CONNECT_STATE,
	E_MOD_RESET_STATE,
    E_GPS_CFG_STATE,
	E_GPS_ENABLE_STATE,
	E_GET_GPS_DATA_STATE,
	E_MOD_WAIT_STATE,
	E_MAX_4G_RUN_STATE
}en_4gModuleRunState_t;

typedef enum
{
	E_SIM_ENABLE_SIM_DETECTION_STATE = 0,
	E_SIM_ENABLE_SIM_STATUS_STATE,
	E_SIM_CHECK_SIM_STATUS_STATE,
	E_SIM_CPIN_CHECK_STATE,
	E_SIM_EXCTRACT_IMEI_STATE,
	E_SIM_EXCTRACT_CCID_STATE,
	E_SIM_EXTRACT_NUM_STATE,
	E_SIM_EXTRACT_OPERATOR_STATE,
	E_SIM_MAX_STATE
}en_simStatusState_t;

typedef enum
{
	E_MQTT_SSL_UPLD_CA_CERT_STATE = 0,
	E_MQTT_SSL_UPLD_CC_CERT_STATE,
	E_MQTT_SSL_UPLD_CK_CERT_STATE,
	E_MQTT_SSL_DELE_CA_CERT_STATE,
	E_MQTT_SSL_DELE_CC_CERT_STATE,
	E_MQTT_SSL_DELE_CK_CERT_STATE,
	E_MQTT_OPN_CFG_CA_CERT_STATE,
	E_MQTT_OPN_CFG_CC_CERT_STATE,
	E_MQTT_OPN_CFG_CK_CERT_STATE,
	E_MQTT_OPN_CFG_SSL_AUTH_STATE,
	E_MQTT_OPN_CFG_SSL_VER_STATE,
	E_MQTT_OPN_CFG_CIPHER_STATE,
	E_MQTT_OPN_CFG_IGR_AUTH_STATE,
	E_MQTT_OPN_SSL_CFG_STATE,
	E_MQTT_OPN_STATE,
	E_MQTT_MAX_STATE
}en_openMqttState_t;

typedef enum
{
	E_REG_NONE = 0,
	E_REGISTERED_NONE = 0x01,
	E_REGISTERED_HOME,
	E_NOT_REGISTERED,
	E_REGISTER_DENIED,
	E_UNKNOWN,
	E_REGISTERED_ROAMING
} en_cmdListRegistered_t;

typedef enum
{
	E_PUBLISH_CMD_STATE = 0,
	E_PUBLISH_DATA_STATE
}en_publishDataState_t;

typedef enum
{
	E_SSL_UPLD_CMD_STATE = 0,
	E_SSL_UPLD_FILE_CONTENT_STATE
}en_sslFileUploadState_t;

typedef enum
{
	E_CA_CERT_FILE = 0,
	E_CC_CERT_FILE,
	E_CK_CERT_FILE
}en_sslFile_t;

typedef enum
{
	E_RST_DISABLE_FUNCTION = 0,
	E_RST_ENALBE_FUNCTION,
	E_RST_WAIT_FUNCTION
}en_modemResetState_t;

typedef enum
{
	E_PREPARE_PACKET_STATE = 0,
	E_PUB_10S_PACKET_STATE,
	E_WAIT_POST_PUB_STATE
}en_10sPacektPubState_t;

typedef enum
{
	E_EXTRACT_GPS_DATA_STATE = 0,
	E_WAIT_POST_EXTRACTION_STATE
}en_gpsProcessState_t;

typedef enum
{
	E_GPS_PROCESS_STATE = 0,
	E_10S_PACKET_PROCESS_STATE
}en_4gProcessState_t;

typedef struct
{
	uint8_t mu8arr_cmdString[SEND_CMD_BUFF_SIZE];
	uint8_t mu8arr_respString[CMD_BUFF_SIZE];
	uint8_t mu8arr_otherRspString[CMD_BUFF_SIZE];
	uint8_t mu8arr_errString[CMD_BUFF_SIZE];
	uint32_t mu32_respTimeoutInMs;
}st_ATCmdTable_t;

typedef enum
{
	E_MQTT_OPN_NONE = -2,
	E_FAILED_TO_OPEN_NW = -1,
	E_NW_OPENED_SUCCESSFULLY = 0,
	E_WRONG_PARAMETER = 1,
	E_MQTT_ID_OCCUPIED = 2,
	E_FAILED_TO_ACTIVATE_PDP = 3,
	E_FAILED_TO_PARSE_DOMAIN_NAME = 4,
	E_NW_CONNECTION_ERROR = 5
}en_mqttOpenErrorCodes_t;

typedef enum
{
	E_MQTT_CLOSE_NONE = -2,
	E_MQTT_FAILED_TO_CLOSE_NW = -1,
	E_MQTT_NW_CLOSE_SUCCESS = 0
}en_mqttCloseErrorCodes_t;

typedef enum
{
	E_MQTT_DISCON_NONE = -2,
	E_MQTT_FAILED_TO_CLOSE_CONN= -1,
	E_MQTT_CONN_CLOSE_SUCCESS = 0
}en_mqttDisconErrorCodes_t;

typedef enum
{
	E_MQTT_CON_NONE = -1,
	E_ACK_RCVD_CONNECT_ACCEPT = 0,
	E_PACKET_RETRANSMISSION = 1,
	E_FAILED_TO_SEND_PACKET = 2,
	E_CON_REF_UNACC_PRO_VER = 3,
	E_CON_REF_ID_REJECT = 4,
	E_CON_REF_SERVER_UNAVAIL = 5,
	E_CON_REF_BAD_USR_PASS = 6,
	E_CON_REF_NOT_AUTH = 7,
	E_CON_UNKNOWN_ERROR = 8
}en_mqttConnectErrorCodes_t;

typedef enum
{
	E_PUB_NONE = -1,
	E_PUB_SUCCESS = 0,
	E_PUB_PACK_RETRAN = 1,
	E_PUB_FAILED_SEND_PACK = 2,
	E_PUB_UNKNOWN_ERROR = 3
}en_mqttPublishErrorCode_t;

typedef enum
{
	E_SUB_NONE = -1,
	E_SUB_ACK_RCVD_CONN_ACCEPT = 0,
	E_SUB_RETRAN = 1,
	E_SUB_FAILED_TO_SEND_PACK = 2,
	E_SUB_UNKNOWN_ERROR = 3
}en_mqttSubErrorCode_t;

typedef struct
{
	bool mb_ismodemPwrDwn;
	bool mb_isSimInserted;
	en_cmdListRegistered_t men_networkRegStatus;
	en_mqttOpenErrorCodes_t men_mqttOpenErrorCodes;
	en_mqttCloseErrorCodes_t men_mqttCloseErrorCodes;
	en_mqttConnectErrorCodes_t men_mqttConnectErrorCodes;
	en_mqttDisconErrorCodes_t men_mqttDisconErrorCodes;
	en_mqttPublishErrorCode_t men_mqttPublishErrorCode;
	en_mqttSubErrorCode_t men_mqttSubErrorCode;
}st_deviceStatus_t;

bool gb_isMqttConnected;

void mod_enable4gModule(void);
void mod_disable4gModule(void);
en_responseRetCodes_t mod_open4gModPort(void);
void mod_receiveRsp(void);
void mod_4gHandler(void);
en_responseRetCodes_t mod_pub10sPackExtractGps(void);
uint8_t mod_getModuleInfo(uint8_t *lu8p_data);
uint8_t mod_getIMEI(uint8_t *lu8p_data);
uint8_t mod_getCCID(uint8_t *lu8p_data);
uint8_t mod_getPhoneNum(uint8_t *lu8p_data);
uint8_t mod_getOperator(uint8_t *lu8p_data);
uint8_t mod_getCurrentTime(uint8_t *lu8_data);	//on demand
uint8_t mod_getSignalQuality(void);

#endif /* MDM_HANDLER_H_ */
