
#include "VCU_PROCESS/Vcu_Process.h"
#include "InputCapture/InputCapture.h"
#include "Vcu_Config.h"
#include "can_matrix.h"
#include "string.h"
#include "4g_data_process.h"
#include "4g_module/mdm_handler.h"

uint16_t Distance = 1;
time_t starttime = 0;
uint8_t RTC_Day = 0;

vcu_fleet_fleet_10_sec TD1;
uint8_t Eventbuffer_4Gcomm[512]={0};

void Process_4G_Event_Data(void)
{

	memset(&TD1,0,sizeof(TD1));
	TD1.car_id = 10;
	TD1.trip_id = 81050;
	TD1.identifier = 318;
//	TD1.rtc.month = current_time.month;
//	TD1.rtc.days = current_time.days;
//	TD1.rtc.day_of_week = current_time.daysofweek;
//	TD1.rtc.hours = current_time.hours;
//	TD1.rtc.minutes = current_time.minutes;
//	TD1.rtc.seconds = current_time.seconds;
	TD1.hv_soc_calculated =Mapped_BMS_SOC;
	TD1.soc = ((int)(CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[1] << 8) | CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[0]);
	TD1.battery_temp=BMS_Avg_temp;
	TD1.odometer = CalOdometer();//52;//will get from cluster
	TD1.charging_indicator = Vcu_InPuts.charger_connect_IN;
	TD1.dte = ((TD1.soc)*2);
	TD1.mcu_temp_1=Mcu_Temp_Irp;
	TD1.ac_status = AC_ON_4g;//CAN_MSG_DB_HVAC[CAN_0x100].CAN_Data[2];
	TD1.min_cell_temp = ((int)((CAN_BMS_29bit[CAN_0X180CA7F3].CAN_Data[3] << 8) | CAN_BMS_29bit[CAN_0X180CA7F3].CAN_Data[2]));
	TD1.max_cell_temp = ((int)((CAN_BMS_29bit[CAN_0X180CA7F3].CAN_Data[3] << 8) | CAN_BMS_29bit[CAN_0X180CA7F3].CAN_Data[2]));
	TD1.min_cell_voltage = ((int)((CAN_BMS_29bit[CAN_0X1808A7F3].CAN_Data[3] << 8) | CAN_BMS_29bit[CAN_0X1808A7F3].CAN_Data[2]));
	TD1.max_cell_voltage = ((int)((CAN_BMS_29bit[CAN_0X1808A7F3].CAN_Data[1] << 8) | CAN_BMS_29bit[CAN_0X1808A7F3].CAN_Data[0]));
	TD1.pack_voltage = ((int)((CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[7] << 8) | CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[6]));
	TD1.pack_current = PackCurrent;//((int)((CAN_BMS_29bit[CAN_0X180EA7F3].CAN_Data[1] << 8) | CAN_BMS_29bit[CAN_0X180EA7F3].CAN_Data[0]));
	TD1.longitude = GPS_data_val.longitude;
	TD1.latitude = GPS_data_val.latitude ;
	TD1.altitude = GPS_data_val.altitude ;
	TD1.direction = GPS_data_val.direction;
	TD1.speed = speed_4g;
	TD1.soh = (int)((CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[3] << 8) | CAN_BMS_29bit[CAN_0X180FA7F3].CAN_Data[2]);
    TD1.timestamp = epoch;
    TD1.ambient_temp=  ambient_temp;
}


	//Process_4G_Event_Data(0);
	//memset(Eventbuffer_4Gcomm, 0, 512);//change to 512

	//pb_ostream_t stream1;

	//stream1 =  pb_ostream_from_buffer(Eventbuffer_4Gcomm,sizeof(Eventbuffer_4Gcomm));
	//pb_encode(&stream1,vcu_fleet_fleet_10_sec_fields, &TD1);
void set_RTC(void)
{
	uint8_t Timebuf[35]={0};
	mod_getCurrentTime(Timebuf);
	timeval.year = (((Timebuf[0]-'0')*10)+(Timebuf[1]-'0'));
	timeval.month = (((Timebuf[3]-'0')*10)+(Timebuf[4]-'0'));
	timeval.days = (((Timebuf[6]-'0')*10)+(Timebuf[7]-'0'));
	timeval.hours = (((Timebuf[9]-'0')*10)+(Timebuf[10]-'0'));
	timeval.minutes = (((Timebuf[12]-'0')*10)+(Timebuf[13]-'0'));
	timeval.seconds = (((Timebuf[15]-'0')*10)+(Timebuf[16]-'0'));
	RTC_Day = timeval.days;
	RTC_init();
}

void epoch_time(void)
{	struct tm my_tm;
	memset(&my_tm, 0, sizeof(my_tm));
	RTC_GetTime(&current_time);
	my_tm.tm_year =(2000 + current_time.year)-1900;
	my_tm.tm_mon = current_time.month;
	my_tm.tm_mday = current_time.days;
	my_tm.tm_hour = current_time.hours;
	my_tm.tm_min = current_time.minutes;
	my_tm.tm_sec = current_time.seconds;
	my_tm.tm_isdst = -1;
	my_tm.tm_mon -= 1;

	epoch = mktime(&my_tm);
}

uint32_t CalOdometer()//For testing only
	{
		float pi = 3.14;
		float rad = 0.279;
		float GRatio = 0.10084; //  1/9.916;
		float mintosec = 0.0166;
		uint16_t DistanceM = 1;

		uint16_t timeDiff = epoch - starttime;
		uint8_t rotations = 3;

		//Distance = (2 * pi * rad * rotations);
		//Distance += (2 * pi * rad * N/(rpm) * GRatio * mintosec * TimeSec);
		DistanceM = (vspeed * (timeDiff/3600));// KM/hr
		Distance += (DistanceM/8);//3600

		return Distance;
	}

void print_struct_uart(vcu_fleet_fleet_10_sec *TD1) {
    char buffer[256];

    snprintf(buffer, sizeof(buffer), "car_id = %u\n", TD1->car_id);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "trip_id = %u\n", TD1->trip_id);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "timestamp = %lld\n", TD1->timestamp);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "latitude = %u\n", TD1->latitude);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "longitude = %u\n", TD1->longitude);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "soc = %u\n", TD1->soc);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "hv_soc_calculated = %u\n", TD1->hv_soc_calculated);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "battery_temp = %u\n", TD1->battery_temp);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "mcu_temp_1 = %d\n", TD1->mcu_temp_1);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "speed = %u\n", TD1->speed);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "odometer = %u\n", TD1->odometer);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "ambient_temp = %u\n", TD1->ambient_temp);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "pack_voltage = %u\n", TD1->pack_voltage);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "pack_current = %u\n", TD1->pack_current);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "charging_indicator = %u\n", TD1->charging_indicator);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "dte = %u\n", TD1->dte);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "ac_status = %u\n", TD1->ac_status);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "min_cell_temp = %u\n", TD1->min_cell_temp);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "max_cell_temp = %u\n", TD1->max_cell_temp);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "min_cell_voltage = %u\n", TD1->min_cell_voltage);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "max_cell_voltage = %u\n", TD1->max_cell_voltage);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "altitude = %u\n", TD1->altitude);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "direction = %u\n", TD1->direction);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "soh = %u\n", TD1->soh);
    uart_debugg4g(buffer);

    snprintf(buffer, sizeof(buffer), "identifier = %d\n", TD1->identifier);
    uart_debugg4g(buffer);
}


