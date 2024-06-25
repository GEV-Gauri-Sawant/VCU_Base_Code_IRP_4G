/*
 * Vcu_Init.h
 *
 *  Created on: 30-Jun-2023
 *      Author: Suchit Sawant
 */

#ifndef VCU_INIT_H_
#define VCU_INIT_H_



#endif /* VCU_INIT_H_ */


typedef struct
{
	uint8_t IC_no;
	uint8_t port;
	uint8_t pin;
}Io_Exp_PinMap_t;


void uart_debugg(uint8_t uart_buff[]);
void Delay(uint32_t delay_ms);
void Io_Exp_Init(void);
void digital_io_setoutputlow(Io_Exp_PinMap_t *IO_EXP_PINName_handler);
void digital_io_setoutputhigh(Io_Exp_PinMap_t *IO_EXP_PINName_handler);

void SuperLooptime_Start(void);
void SuperLooptime_End(void);

/* IO_EXP U25 */
Io_Exp_PinMap_t AUX_EFUSE_2_OUT_D;
Io_Exp_PinMap_t HV_BATT_FAN_PWR_OUT;
Io_Exp_PinMap_t ORVM_OPEN_OUT_D;
Io_Exp_PinMap_t ORVM_FOLD_OUT_D;
Io_Exp_PinMap_t ORVM_PWR_OUT_D;

/* IO_EXP U38 */
Io_Exp_PinMap_t AC_BLOWER_SPEED1_OUT_D;
Io_Exp_PinMap_t AC_BLOWER_SPEED2_OUT_D;
Io_Exp_PinMap_t AC_BLOWER_SPEED3_OUT_D;
Io_Exp_PinMap_t AC_SOL_PWR_OUT_D;

Io_Exp_PinMap_t AUX_EFUSE_3_OUT_D;
Io_Exp_PinMap_t AUX_EFUSE_4_OUT_D;
Io_Exp_PinMap_t AUX_EFUSE_5_OUT_D;
Io_Exp_PinMap_t AUX_MOSFET_OUT3_D;
Io_Exp_PinMap_t SUNROOF_PWR_OUT_D;
Io_Exp_PinMap_t HV_CHARGER_EN_OUT_D;
Io_Exp_PinMap_t AC_COMPRESSOR_OUT_D;

/* IO_EXP U38 */
Io_Exp_PinMap_t ELEC_HANDBRAKE_PWR_OUT_D;

double SuperLoop_Time, SuperLoop_Time_usec, SuperLoop_Time_msec, SuperLoop_Time_sec;
uint32_t End_Time, Start_Time;

uint8_t CState, PreState;

//used for 12V battery charging during parked mode.
volatile uint16_t seconds_elapsed;
