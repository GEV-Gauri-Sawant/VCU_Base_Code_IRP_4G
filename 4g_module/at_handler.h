/*
 * at_handler.h
 *
 *  Created on: 02-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#ifndef AT_HANDLER_H_
#define AT_HANDLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "comman.h"

typedef enum
{
	E_SUCCESS = 0,
	E_FAIL
}en_returnCodes_t;

typedef struct
{
	uint8_t mu8_command[1024];			/* It is used to store the command. */
	uint8_t mu8_successResp[1024];		/* It is used to store the success response of the command. */
	uint8_t	mu8_errorResp[24];			/* It is used to store the error response of the command. */
	uint8_t mu8_otherResp[48];			/* It is used to store the other response of the command. */
	uint32_t mu32_timeoutInMs;			/* It is used to store wait time after command send. */
	uint8_t mu8_maxRespRtryCnt;			/* It is used to store the maximum retry count of the response. */
	uint8_t mu8_maxNtfnRtryCnt;			/* It is used to store the maximum retry count of the notification. */
	uint16_t mu16_parseDateOffset;		/* It is used to store the offset for response buffer */
	bool mb_ntfnExpFlag;				/* It is 1 when notification will received otherwise it is 0. */
	bool mb_stopOnErrorFlag;			/* It is 1 when error or retry over then do not send remaining command, 0 then send remaining command. */
} st_commandTableList_t;

en_responseRetCodes_t at_initInterface(void);
en_responseRetCodes_t at_openPort(void);
uint8_t at_readPort(void);
uint8_t at_writePort(uint8_t *lu8_data, uint16_t lu16_buffLen);
bool at_isRxBuffEmpty();
void at_clearBuff();
#endif /* AT_HANDLER_H_ */
