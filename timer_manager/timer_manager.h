/*
 * timer_manager.h
 *
 *  Created on: 03-Apr-2024
 *      Author: Kirankumar_Chincholi
 */

#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include "SYSTIMER/systimer.h"
#include "4g_module/comman.h"

#define TM_1S_TIMER_VAL 	1000000U
#define TM_1MS_TIMER_VAL 	1000U

#define TIMER_300MS			300
#define TIMER_1S			1000
#define TIMER_5S			5000

en_responseRetCodes_t tm_setTimerCount(uint32_t timerValue);
uint32_t tm_getTimerCount(void);
void tm_clearTimerCount(void);
void tm_setResetTimer(uint32_t lu32_timeInMs);
uint32_t tm_getResetTimerValue();
void tm_set4gRunTimer(uint32_t lu32_timeInMs);
uint32_t tm_get4gRunTimerValue();
void tm_set10s4gRunTimer(uint32_t lu32_timeInMs);
uint32_t tm_get10s4gRunTimerValue();
void tm_set3s4gRunTimer(uint32_t lu32_timeInMs);
uint32_t tm_get3s4gRunTimerValue();
void tm_setResponseTime(uint32_t lu32_timeInMs);
uint32_t tm_getResponseTimeValue();
en_responseRetCodes_t tm_startTimer(void);
en_responseRetCodes_t tm_stopTimer(void);
void tm_clearResponseTime(void);
#endif /* TIMER_MANAGER_H_ */
