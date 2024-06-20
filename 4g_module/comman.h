/*
 * comman.h
 *
 *  Created on: 02-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#ifndef COMMAN_H_
#define COMMAN_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	E_RET_SUCCESS = 0,
	E_RET_FAILED_TRY_DIFF_ID,
	E_RET_FAILED,
	E_RET_RSP_ERROR,
	E_RET_INPROGRESS,
	E_RET_WRITE_ERROR,
	E_RET_TIMEOUT_ERROR,
	E_RET_TIMER_ERROR,
	E_RET_TIMER_ID_ZERO_ERROR,
	E_RET_SIM_NOT_DETECTED,
	E_RET_CONN_CLOSED_ERROR,
	E_RET_CME_ERROR,
	E_RET_CMS_ERROR,
	E_RET_CONN_ERROR,
	E_RET_IN_WAIT,
	E_RET_MAX
}en_responseRetCodes_t;

#endif /* COMMAN_H_ */
