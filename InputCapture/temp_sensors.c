/*
 * temp_sensors.c

 *
 *  Created on: 14-Jul-2023
 *      Author: Suchit Sawant
 */
#include <math.h>
#include "DAVE.h"
#include "Vcu_config.h"

#define U18_address 0X94
#define U6_address 0x90
#define U9_address 0x92

float ambient_temp = 0;
float cabin_temp = 0;

//not working
//enum U18_channels {
//	MOTOR_TEMP_BYTE = 0x9C,//0b10011100,
//	CABIN_TEMP_BYTE = 0xDC,//0b11011100,
//	MC_TEMP_BYTE = 0xAC,//0b10101100,
//	BATTERY_TEMP_BYTE = 0xEC//0b11101100
//};
float calculate_temperatre(uint16_t adc_raw)
{
	float nominal_in_k = 298.15;
	uint16_t resolution = 4096;
	float v_supply = 3.3;
	uint16_t nomial_r = 10000;
	uint16_t beta = 3435;
	float v_ref = 2.5;

	float vout = adc_raw * (v_ref/resolution); //25 in c = 298.15 in K
	float rt = nomial_r * ((v_supply / vout) - 1);
	float t_in_kel = (1 / nominal_in_k) + (1 / (beta * (log(nomial_r/rt))));
	t_in_kel = 1 / t_in_kel;
	float t_in_cel = t_in_kel - 273.15;
	cabin_temp = t_in_cel;
	return cabin_temp;
}

void U18_read_temp(void)
{
	uart_debugg("in temp");
	U18_MotorTemp_read();
	U18_CabinTemp_read();

//	ambient_temp = U18_read_channel(MOTOR_TEMP_BYTE); //test this //not working
	//U18_McTemp_read();
	//U18_BatteryTemp_read();
	//U18_throttle_read();
	uart_debugg("exit temp");
}

//not working
//float U18_read_channel(uint8_t ch_no)
//{
//	unsigned int SERIESRESISTOR = 10000, NOMINAL_RESISTANCE = 10000, BCOEFFICIENT = 3950, NOMINAL_TEMPERATURE = 25;
//	bool start = true, stop = false, ack = false;
//	float Resistance = 0, steinhart = 0, temp = 0;
//	uint8_t rx_buff[2];
//	uint16_t rx = 0;
//
//	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &ch_no, 1, stop);
//	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_1));
//
//	stop = true;
//
//	I2C_MASTER_Receive(&I2C_MASTER_1, start, U18_address, rx_buff, 2, stop, ack);
//	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_1));
//
//	rx = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
//	rx &= 0x0fff;
//
//	Resistance = ((float)4095.0/(float)rx) - 1;
//	Resistance = ((float)10000.0/(float)Resistance);
//
//	Resistance /= (float)2;
//
//	steinhart = (float)Resistance / (float)10000.0; // (R/Ro)
//	steinhart = (float)log(steinhart); // ln(R/Ro)
//	steinhart /= (float)3950.0;
//	steinhart += (float)1.0 / (NOMINAL_TEMPERATURE + (float)273.15); // + (1/To)
//
//	steinhart = (float)1.0 / steinhart;
//	temp =	steinhart -= (float)273.15;
//
//	return temp;
//}

void U18_48v_read(void)
{
	bool start = true, stop = false, ack = false;
	uint8_t rx_buff[2];
	uint8_t command_byte= 0x0f;
	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_1));
	start = false;
	I2C_MASTER_Receive(&I2C_MASTER_1, start, U18_address, rx_buff, 2, stop, ack);

	//rx_buff &= 0x0fff;
}
void U18_MotorTemp_read(void)
{
	/*bool start = true, stop = true;
	uint8_t command_byte= 0x1f;
	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U38_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));*/

	bool start = true, stop = 0, ack = true;
	float ans = 0, Resistance = 0;
	unsigned int SERIESRESISTOR = 10000, NOMINAL_RESISTANCE = 10000, BCOEFFICIENT = 3950, NOMINAL_TEMPERATURE = 25;
	uint8_t command_byte= 0x9f, rx_buff[2] = {0};
	uint16_t rx = 0;

	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_1));

	stop = true;

	I2C_MASTER_Receive(&I2C_MASTER_1, start, U18_address, rx_buff, 2, stop, ack);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_1));

	rx = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
	rx &= 0x0fff;

	Resistance = ((float)4095.0/(float)rx) - 1;
	Resistance = ((float)10000.0/(float)Resistance);

	Resistance /= (float)2;

	float steinhart;

	steinhart = (float)Resistance / (float)10000.0; // (R/Ro)
	steinhart = (float)log(steinhart); // ln(R/Ro)
	steinhart /= (float)3950.0;
	steinhart += (float)1.0 / (NOMINAL_TEMPERATURE + (float)273.15); // + (1/To)

	steinhart = (float)1.0 / steinhart;
	ambient_temp =	steinhart -= (float)273.15;
}

void U18_CabinTemp_read(void)
{
	bool start = true, stop = 0, ack = true;
	float ans = 0, Resistance = 0;
	unsigned int SERIESRESISTOR = 10000, NOMINAL_RESISTANCE = 10000, BCOEFFICIENT = 3950, NOMINAL_TEMPERATURE = 25;
	uint8_t command_byte= 0xdc, rx_buff[2] = {0};
	uint16_t rx = 0;

	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_1));

	stop = true;

	I2C_MASTER_Receive(&I2C_MASTER_1, start, U18_address, rx_buff, 2, stop, ack);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_1));

	rx = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
	rx &= 0x0fff;

	cabin_temp = calculate_temperatre(rx);

	Resistance = ((float)4095.0/(float)rx) - 1;
	Resistance = ((float)10000.0/(float)Resistance);

	Resistance /= (float)2;

	float steinhart;

	steinhart = (float)Resistance / (float)10000.0; // (R/Ro)
	steinhart = (float)log(steinhart); // ln(R/Ro)
	steinhart /= (float)3950.0;
	steinhart += (float)1.0 / (NOMINAL_TEMPERATURE + (float)273.15); // + (1/To)

	steinhart = (float)1.0 / steinhart;
	steinhart -= (float)273.15;
	cabin_temp = steinhart;
}

void U18_McTemp_read(void)
{
	bool start = true, stop = 0, ack = true;
	float ans = 0, Resistance = 0;
	unsigned int SERIESRESISTOR = 10000, NOMINAL_RESISTANCE = 10000, BCOEFFICIENT = 3950, NOMINAL_TEMPERATURE = 25;
	uint8_t command_byte= 0xac, rx_buff[2] = {0};
	uint16_t rx = 0;

	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_1));

	stop = true;

	I2C_MASTER_Receive(&I2C_MASTER_1, start, U18_address, rx_buff, 2, stop, ack);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_1));

	rx = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
	rx &= 0x0fff;

	Resistance = ((float)4095.0/(float)rx) - 1;
	Resistance = ((float)10000.0/(float)Resistance);

	Resistance /= (float)2;

	float steinhart;

	steinhart = (float)Resistance / (float)10000.0; // (R/Ro)
	steinhart = (float)log(steinhart); // ln(R/Ro)
	steinhart /= (float)3950.0;
	steinhart += (float)1.0 / (NOMINAL_TEMPERATURE + (float)273.15); // + (1/To)

	steinhart = (float)1.0 / steinhart;
	steinhart -= (float)273.15;

}

void U18_BatteryTemp_read(void)
{

	bool start = true, stop = 0, ack = true;
	float ans = 0, Resistance = 0;
	unsigned int SERIESRESISTOR = 10000, NOMINAL_RESISTANCE = 10000, BCOEFFICIENT = 3950, NOMINAL_TEMPERATURE = 25;
	uint8_t command_byte= 0xec, rx_buff[2] = {0};
	uint16_t rx = 0;

	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_1));

	stop = true;

	I2C_MASTER_Receive(&I2C_MASTER_1, start, U18_address, rx_buff, 2, stop, ack);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_1));

	rx = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
	rx &= 0x0fff;

	Resistance = ((float)4095.0/(float)rx) - 1;
	Resistance = ((float)10000.0/(float)Resistance);

	Resistance /= (float)2;

	float steinhart;

	steinhart = (float)Resistance / (float)10000.0; // (R/Ro)
	steinhart = (float)log(steinhart); // ln(R/Ro)
	steinhart /= (float)3950.0;
	steinhart += (float)1.0 / (NOMINAL_TEMPERATURE + (float)273.15); // + (1/To)

	steinhart = (float)1.0 / steinhart;
	steinhart -= (float)273.15;

}

void U18_throttle_read(void)
{
	bool start = true, stop = true;
	uint8_t command_byte= 0x3f;
	I2C_MASTER_Transmit(&I2C_MASTER_1, start, U18_address, &command_byte, 1, stop);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
}

void U6_On_board_temp_read(void)
{
/*	I2C_MASTER_Transmit(&I2C_MASTER_0, start, U6_address, &command_byte, 1, stop);
		while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));*/

}

void U9_On_board_temp_read(void)
{

}
