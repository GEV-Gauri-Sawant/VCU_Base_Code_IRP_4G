/*
 * at_handler.c
 *
 *  Created on: 02-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#include "at_handler.h"
#include "DAVE.h"

/**************************************************************************
 * Function Name	:	initInterface
 *
 * Description   	:	This function initializes and opens the UART interface and
 * 						initializes requires states and initial things to start the tasks.
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - Return status
 *
 ****************************************************************************/
en_responseRetCodes_t at_initInterface(void)
{
	DAVE_STATUS_t init_status;
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	/**  Initialization of UART APP instance UART_0 */
	init_status = (DAVE_STATUS_t) UART_Init(&UART_0);
	if (DAVE_STATUS_SUCCESS == init_status)
	{
		len_retStatus = E_RET_SUCCESS;
	}
	else
	{
		len_retStatus = E_RET_FAILED;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	at_openPort
 *
 * Description   	:	This function initializes and opens the UART interface.
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - Return status
 *
 ****************************************************************************/
en_responseRetCodes_t at_openPort(void)
{
	DAVE_STATUS_t init_status;
	en_responseRetCodes_t len_retStatus = E_RET_INPROGRESS;

	/**  Initialization of UART APP instance UART_0 */
	init_status = (DAVE_STATUS_t) UART_Init(&UART_0);
	if (DAVE_STATUS_SUCCESS == init_status)
	{
		len_retStatus = E_RET_SUCCESS;
	}
	else
	{
		len_retStatus = E_RET_FAILED;
	}
	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	at_readPort
 *
 * Description   	:	This function reads data from UART
 *
 * Arguments     	:	void
 *
 * Return values 	:	uint8_t
 *
 ****************************************************************************/
uint8_t at_readPort()
{
	return UART_GetReceivedWord(&UART_0);
}

/**************************************************************************
 * Function Name	:	at_isRxBuffEmpty
 *
 * Description   	:	This function return received buffer empty status
 *
 * Arguments     	:	void
 *
 * Return values 	:	bool
 *
 ****************************************************************************/
bool at_isRxBuffEmpty()
{
	return XMC_USIC_CH_RXFIFO_IsEmpty(UART_0.channel);
}

void at_clearBuff()
{
	XMC_USIC_CH_RXFIFO_Flush(UART_0.channel);
}
/**************************************************************************
 * Function Name	:	at_writePort
 *
 * Description   	:	This function write data to UART
 *
 * Arguments     	:	uint8_t *lu8_data - send buffer
 *						uint16_t lu16_buffLen - buffer length
 *
 * Return values 	:	uint8_t
 *
 ****************************************************************************/
uint8_t at_writePort(uint8_t *lu8_data, uint16_t lu16_buffLen)
{
	UART_STATUS_t ret_stat = UART_STATUS_BUSY;
	ret_stat = UART_Transmit(&UART_0, lu8_data, lu16_buffLen);
	uint8_t lu8_ret = 0;
	if (UART_STATUS_SUCCESS == ret_stat)
	{
		lu8_ret = E_SUCCESS;
	}
	else if (UART_STATUS_FAILURE == ret_stat)
	{
		lu8_ret = E_FAIL;
	}
	return lu8_ret;
}
