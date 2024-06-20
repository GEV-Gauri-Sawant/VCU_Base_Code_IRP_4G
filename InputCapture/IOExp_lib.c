/*
 * IOExp_lib.c
 *
 *  Created on: 2023 Feb 13 17:39:06
 *  Author: Gensol
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include<xmc_i2c.h>
#include<stdio.h>

//#define I2C_SLAVE_ADDRESS 0x42
static uint8_t I2C_SLAVE_ADDRESS;

#define INPUT_REG_PORT0 0x00
#define INPUT_REG_PORT1	0x01
#define OUTPUT_REG_PORT0 0x02
#define OUTPUT_REG_PORT1 0x03
#define CONFIG_REG_PORT0 0x06
#define CONFIG_REG_PORT1 0x07

#define PIN_LOW  false
#define PIN_HIGH true

/* This test case configures Port 0 of IO Expander as output
 * and Port 1 as input and check the signals transmission from Port 0 on Port 1 */
void IOExp_Test_FullPORT(void)
{
	bool send_start = true, send_stop = true;
	uint8_t data_ptr[20] = {0}, data_RxPtr[20] = {0}, CMD;
	uint32_t data_count;
	I2C_MASTER_STATUS_t I2C_status = I2C_MASTER_STATUS_FAILURE;
	bool test_result = false;
	uint8_t pass_count=0;

	/*********************************************TEST port 0 output, port 1 input ************************************************/
	/* Configure port 0 */
	CMD = CONFIG_REG_PORT0;
	data_ptr[0] = CMD;
	data_ptr[1] = 0x00; // data to port 0
	data_ptr[2] = 0xFF; // data to port 1
	data_count = 3;

	/* Set Port 0 as output and port 1 as input */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	//	/* Configure port 1 */
	//	CMD = CONFIG_REG_PORT1;
	//	data_ptr[0] = CMD;
	//	data_ptr[1] = 0xFF;
	//
	//	/* Set Port 1 as input */
	//	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, data_ptr, data_count, send_stop);

	//make connections port 0 to port 1 pins correspondingly

	/* port 0 pins set high */
	CMD = OUTPUT_REG_PORT0;
	data_ptr[0] = CMD;
	data_ptr[1] = 0xFF; // data to port 0
	data_count = 2;

	/* Write port 0 all pins high */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);


	/* Read port 1 configuration */
	CMD = INPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_count = 1;
	send_stop = false;

	/* Read port 1 */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	send_start = true;
	send_stop = true;

	/* Read Port 1 pins */
	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_RxPtr[0], data_count, send_stop, true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	if(data_RxPtr[0] == 0xFF)
	{
		test_result = true;
		pass_count++;
	}

	/* set alternate pins of Port 0 as high and low */
	/* P0.0 high, P0.1 low, P0.2 high, P0.3 low, etc.. */

	/* port 0 pins set high */
	CMD = OUTPUT_REG_PORT0;
	data_ptr[0] = CMD;
	data_ptr[1] = 0xAA; // data to port 0
	data_count = 2;
	send_start = true;

	/* Write port 0 alternate pins high */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	/* Read port 1 configuration */
	CMD = INPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_count = 1;
	send_stop = false;

	/* Read port 1 */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	send_start = true;
	send_stop = true;

	/* Read Port 1 pins */
	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_RxPtr[0], data_count, send_stop, true);

	if(data_RxPtr[0] == 0xAA)
	{
		test_result = true;
		pass_count++;
	}

	/* set alternate pins of Port 0 as high and low */
	/* P0.0 high, P0.1 low, P0.2 high, P0.3 low, etc.. */

	/* port 0 pins set high */
	CMD = OUTPUT_REG_PORT0;
	data_ptr[0] = CMD;
	data_ptr[1] = 0x55; // data to port 0
	data_count = 2;
	send_start = true;

	/* Write port 0 alternate pins high */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	/* Read port 1 configuration */
	CMD = INPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_count = 1;
	send_stop = false;

	/* Read port 1 */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	send_start = true;
	send_stop = true;

	/* Read Port 1 pins */
	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_RxPtr[0], data_count, send_stop, true);

	if(data_RxPtr[0] == 0x55)
	{
		test_result = true;
		pass_count++;
	}


	/********************************************* END TEST 1 ************************************************/

	/*********************************************TEST port 0 output, port 1 input ************************************************/
	/* Configure port 1 */
	CMD = CONFIG_REG_PORT1;
	data_ptr[0] = CMD;
	data_ptr[1] = 0x00; // data to port 1
	data_ptr[2] = 0xFF; // data to port 0
	data_count = 3;

	/* Set Port 1 as output and port 0 as input */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	//	/* Configure port 0 */
	//	CMD = CONFIG_REG_PORT0;
	//	data_ptr[0] = CMD;
	//	data_ptr[1] = 0xFF;
	//
	//	/* Set Port 0 as input */
	//	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, data_ptr, data_count, send_stop);

	//make connections port 0 to port 1 pins correspondingly

	/* port 1 pins set high */
	CMD = OUTPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_ptr[1] = 0xFF; // data to port 0
	data_count = 2;

	/* Write port 1 all pins high */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);


	/* Read port 0 configuration */
	CMD = INPUT_REG_PORT0;
	data_ptr[0] = CMD;
	data_count = 1;
	send_stop = false;

	/* Read port 0 */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	send_start = true;
	send_stop = true;

	/* Read Port 1 pins */
	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_RxPtr[0], data_count, send_stop, true);

	if(data_RxPtr[0] == 0xFF)
	{
		test_result = true;
		pass_count++;
	}

	/* set alternate pins of Port 0 as high and low */
	/* P0.0 high, P0.1 low, P0.2 high, P0.3 low, etc.. */

	/* port 1 pins set high */
	CMD = OUTPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_ptr[1] = 0xAA; // data to port 0
	data_count = 2;
	send_start = true;

	/* Write port 1 alternate pins high */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	/* Read port 0 configuration */
	CMD = INPUT_REG_PORT0;
	data_ptr[0] = CMD;
	data_count = 1;
	send_stop = false;

	/* Read port 0 */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	send_start = true;
	send_stop = true;

	/* Read Port 0 pins */
	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_RxPtr[0], data_count, send_stop, true);

	if(data_RxPtr[0] == 0xAA)
	{
		test_result = true;
		pass_count++;
	}

	/* set alternate pins of Port 0 as high and low */
	/* P0.0 high, P0.1 low, P0.2 high, P0.3 low, etc.. */

	/* port 1 pins set high */
	CMD = OUTPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_ptr[1] = 0x55; // data to port 1
	data_count = 2;
	send_start = true;

	/* Write port 1 alternate pins high */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	/* Read port 0 configuration */
	CMD = INPUT_REG_PORT1;
	data_ptr[0] = CMD;
	data_count = 1;
	send_stop = false;

	/* Read port 0 */
	I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_ptr[0], data_count, send_stop);

	send_start = true;
	send_stop = true;

	/* Read Port 0 pins */
	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, I2C_SLAVE_ADDRESS, &data_RxPtr[0], data_count, send_stop, true);

	if(data_RxPtr[0] == 0x55)
	{
		test_result = true;
		pass_count++;
	}

	if(pass_count == 6)
	{
		//test passed
		while(1);
	}
	else
	{
		//test failed
		while(1);
	}


	/********************************************* END TEST 2 ************************************************/
}

/* Configures pin input and output for corresponding ports as provided in port0 and port1 parameter */
/* IOExp_address is the device address, e.g. 0x40 */
void IOExp_Configure(I2C_MASTER_t *handle, uint8_t IOExp_address, uint8_t port0, uint8_t port1)
{
	bool send_start = true, send_stop = true;
	uint8_t data_ptr[20] = {0}, data_RxPtr[20] = {0}, CMD;
	uint32_t data_count;
	I2C_MASTER_STATUS_t I2C_status = I2C_MASTER_STATUS_FAILURE;
	bool test_result = false;
	uint8_t pass_count=0;

	/*********************************************TEST port 0 output, port 1 input ************************************************/
	/* Configure port 0 */
	CMD = CONFIG_REG_PORT0;
	data_ptr[0] = CMD;
	data_ptr[1] = port0; // data to port 0
	data_ptr[2] = port1; // data to port 1
	data_count = 3;

	for(int i = 0; i < 0xffff; i++);
	/* Set Port 0 as output and port 1 as input */
	I2C_MASTER_Transmit(handle, send_start, IOExp_address/*I2C_SLAVE_ADDRESS*/, &data_ptr[0], data_count, send_stop);
}

/* Internal function to set a pin high or low for specified IO expander
 * return: true,  operation is successful
 * 		   false, operation not successful */
bool IOExp_SetPIN_UPDATE(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port, uint8_t pin, bool pin_level)
{
	bool send_start = true, send_stop = true;
	uint8_t data_ptr[20] = {0}, data_Rx[2] = {0}, CMD;
	uint32_t data_count;
	I2C_MASTER_STATUS_t I2C_status = I2C_MASTER_STATUS_FAILURE;

	if(0 == port)
	{
		/* Read port 0 configuration */
		CMD = OUTPUT_REG_PORT0;
	}
	else //if(1 == port)
	{
		/* Read port 1 configuration */
		CMD = OUTPUT_REG_PORT1;
	}

	data_ptr[0] = CMD;
	data_count = 1;

	send_stop = false;
	/* Read port 0 */
	I2C_status = I2C_MASTER_Transmit(handle, send_start, IOExp_Address, &data_ptr[0], data_count, send_stop);
	if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
	{
		//send_start = true;
		send_start = true;
		send_stop = true;

		/* Read Port 1 pins */
	//	I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, IOExp_Address, &data_Rx[0], data_count, send_stop, true);
		//data_count = 2;
		I2C_status = I2C_MASTER_Receive(handle, send_start, IOExp_Address, &data_ptr[1], data_count, send_stop, true);
		if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
		{
			if(PIN_HIGH == pin_level)
			{
				/* Update output register value */
				data_ptr[1] |= /*data_Rx[0] |*/ (1 << pin);
			}
			else
			{
				/* Update output register value */
				data_ptr[1] &= /*data_Rx[0] &*/ (~(1 << pin));
			}

			data_count = 2;
			send_start = true;

			for(int i= 0; i < 0xffff; i++);
			/* update pin */
			I2C_status = I2C_MASTER_Transmit(handle, send_start, IOExp_Address, &data_ptr[0], data_count, send_stop);
			/* data is expected to be successfully written at this point */
		}
	}

	if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
		return true;
	else
		return false;
}

/* Function to set a pin high for specified IO expander
 * return: true,  operation is successful
 * 		   false, operation not successful */
bool IOExp_SetPIN_HIGH(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port, uint8_t pin)
{
	return IOExp_SetPIN_UPDATE(handle, IOExp_Address, port, pin, PIN_HIGH);
}

/* Function to set a pin low for specified IO expander
 * return: true,  operation is successful
 * 		   false, operation not successful */
bool IOExp_SetPIN_LOW(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port, uint8_t pin)
{
	return IOExp_SetPIN_UPDATE(handle, IOExp_Address, port, pin, PIN_LOW);
}

/* Function to read a pin level for specified IO expander
 * return: true,  pin is HIGH
 * 		   false, pin is LOW */
//
//bool IOExp_ReadPIN_LEVEL(uint8_t IOExp_Address, uint8_t port, uint8_t pin)
//{
//	bool send_start = true, send_stop = true;
//	uint8_t data_ptr[20] = {0}, data_Rx[2] = {0}, CMD;
//	uint32_t data_count;
//	I2C_MASTER_STATUS_t I2C_status = I2C_MASTER_STATUS_FAILURE;
//
//	if(0 == port)
//	{
//		/* Read port 0 configuration */
//		CMD = INPUT_REG_PORT0;
//	}
//	else //if(1 == port)
//	{
//		/* Read port 1 configuration */
//		CMD = INPUT_REG_PORT1;
//	}
//
//	data_ptr[0] = CMD;
//	data_count = 1;
//
//	send_stop = false;
//	/* Read port */
//	I2C_status = I2C_MASTER_Transmit(&I2C_MASTER_0, send_start, IOExp_Address, &data_ptr[0], data_count, send_stop);
//	if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
//	{
//		send_start = true;
//		send_stop = true;
//
//		/* Read Port pins */
//		I2C_status = I2C_MASTER_Receive(&I2C_MASTER_0, send_start, IOExp_Address, &data_Rx[0], data_count, send_stop, true);
//
//		if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
//		{
//			return (data_Rx[0] >> pin) & 0x01;
//		}
//	}
//}


uint8_t* IOExp_ReadPIN_LEVEL(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port)
{
	bool send_start = true, send_stop = true;
	uint8_t data_ptr[20] = {0}, /*data_Rx[2] = {0},*/ CMD;
	static uint8_t data_Rx[2] = {0, 0};
	uint32_t data_count;
	I2C_MASTER_STATUS_t I2C_status = I2C_MASTER_STATUS_FAILURE;

	if(0 == port)
	{
		/* Read port 0 configuration */
		CMD = INPUT_REG_PORT0;
	}
	else //if(1 == port)
	{
		/* Read port 1 configuration */
		CMD = INPUT_REG_PORT1;
	}

	data_ptr[0] = CMD;
	data_count = 1;

	send_stop = true;
	/* Read port */
	//for(int i = 0; i < 0xffff; i++);
	I2C_status = I2C_MASTER_Transmit(handle, send_start, IOExp_Address, &data_ptr[0], data_count, send_stop);
	if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
	{
		send_start = true;
		send_stop = true;
		for(int i = 0; i < 0xffff; i++);
		/* Read Port pins */
		I2C_status = I2C_MASTER_Receive(handle, send_start, IOExp_Address, data_Rx, 2/*data_count*/, send_stop, true);

		if(I2C_MASTER_STATUS_SUCCESS == I2C_status)
		{
			return (data_Rx);
		}
	}
}
