//#include "VCU_Types.h"

#define TWO_BYTES					0x2
#define ADC_FULL_SCALE				0xFF
#define ADC_MID_RANGE				0x80
#define ADC_ZERO_RANGE				0x00


#define MODE_CONTROL_AUTO1			0x2000
#define PROGRAM_REGISTER_AUTO1		0x8000
#define PROGRAM_ENABLECHANNEL_AUTO1 0xFFFF

#define MODE_CONTROL_AUTO2			0x3800
#define PROGRAM_REGISTER_AUTO2		0x93C0
#define ADS2_Port5                    5
#define ADS2_Pin                     6
#define ADS3_Port2                    2
#define ADS3_Pin                     6
#define CONTINUE_MODE_PREVIOUS		0x0000

#define ADS_CHANNEL_MAX				16

enum
{
	ADC_AUTO1,
	ADC_AUTO2,
	ADC_MANUAL
}ADS_MODE;


typedef struct DIGITAL_IO_cs
{
  XMC_GPIO_PORT_t * gpio_port;             /**< port number */
  XMC_GPIO_CONFIG_t gpio_config;          /**< mode, initial output level and pad driver strength / hysteresis */
  uint8_t gpio_pin;                       /**< pin number */
  XMC_GPIO_HWCTRL_t hwctrl;               /**< Hardware port control */
} DIGITAL_IO_cs;



typedef union
{
	struct
	{
		uint16_t GPIO_Output:4;
		uint16_t output_mode:1;
		uint16_t device_operation:1;//fix 0, normal mode (no powerdown)
		uint16_t input_range:1;			//fix 0	to Vref
		uint16_t channel_selection:4;
		uint16_t enable_D0_to_D6:1;		//fix 0
		uint16_t operating_mode:4;	//0001 for manual mode
	}Bit;
	uint16_t F_Data;
}ADS7961Frame_t;

float DROPPED_IN_12V;


//ADS7961 frame format
uint8_t ADCModeAUTO2Frame[2];
//collecting data ADS1
uint8_t ADS1_receive_data[16];
uint8_t ADS1_recive_channel[16];
uint32_t ADS1_avg_receive_data[16];

//collecting data ADS2
uint8_t ADS2_receive_data[16][50];
//uint8_t ADS2_recive_channel[16]; //uncomment channel for debugging
uint32_t ADS2_avg_receive_data[16];

//collecting data ADS3//
uint8_t ADS3_receive_data[16][50];
//uint8_t ADS3_recive_channel[16]; //uncomment channel for debugging
uint32_t ADS3_avg_receive_data[16];

uint8_t flag;
float adc2_current[16];
float adc3_current[16];

XMC_GPIO_PORT_t temp;

void SPI_ADC_MANUAL_MODE(void);
void SPI_ADC_ReadAllData(uint8_t ADCMode);

uint16_t ADS7861_MANUAL_PKT(uint16_t channel);
void ADC_Read_AllChannel(uint8_t temp_port_num ,uint8_t pin_number);
void ADC_Read_by_Channel(uint8_t temp_port_num ,uint8_t pin_number,uint8_t channel);
void SPI_ADS7961_AUTO2_MODE(uint8_t temp_port_num ,uint8_t pin_number);
void SPI_ADS7961_AUTO2_Init(uint8_t temp_port_num ,uint8_t pin_number);
void DROPPED_IN_12_volt(void);
