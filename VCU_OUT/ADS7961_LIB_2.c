#include "DAVE.h"
#include "ADS7961_LIB_2.h"
#include <math.h>

#define ADC_GAIN		151.1
#define RSHUNT			0.0005
#define VREF			2.5
#define RESOLUTION		256
#define TOTAL_SAMPLES	50
#define ATTENUATION 	0.1175

float DROPPED_IN_12V = 0;
uint8_t flag = false;
uint8_t adc2_array_counter = 0;
uint8_t adc3_array_counter = 0;

///**************************** THINGS TO UPDATE FIRST *********************************

void DROPPED_IN_12_volt(void)
{
//		float adc_vout = ((ADS3_avg_receive_data[12] / 50)-2) * (2.5 /256);
	uint32_t avg_receive_data = 0;
	for(uint8_t cnt = 0; cnt < TOTAL_SAMPLES; cnt++)
	{
		avg_receive_data += ADS3_receive_data[12][cnt];
	}
	float adc_vout = (avg_receive_data / TOTAL_SAMPLES) * (VREF /RESOLUTION);
	DROPPED_IN_12V = adc_vout / ATTENUATION;
}

void convert_raw_data_into_current(void)
{
	memset(ADS2_avg_receive_data, 0, sizeof(ADS2_avg_receive_data));
	memset(ADS3_avg_receive_data, 0, sizeof(ADS3_avg_receive_data));

	for(int i = 0; i < 16; i++)
	{
		for(uint8_t cnt = 0; cnt < TOTAL_SAMPLES; cnt++)
		{
			ADS2_avg_receive_data[i] += ADS2_receive_data[i][cnt];
			ADS3_avg_receive_data[i] += ADS3_receive_data[i][cnt];
		}

		float adc_vout = (ADS2_avg_receive_data[i] / TOTAL_SAMPLES) * (VREF /RESOLUTION);
		adc2_current[i] = (adc_vout / ADC_GAIN) / RSHUNT;

		adc_vout = 0;
		adc_vout = (ADS3_avg_receive_data[i] / TOTAL_SAMPLES) * (VREF /RESOLUTION);
		adc3_current[i] = (adc_vout / ADC_GAIN) / RSHUNT;
	}
}

void SPI_ADC_ReadAllData(uint8_t ADCMode)
{
	if(ADC_AUTO1 == ADCMode)
	{
		//change operating mode to AUTO1
	}
	else if(ADC_AUTO2 == ADCMode)
	{
		//Add ADC1 after hardware changes
		SPI_ADS7961_AUTO2_MODE(ADS3_Port2,ADS3_Pin);//pass Ads cs port and pin
		SPI_ADS7961_AUTO2_MODE(ADS2_Port5 ,ADS2_Pin);//pass Ads cs port and pin
	}
	else //manual mode
	{
		//configure manual mode
		SPI_ADC_MANUAL_MODE();
	}

	//do not call this right now you can call this when it is in use.
	convert_raw_data_into_current();
}

void SPI_ADC_MANUAL_MODE(void)
{
	//ADC_Read_AllChannel(ADS2_Port5 ,ADS2_Pin);//pass Ads cs port and pin
	//ADC_Read_AllChannel(ADS3_Port2,ADS3_Pin);//pass Ads cs port and pin
	ADC_Read_by_Channel(ADS3_Port2,ADS3_Pin,12);//pass Ads cs port , pin and channel
}

uint16_t ADS7861_MANUAL_MODE_PKT(uint16_t channel) {

	ADS7961Frame_t transmitPkt;
	transmitPkt.Bit.operating_mode=1;
	transmitPkt.Bit.enable_D0_to_D6=0;
	transmitPkt.Bit.channel_selection=channel;
	transmitPkt.Bit.input_range=0;
	transmitPkt.Bit.device_operation=0;
	transmitPkt.Bit.output_mode=0;
	transmitPkt.Bit.GPIO_Output=0;
	return  transmitPkt.F_Data;
}

void ADC_Read_AllChannel(uint8_t temp_port_num, const uint8_t pin_number)
{
	XMC_GPIO_PORT_t * temp_ptr;

	if (temp_port_num == 5) {
		temp_ptr = XMC_GPIO_PORT5;
		for (int re_as_loop = 0; re_as_loop < 16; re_as_loop++) {
			ADS2_avg_receive_data[re_as_loop] = 0;
		}

	} else if (temp_port_num == 2) {
		temp_ptr = XMC_GPIO_PORT2;
		for (int re_as_loop = 0; re_as_loop < 16; re_as_loop++) {
			ADS3_avg_receive_data[re_as_loop] = 0;
		}

	} else if (temp_port_num == 3) {

	}

	for (int i = 0; i < TOTAL_SAMPLES; i++) {
		for (int j = 0; j < 16; j++) {
			int pkt = ADS7861_MANUAL_MODE_PKT(j);
			uint8_t SendData[2] = { (pkt >> 8), (pkt & 0xFF) };
			uint8_t ReadData[2];
			XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			for (int i = 0; i > 16; i++)
				;
			SPI_MASTER_Transmit(&SPI_MASTER_0, SendData, 2);
			for (int i = 0; i > 9; i++)
				;
			XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			;
			for (int i = 0; i > 2; i++)
				;
			XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			for (int i = 0; i > 9; i++)
				;
			SPI_MASTER_Receive(&SPI_MASTER_0, ReadData, 2);
			for (int i = 0; i > 2; i++)
				;
			XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			;
			for (int i = 0; i > 9; i++)
				;
			XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			for (int i = 0; i > 9; i++)
				;
			SPI_MASTER_Receive(&SPI_MASTER_0, ReadData, 2);

			XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			;

			if (temp_port_num == 5) {
//				ADS2_receive_data[j] = ((ReadData[0] & 0x0F) << 4) | ((ReadData[1] & 0xF0) >> 4);
//				ADS2_recive_channel[j] = ((ReadData[0] & 0xF0) >> 4);

//				ADS2_avg_receive_data[j] += ADS2_receive_data[j];
			} else if (temp_port_num == 2) {
//				ADS3_receive_data[j] = ((ReadData[0] & 0x0F) << 4) | ((ReadData[1] & 0xF0) >> 4);
//				ADS3_recive_channel[j] = ((ReadData[0] & 0xF0) >> 4);

//				ADS3_avg_receive_data[j] += ADS3_receive_data[j];
			}
		}
	}
}

void SPI_ADS7961_AUTO2_Init(uint8_t temp_port_num ,uint8_t pin_number)
{
	XMC_GPIO_PORT_t * temp_ptr;

	if(temp_port_num == 5)
	{
		temp_ptr = XMC_GPIO_PORT5;
		memset(ADS2_avg_receive_data, 0, sizeof(ADS2_avg_receive_data));
	}
	else if(temp_port_num == 2)
	{
		temp_ptr = XMC_GPIO_PORT2;
		memset(ADS3_avg_receive_data, 0, sizeof(ADS3_avg_receive_data));
	}

	uint8_t SendData[2] = { 0x3C, 0x00 }; //{MODE_CONTROL_AUTO2 >> 8, MODE_CONTROL_AUTO2 && 0xFF};
	uint8_t SendData1[2];

	if(temp_port_num == 5)
	{
		SendData1[0] = 0x93;   //{PROGRAM_REGISTER_AUTO2 >>8, PROGRAM_REGISTER_AUTO2 && 0xFF};
		SendData1[1] =  0xC0;
	}
	else if(temp_port_num == 2)
	{
		SendData1[0] = 0x93;   //{PROGRAM_REGISTER_AUTO2 >>8, PROGRAM_REGISTER_AUTO2 && 0xFF};
		SendData1[1] =  0x00;
	}
	uint8_t SendData2[2] = {0x00,0x00} ; //{CONTINUE_MODE_PREVIOUS >>8, CONTINUE_MODE_PREVIOUS && 0xFF};

	XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *)temp_ptr,pin_number);

	XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *)temp_ptr,pin_number);
	for (int i = 0; i > 9; i++);
	SPI_MASTER_Transmit(&SPI_MASTER_0, SendData1, 2);
	XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *)temp_ptr,pin_number);

    XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *)temp_ptr,pin_number);
	for (int i = 0; i > 9; i++);
	SPI_MASTER_Transmit(&SPI_MASTER_0, SendData, 2);
	for (int i = 0; i > 9; i++);
	XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *)temp_ptr,pin_number);

	XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *)temp_ptr,pin_number);
	for (int i = 0; i > 9; i++);
	// for CONTINUE MODE PREVIOUS
	SPI_MASTER_Transmit(&SPI_MASTER_0, SendData2, 2);
	for (int i = 0; i > 9; i++);

	XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *)temp_ptr,pin_number);
}

//
void SPI_ADS7961_AUTO2_MODE(uint8_t temp_port_num, uint8_t pin_number)
{
	uint8_t loop = 16;
	uint8_t ReadData[2];
//	if(flag==false)
//	{
	SPI_ADS7961_AUTO2_Init(temp_port_num, pin_number);
	flag = true;
//	}

	XMC_GPIO_PORT_t * temp_ptr;

	if (temp_port_num == 5)
	{
		temp_ptr = XMC_GPIO_PORT5;
	}
	else if (temp_port_num == 2)
	{
		temp_ptr = XMC_GPIO_PORT2;
		loop = 13;
	}

	if(adc2_array_counter > 49)
	{
		adc2_array_counter = 0;
	}

	if(adc3_array_counter > 49)
	{
		adc3_array_counter = 0;
	}

	//take 5 samples in one cycle
	for (int i = 0; i < 5; i++)
	{
		for (uint8_t channel_count = 0; channel_count < loop; channel_count++)
		{
			XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			//for (int i = 0; i > 9; i++);

			XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
			for (int i = 0; i > 2; i++);
			SPI_MASTER_Receive(&SPI_MASTER_0, ReadData, 2);
			for (int i = 0; i > 2; i++);
			XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);

			if (temp_port_num == 5)
			{
				ADS2_receive_data[channel_count][adc2_array_counter] = ((ReadData[0] & 0x0F) << 4) | ((ReadData[1] & 0xF0) >> 4);
//				ADS2_recive_channel[channel_count] = ((ReadData[0] & 0xF0) >> 4); //uncomment channel for debugging

//				ADS2_avg_receive_data[channel_count] += ADS2_receive_data[channel_count];
			}
			else if (temp_port_num == 2)
			{
				ADS3_receive_data[channel_count][adc3_array_counter] = ((ReadData[0] & 0x0F) << 4) | ((ReadData[1] & 0xF0) >> 4);
//				ADS3_recive_channel[channel_count] = ((ReadData[0] & 0xF0) >> 4); //uncomment channel for debugging

//				ADS3_avg_receive_data[channel_count] += ADS3_receive_data[channel_count];
			}
		}

		if (temp_port_num == 5)
		{
			adc2_array_counter++;
		}
		else if (temp_port_num == 2)
		{
			adc3_array_counter++;
		}
	}
}

void ADC_Read_by_Channel(uint8_t temp_port_num, uint8_t pin_number, uint8_t channel)
{
	XMC_GPIO_PORT_t * temp_ptr;

	if (temp_port_num == 5)
	{
		temp_ptr = XMC_GPIO_PORT2;
		ADS2_avg_receive_data[channel] = 0;
	}
	else if (temp_port_num == 2)
	{
		temp_ptr = XMC_GPIO_PORT2;
		ADS3_avg_receive_data[channel] = 0;
	}

	for (int i = 0; i < TOTAL_SAMPLES; i++)
	{
		int pkt = ADS7861_MANUAL_MODE_PKT(channel);
		uint8_t SendData[2] = { (pkt >> 8), (pkt & 0xFF) };
		uint8_t ReadData[2];
		XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		for (int i = 0; i > 16; i++)
			;
		SPI_MASTER_Transmit(&SPI_MASTER_0, SendData, 2);
		for (int i = 0; i > 9; i++)
			;
		XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		;
		for (int i = 0; i > 2; i++)
			;
		XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		for (int i = 0; i > 9; i++)
			;
		SPI_MASTER_Receive(&SPI_MASTER_0, ReadData, 2);
		for (int i = 0; i > 2; i++)
			;
		XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		;
		for (int i = 0; i > 9; i++)
			;

		XMC_GPIO_SetOutputLow((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		for (int i = 0; i > 9; i++)
			;
		SPI_MASTER_Receive(&SPI_MASTER_0, ReadData, 2);

		XMC_GPIO_SetOutputHigh((XMC_GPIO_PORT_t *) temp_ptr, pin_number);
		;

		if (temp_port_num == 5) {
//			ADS2_receive_data[channel] = ((ReadData[0] & 0x0F) << 4) | ((ReadData[1] & 0xF0) >> 4);
//			ADS2_recive_channel[channel] = ((ReadData[0] & 0xF0) >> 4);

//			ADS2_avg_receive_data[channel] += ADS2_receive_data[channel];
		} else if (temp_port_num == 2) {
//			ADS3_receive_data[channel] = ((ReadData[0] & 0x0F) << 4) | ((ReadData[1] & 0xF0) >> 4);
//			ADS3_recive_channel[channel] = ((ReadData[0] & 0xF0) >> 4);

//			ADS3_avg_receive_data[channel] += ADS3_receive_data[channel];
		}
	}
}
