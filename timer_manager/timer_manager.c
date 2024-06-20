/*
 * timer_manager.c
 *
 *  Created on: 03-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#include "timer_manager.h"
static volatile uint32_t timerCount = 0;
static volatile uint32_t gu32_resetCounter = 0;
static volatile uint32_t gu32_4gCounter = 0;
static volatile uint32_t gu32_10s4gCounter = 0;
static volatile uint32_t gu32_3s4gCounter = 0;
static volatile uint32_t gu32_responseCount = 0;
static uint32_t timerId;

/**************************************************************************
 * Function Name	:	tm_sysTickCallback
 *
 * Description   	:	This is a system tick call back function
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void tm_sysTickCallback(void)
{
	timerCount++;

	if(gu32_responseCount > 0)
	{
		gu32_responseCount--;
	}
	if(gu32_resetCounter > 0)
	{
		gu32_resetCounter--;
	}

	if(gu32_4gCounter > 0)
	{
		gu32_4gCounter--;
	}

	if(gu32_10s4gCounter > 0)
	{
		gu32_10s4gCounter--;
	}

	if(gu32_3s4gCounter > 0)
	{
		gu32_3s4gCounter--;
	}
}

/**************************************************************************
 * Function Name	:	tm_setTimerCount
 *
 * Description   	:	This function used to sets the timer count value
 *
 * Arguments     	:	uint32_t - timer value
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
en_responseRetCodes_t tm_setTimerCount(uint32_t timerValue)
{
	en_responseRetCodes_t len_retStatus;
	//uint32_t tempTimerValue = timerValue * TM_1MS_TIMER_VAL;

	timerId = (uint32_t) SYSTIMER_CreateTimer(timerValue,
			SYSTIMER_MODE_PERIODIC, (void*) tm_sysTickCallback, NULL);

	if (0U != timerId)
	{
		len_retStatus = E_RET_SUCCESS;
	}
	else
	{
		len_retStatus = E_RET_TIMER_ERROR;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	tm_startTimer
 *
 * Description   	:	This function used to starts the timer
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
en_responseRetCodes_t tm_startTimer()
{
	en_responseRetCodes_t len_retStatus;
	SYSTIMER_STATUS_t timerStatus;

	if (timerId != 0)
	{
		timerStatus = SYSTIMER_StartTimer(timerId);
		if (SYSTIMER_STATUS_SUCCESS == timerStatus)
		{
			len_retStatus = E_RET_SUCCESS;
		}
		else
		{
			len_retStatus = E_RET_TIMER_ERROR;
		}
	}
	else
	{
		len_retStatus = E_RET_TIMER_ID_ZERO_ERROR;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	tm_stopTimer
 *
 * Description   	:	This function used to stop the timer
 *
 * Arguments     	:	void
 *
 * Return values 	:	en_responseRetCodes_t - return status
 *
 ****************************************************************************/
en_responseRetCodes_t tm_stopTimer()
{
	en_responseRetCodes_t len_retStatus;
	SYSTIMER_STATUS_t timerStatus;

	if (timerId != 0)
	{
		timerStatus = SYSTIMER_StopTimer(timerId);
		if (SYSTIMER_STATUS_SUCCESS == timerStatus)
		{
			len_retStatus = E_RET_SUCCESS;
		}
		else
		{
			len_retStatus = E_RET_TIMER_ERROR;
		}
	}
	else
	{
		len_retStatus = E_RET_TIMER_ID_ZERO_ERROR;
	}

	return len_retStatus;
}

/**************************************************************************
 * Function Name	:	tm_getTimerCount
 *
 * Description   	:	This function used to get the timer count value
 *
 * Arguments     	:	void
 *
 * Return values 	:	uint32_t - timer count value
 *
 ****************************************************************************/
uint32_t tm_getTimerCount()
{
	return timerCount;
}

/**************************************************************************
 * Function Name	:	tm_clearTimerCount
 *
 * Description   	:	This function used to clear the timer count
 *
 * Arguments     	:	void
 *
 * Return values 	:	void
 *
 ****************************************************************************/
void tm_clearTimerCount()
{
	timerCount = 0;
}

void tm_setResetTimer(uint32_t lu32_timeInMs)
{
	gu32_resetCounter = lu32_timeInMs;
}

uint32_t tm_getResetTimerValue()
{
	return gu32_resetCounter;
}

void tm_set10s4gRunTimer(uint32_t lu32_timeInMs)
{
	gu32_10s4gCounter = lu32_timeInMs;
}

uint32_t tm_get10s4gRunTimerValue()
{
	return gu32_10s4gCounter;
}

void tm_set3s4gRunTimer(uint32_t lu32_timeInMs)
{
	gu32_3s4gCounter = lu32_timeInMs;
}

uint32_t tm_get3s4gRunTimerValue()
{
	return gu32_3s4gCounter;
}

void tm_set4gRunTimer(uint32_t lu32_timeInMs)
{
	gu32_3s4gCounter = lu32_timeInMs;
}

uint32_t tm_get4gRunTimerValue()
{
	return gu32_3s4gCounter;
}

void tm_setResponseTime(uint32_t lu32_timeInMs)
{
	gu32_responseCount = lu32_timeInMs;
}

uint32_t tm_getResponseTimeValue()
{
	return gu32_responseCount;
}
void tm_clearResponseTime()
{
	gu32_responseCount = 0;
}
