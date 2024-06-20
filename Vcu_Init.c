/*
 * Vcu_Init.c
 *
 *  Created on: 30-Jun-2023
 *      Author: Suchit Sawant
 */
#include "DAVE.h"
#include "Vcu_Init.h"
#include "InputCapture/IOExp_lib.h"
#include "stdlib.h"
#include "string.h"

#define UART_DEBUG 0
#define UART_DEBUG4G 1

#define IO_EXP_IC_25 25
#define IO_EXP_IC_38 38
#define IO_EXP_IC_48 48

#define PORT0 0x00
#define PORT1 0x01

#define PIN0 0X00
#define PIN1 0X01
#define PIN2 0X02
#define PIN3 0X03
#define PIN4 0X04
#define PIN5 0X05
#define PIN6 0X06
#define PIN7 0X07


/* IO_EXP U25 */
Io_Exp_PinMap_t AUX_EFUSE_2_OUT_D = {IO_EXP_IC_25, PORT0, PIN6};
Io_Exp_PinMap_t HV_BATT_FAN_PWR_OUT_D = {IO_EXP_IC_25, PORT1, PIN3};
Io_Exp_PinMap_t ORVM_OPEN_OUT_D = {IO_EXP_IC_25, PORT1, PIN4};
Io_Exp_PinMap_t ORVM_FOLD_OUT_D = {IO_EXP_IC_25, PORT1, PIN6};
Io_Exp_PinMap_t ORVM_PWR_OUT_D = {IO_EXP_IC_25, PORT1, PIN7};


/* IO_EXP U38 */
Io_Exp_PinMap_t AC_BLOWER_SPEED1_OUT_D = {IO_EXP_IC_38, PORT0, PIN0};
Io_Exp_PinMap_t AC_BLOWER_SPEED2_OUT_D = {IO_EXP_IC_38, PORT0, PIN1};
Io_Exp_PinMap_t AC_BLOWER_SPEED3_OUT_D = {IO_EXP_IC_38, PORT0, PIN2};
Io_Exp_PinMap_t AC_SOL_PWR_OUT_D = {IO_EXP_IC_38, PORT0, PIN3};

Io_Exp_PinMap_t AUX_EFUSE_3_OUT_D = {IO_EXP_IC_38, PORT1, PIN1};
Io_Exp_PinMap_t AUX_EFUSE_4_OUT_D = {IO_EXP_IC_38, PORT1, PIN2};
Io_Exp_PinMap_t AUX_EFUSE_5_OUT_D = {IO_EXP_IC_38, PORT1, PIN3};
Io_Exp_PinMap_t AUX_MOSFET_OUT3_D = {IO_EXP_IC_38, PORT1, PIN4};
Io_Exp_PinMap_t SUNROOF_PWR_OUT_D = {IO_EXP_IC_38, PORT1, PIN5};
Io_Exp_PinMap_t HV_CHARGER_EN_OUT_D = {IO_EXP_IC_38, PORT1, PIN6};
Io_Exp_PinMap_t AC_COMPRESSOR_OUT_D = {IO_EXP_IC_38, PORT1, PIN7};


/* IO_EXP U48 */
Io_Exp_PinMap_t ELEC_HANDBRAKE_PWR_OUT_D = {IO_EXP_IC_48, PORT0, PIN2};


//#if UART_DEBUG
void uart_debugg(uint8_t uart_buff[])
{

#if UART_DEBUG
	int index = 0;
		/*while(UART_Transmit(&UART_0, uart_buff, strlen(uart_buff)) == UART_STATUS_BUSY);
		while((UART_Transmit(&UART_0, "\n", 1) == UART_STATUS_BUSY));
		while((UART_Transmit(&UART_0, "\r", 1) == UART_STATUS_BUSY));*/

	//while(uart_buff)
	UART_Transmit(&UART_0, uart_buff, strlen(uart_buff));
	//while(UART_0.runtime->tx_busy);
	(UART_Transmit(&UART_0, "\n", 1));
	//while(UART_0.runtime->tx_busy);
	(UART_Transmit(&UART_0, "\r", 1));
	//while(UART_0.runtime->tx_busy);


	//@ref UART_GetProtocolStatus
	/* while(index < strlen(uart_buff))
	  {
	            UART_TransmitWord(&UART_0,uart_buff[index]);
	            index++;

	            //Wait for transmit buffer interrupt to fill it again with remaining data
	            while((UART_GetTXFIFOStatus(&UART_0) & XMC_USIC_CH_TXFIFO_EVENT_STANDARD) == 0);
	            UART_ClearTXFIFOStatus(&UART_0, XMC_USIC_CH_TXFIFO_EVENT_STANDARD);
	   }*/
#endif
}
//#endif

//#if UART_DEBUG
void uart_debugg4g(uint8_t uart_buff[])
{

#if UART_DEBUG4G
	int index = 0;
		/*while(UART_Transmit(&UART_0, uart_buff, strlen(uart_buff)) == UART_STATUS_BUSY);
		while((UART_Transmit(&UART_0, "\n", 1) == UART_STATUS_BUSY));
		while((UART_Transmit(&UART_0, "\r", 1) == UART_STATUS_BUSY));*/

	//while(uart_buff)
	UART_Transmit(&UART_0, uart_buff, strlen(uart_buff));
	//while(UART_0.runtime->tx_busy);
	(UART_Transmit(&UART_0, "\n", 1));
	//while(UART_0.runtime->tx_busy);
	(UART_Transmit(&UART_0, "\r", 1));
	//while(UART_0.runtime->tx_busy);


	//@ref UART_GetProtocolStatus
	/* while(index < strlen(uart_buff))
	  {
	            UART_TransmitWord(&UART_0,uart_buff[index]);
	            index++;

	            //Wait for transmit buffer interrupt to fill it again with remaining data
	            while((UART_GetTXFIFOStatus(&UART_0) & XMC_USIC_CH_TXFIFO_EVENT_STANDARD) == 0);
	            UART_ClearTXFIFOStatus(&UART_0, XMC_USIC_CH_TXFIFO_EVENT_STANDARD);
	   }*/
#endif
}
//#endif


void Io_Exp_Init(void)
{
	/* 0 set as output, 1 as input */
	/* Initially output is high hence make 0 */

	uint8_t Io_Exp_address = 0x42, set_port0_pin_as_out_or_input = 0xbf, set_port1_pin_as_out_or_input = 0x27, port0 = 0x00, port1 = 0x01, pin_value = 0x06;

	/* U25 I2C_0*/
	IOExp_Configure(&I2C_MASTER_0, Io_Exp_address, set_port0_pin_as_out_or_input , set_port1_pin_as_out_or_input);
	IOExp_SetPIN_LOW(&I2C_MASTER_0,Io_Exp_address, port0, pin_value);
	IOExp_SetPIN_LOW(&I2C_MASTER_0,Io_Exp_address, port1, 0x03);
	IOExp_SetPIN_LOW(&I2C_MASTER_0,Io_Exp_address, port1, 0x04);
	IOExp_SetPIN_LOW(&I2C_MASTER_0,Io_Exp_address, port1, 0x06);
	IOExp_SetPIN_LOW(&I2C_MASTER_0,Io_Exp_address, port1, 0x07);
	//IOExp_SetPIN_HIGH(&I2C_MASTER_0,Io_Exp_address, port0, pin_value);

	/* U38 I2C_1 */
	Io_Exp_address = 0x40;
	set_port0_pin_as_out_or_input = 0xf0;
	set_port1_pin_as_out_or_input = 0x01;
	IOExp_Configure(&I2C_MASTER_1, Io_Exp_address, set_port0_pin_as_out_or_input , set_port1_pin_as_out_or_input);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port0, 0);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port0, 1);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port0, 2);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port0, 3);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x01);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x02);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x03);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x04);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x05);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x06);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port1, 0x07);

	/* U48 I2C_1 */
	Io_Exp_address = 0x42;
	set_port0_pin_as_out_or_input =0XF7;
	set_port1_pin_as_out_or_input = 0xFF;
	IOExp_Configure(&I2C_MASTER_1, Io_Exp_address, set_port0_pin_as_out_or_input , set_port1_pin_as_out_or_input);
	IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, port0, 3);

}


void digital_io_setoutputlow(Io_Exp_PinMap_t *IO_EXP_PINName_handler)
{
	uint8_t Io_Exp_address;

	if((IO_EXP_PINName_handler ->IC_no == 24) || (IO_EXP_PINName_handler ->IC_no == 25))
	{
		Io_Exp_address = 0x40;

		if(IO_EXP_PINName_handler ->IC_no == 25)
			Io_Exp_address = 0x42;

		IOExp_SetPIN_LOW(&I2C_MASTER_0, Io_Exp_address, IO_EXP_PINName_handler ->port, IO_EXP_PINName_handler ->pin);
	}
	else if((IO_EXP_PINName_handler ->IC_no == 38) || (IO_EXP_PINName_handler ->IC_no == 48))
	{
		Io_Exp_address = 0x40;

		if(IO_EXP_PINName_handler ->IC_no == 48)
			Io_Exp_address = 0x42;

		IOExp_SetPIN_LOW(&I2C_MASTER_1, Io_Exp_address, IO_EXP_PINName_handler ->port, IO_EXP_PINName_handler ->pin);
	}

}


void digital_io_setoutputhigh(Io_Exp_PinMap_t *IO_EXP_PINName_handler)
{
	uint8_t Io_Exp_address;

	if((IO_EXP_PINName_handler ->IC_no == 24) || (IO_EXP_PINName_handler ->IC_no == 25))
	{
		Io_Exp_address = 0x40;

		if(IO_EXP_PINName_handler ->IC_no == 25)
			Io_Exp_address = 0x42;

		IOExp_SetPIN_HIGH(&I2C_MASTER_0, Io_Exp_address, IO_EXP_PINName_handler ->port, IO_EXP_PINName_handler ->pin);
	}
	else if((IO_EXP_PINName_handler ->IC_no == 38) || (IO_EXP_PINName_handler ->IC_no == 48))
	{
		Io_Exp_address = 0x40;

		if(IO_EXP_PINName_handler ->IC_no == 48)
			Io_Exp_address = 0x42;

		IOExp_SetPIN_HIGH(&I2C_MASTER_1, Io_Exp_address, IO_EXP_PINName_handler ->port, IO_EXP_PINName_handler ->pin);
	}

}

void Delay(uint32_t delay_ms)
{
	uint32_t delay_cnt;

	TIMER_ClearEvent(&TIMER_0);

   delay_cnt = delay_ms * 100000;//TIMER_DELAY_MUL_FACTOR;

   TIMER_SetTimeInterval(&TIMER_0,delay_cnt);

   TIMER_Start(&TIMER_0);

   while(!TIMER_GetInterruptStatus(&TIMER_0));

   TIMER_Stop(&TIMER_0);

}

void SuperLooptime_Start(void)
{
	TIMER_STATUS_t timer_status;

	timer_status = TIMER_Start(&TIMER_1);
	if(timer_status == TIMER_STATUS_SUCCESS)
		Start_Time = TIMER_GetTime(&TIMER_1);
}

void SuperLooptime_End(void)
{
	TIMER_STATUS_t timer_status;
	SuperLoop_Time = 0;

	timer_status = TIMER_Stop(&TIMER_1);
	if(timer_status == TIMER_STATUS_SUCCESS)
	{
		End_Time = (uint32_t)TIMER_GetTime(&TIMER_1);
		SuperLoop_Time = (End_Time - Start_Time);
		SuperLoop_Time_usec = (End_Time - Start_Time) / 100.0;
		SuperLoop_Time_msec = (End_Time - Start_Time) / 100000.0;
		SuperLoop_Time_sec = (End_Time - Start_Time) / 100000000.0;

		//itoa();
	}

	TIMER_Clear(&TIMER_1);
}
