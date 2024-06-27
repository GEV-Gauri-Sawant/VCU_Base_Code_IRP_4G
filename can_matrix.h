//#include "Vcu_Config.h"
/* CAN NODE 0 */
#define CAN_TX_MO_COUNT_CLUSTER			7U
#define CAN_TX_MO_MC_INIT_BASE			7U
#define CAN_TX_MO_MC_INIT_TOP			(5U + CAN_TX_MO_MC_INIT_BASE)
#define CAN_RX_MO_MC_BASE				CAN_TX_MO_MC_INIT_TOP
#define CAN_RX_MO_MC_TOP				CAN_RX_MO_MC_BASE + 3U

#define CAN_TX_MO_COUNT_GTAKE  			CAN_RX_MO_MC_TOP
#define CAN_RX_MO_GTAKE_BASE    		CAN_TX_MO_COUNT_GTAKE
#define CAN_RX_MO_GTAKE_TOP     		CAN_RX_MO_GTAKE_BASE + 5

/* CAN NODE 1 */
#define CAN_TX_MO_COUNT_HVAC	0
#define CAN_RX_MO_HVAC_BASE		0
#define CAN_RX_MO_HVAC_TOP		3

#define CAN_RX_MO_BMS_BASE		CAN_RX_MO_HVAC_TOP
#define CAN_RX_MO_BMS_TOP		CAN_RX_MO_BMS_BASE + 7

//Delays
#define DELAY_1s	1000
#define DELAY_500ms	500
#define DELAY_300ms	300
#define DELAY_200ms	200
#define DELAY_100ms	100
#define DELAY_50ms	50

//Byte positions
#define ZERO_BYTE     0
#define FIRST_BYTE    1
#define SECOND_BYTE   2
#define THIRD_BYTE    3
#define FOURTH_BYTE   4
#define FIFTH_BYTE    5
#define SIXTH_BYTE    6
#define SEVENTH_BYTE  7

#ifdef HVAC_0x100
	#define HIGH_PRESSURE_mP 1.47
#else
	#define HIGH_PRESSURE_mP 2.25
#endif



#define CAN_id102_250kbps 20
#define CAN_id103_250kbps 21
#define CAN_id104_250kbps 22
#define CAN_id105_250kbps 23
#define CAN_id113_250kbps 24
#define CAN_id114_250kbps 25
#define CAN_id116_250kbps 26


typedef struct
{
	uint32_t 	MSG_ID;
	uint8_t		CAN_Data[8];
}CAN_MSG_t;

/************************OBD_II***************************/

typedef struct
{
	uint32_t 	MSG_ID;
	int8_t		CAN_Data[8];
}OBD_CAN_MSG_t;


typedef enum
{
	can_0x01 = 0,
	can_0x02,
	can_0x03,
	can_0x04,
	can_0x05,
	can_OBD_max
}OBD_index_t;

/*************************OBD_II_end***************************/

/*******gtake ****************/

typedef struct
{
	uint8_t faults_Code : 8;
}GtakeFault_t;

enum GtakeFaultCodeValue
{
	Software_overcurrent_protection = 1,
	Software_overvoltage_protection = 4,
	Drive_protection = 7,
	Motor_autotunning_failed = 8,
	Driver_overload = 9,
	Motor_overload = 10,
	U_phase_Current_Hall_Abnormal = 11,
	Motor_output_shortcircuit_to_earth = 12,
	Inverter_module_overload_protection = 15,
	Driver_overheat = 16,
	Motor_overheat = 17,
	Driver_tempdetection_channel_disconnected = 18,
	Readwrite_Fault_of_driver_parameters = 29,
	Software_version_inconsistent = 35,
	Version_recognition_error = 36,
	Overcurrent_benchmark_error = 37,
	Overlimit_protection_of_power_software_on_driver_control_board = 38,
	Stall_fault = 39,
	AI_input_overlimit_fault = 40,
	Bus_undervoltage_protection = 41,
	CAN_communication_exception = 46,
	Motor_overspeed_fault = 47,
	Motor_temperature_sensor_disconnected = 48,
	Hardware_overcurrent_protection = 49,
	Hardware_overvoltage_protection = 50,
	Drive_power_undervoltage_protection = 51,
	Driver_exception_protection = 53,
	//Overlimit_protection_of_power_software_on_driver_control_board = 54,
	Vphase_Current_Hall_Abnormal = 59,
	Wphase_Current_Hall_Abnormal = 60

};

typedef struct
{
	uint8_t Motor_direction_cmd:3;
	uint8_t Drive_mode_cmd:3;
	uint8_t reserved_0:2;

	uint8_t reserved_1;
	uint8_t reserved_2;
	uint8_t reserved_3;
	uint8_t reserved_4;
	uint8_t reserved_5;
	uint8_t reserved_6;
	uint8_t reserved_7;

}Gtake_tx_0x8000121_t;

typedef struct
{
	uint8_t reserved_00:1;
	uint8_t reserved_01:1;
	uint8_t reserved_02:1;
	uint8_t reserved_03:1;
	uint8_t reserved_04:1;
	uint8_t reserved_05:1;
	uint8_t Brake_cmd:1;
	uint8_t Hill_hold_assist:1;

	uint8_t reserved_1;
	uint8_t reserved_2;
	uint8_t reserved_3;
	uint8_t reserved_4;
	uint8_t reserved_5;
	uint8_t reserved_6;
	uint8_t reserved_7;

}Gtake_tx_0x8000111_t;

typedef enum
{
	CAN_id0x8000201 = 0,
	CAN_id0x8000211,
	CAN_id0x8000221,
	CAN_id0x8000230,
	CAN_id0x8000231,
	CAN_id0x8000241,
	CAN_id0x8000121,
	CAN_id0x8000111,
	CAN_Gtake_Total_id29bit

}CANIndexGtake_29bit;

typedef enum
{
	fwd = 0,
	rev = 1
}MotorDirection;

typedef enum
{
	stop_cmd = 0,
	power_mode_mcu = 1,
	normal_mode_mcu = 2,
	eco_mode_mcu = 3,
	limphome_mode_mcu = 4

}AdditionalFeatures;

typedef struct
{
	/* 0 */
	uint8_t Motor_direction_cmd:3;
	uint8_t Drive_mode_cmd:3;
	uint8_t reserved_0:2;

	uint8_t reserved_1;
	uint8_t reserved_2;
	uint8_t reserved_3;
	uint8_t reserved_4;
	uint8_t reserved_5;
	uint8_t reserved_6;
	uint8_t reserved_7;

}Gtake_Mcu_tx_id0x121_t;
/*
typedef enum
{
	power_mode = 1,
	normal_mode = 2,
	eco_mode = 3
}MotorDrive_Mode_t;
*/
/*********gtake end *************/

/*********irp start***************/


typedef enum
{
	eco_mode_irp = 0,
	city_mode_irp = 1,
	sport_mode_irp = 2,
	Limp_Crawl_irp = 3

}DriveMode_IRP;

typedef enum
{
	Neutral_Irp = 0,
	Forward_Irp = 1,
	Reverse_Irp = 2,
	Fault_Irp = 3

}IRP_FNR;

typedef enum
{
	CAN_id0x10,
	CAN_id0x11,
	CAN_id0x12,
	CAN_id0x13,
	CAN_id0x20,
	CAN_id0x21,
	CAN_id0x30,
	CAN_id0x31,
	CAN_id0x32,
	CAN_id0x33,
	CAN_id0x55,
	CAN_IRP_Total_id29bit

}CANIndexIrp;

#pragma pack(1)

typedef struct
{
	uint8_t FNR:2;
	uint8_t Driving_Profile:3;
	uint8_t Brake_Command:1;
	uint8_t Handbrake_Command:1;
	uint8_t Ignition_Key_indicator:1;

	uint16_t Throttle_Command:10;
	uint8_t Regen_On_Brake:1;
	uint8_t Regen_On_Throttle_Realese:1;
	//uint8_t reserved:4;
	//uint8_t Regen_On_Brake:1;
	//uint8_t Regen_On_Throttle_Realese:1;
	//uint8_t reserved_1_2:2;

	int16_t Torque_Command:13;
	uint8_t reserved_2:3;

	uint8_t reserved_3:8;
	uint8_t reserved_4:4;
	uint8_t VCU_Alive_Counter:4;

	uint8_t VCU_Checksum;

}IRP_Mcu_tx_id0x10_t;


typedef struct
{
	uint8_t BMS_OperationMode;

	uint8_t BMS_Contactor_Status:2;
	uint8_t reserved_1:6;

	uint8_t SOH:7;
	uint8_t reserved_2:1;

	uint16_t BMS_SOC :10;
	uint8_t resreved_3:6;

	uint8_t reserved_4;
	uint8_t reserved_5;
	uint8_t reserved_6;

}IRP_Mcu_tx_id0x20_t;

typedef struct
{
	uint16_t Battery_Voltage:13;
	uint8_t reserved_1:3;

	int16_t Battery_Current:11;
	uint8_t reserved_2:5;

	int16_t MaxDischargeCurrent:11;
	uint8_t reserved_3:5;

	int16_t MaxRechargeCurrent :11;
	uint8_t resreved_4:5;

}IRP_Mcu_tx_id0x21_t;

#pragma pack

typedef struct
{
	int16_t Speed_rpm:15;
	//uint8_t reserved_1:1;

	int16_t Torque_Estimation:13;
	//uint8_t reserved_2:3;

	int16_t DC_Current:11;
	//uint8_t reserved_3:5;

	uint16_t DC_Voltage:13;
	//uint8_t reserved_1:3;

	uint8_t Msg_013_Alive_Counter:4;
	//uint8_t reserved_5:4;

	uint8_t Msg_013_Checksum;
}__attribute__((packed)) IRP_Mcu_rx_id0x13_t;


typedef struct
{
	int16_t Thorttle:10;
	int8_t MCU_State:3;
	bool Hill_hold_flag:1;
	bool Creep_flag:1;
	uint8_t reserved_1:1;
	uint8_t Motor_temp;
	uint8_t MCU_temp;
	uint8_t Precharge_temp;
	uint8_t FNR_State:2;
	uint8_t reserved_2:6;
	uint8_t Active_Driving_Profile:4;
	uint8_t Msg_012_Alive_Counter:4;
	uint8_t Msg_012_Checksum;

}IRP_Mcu_rx_id0x12_t;

typedef struct
{

	bool FLT_MotorOverTemp:1;
	bool FLT_MotorLowTemp:1;
	bool FLT_MotorTempSensor:1;
	bool FLT_ControllerOverTemp:1;
	bool FLT_ControllerLowTemp:1;
	bool FLT_ControllerTempSensor:1;
	bool FLT_PreChargeOverTempPbit:1;
	bool FLT_PreChargeOverTempCbit:1;
	bool FLT_PreChargeTempSensor:1;
	bool FLT_CpuOverTemp:1;
	bool FLT_Phase_U_OverCurrentPeak:1;
	bool FLT_Phase_U_Sensor:1;
	bool FLT_Phase_V_OverCurrentPeak:1;
	bool FLT_Phase_V_Sensor:1;
	bool FLT_Phase_W_OverCurrentPeak:1;
	bool FLT_Phase_U_Disconnected:1;
	bool FLT_Phase_V_Disconnected:1;
	bool FLT_Phase_W_Disconnected:1;
	bool FLT_BusOverCurrent:1;
	bool FLT_BusCurrentSensor:1;
	bool FLT_PreChargeUnderVoltage:1;
	bool FLT_BusUnderVoltage:1;
	bool FLT_BusLowVoltage:1;
	bool FLT_BusHighVoltage:1;
	bool FLT_BusOverVoltage:1;
	bool FLT_PreChargeLatch:1;
	bool FLT_PreChargeTimeout:1;
	bool FLT_GateDriverVoltage:1;
	bool FLT_VswUnderVoltage:1;
	bool FLT_PositionSensor:1;
	bool FLT_MemoryRead:1;
	bool FLT_CanNoCom:1;
	bool FLT_CanTimeout:1;
	bool FLT_CanMb0Timeout:1;
	bool FLT_CanMb1Timeout:1;
	bool FLT_CanMb2Timeout:1;
	bool FLT_CanMb3Timeout:1;
	bool FLT_CanInvalidCommand:1;
	bool FLT_CanDigitalInput:1;
	bool FLT_ThrottleInvalid:1;
	bool FLT_Throttle:1;
	bool FLT_PerfDeratingBusVoltage:1;
	bool FLT_PerfDeratingControllerTemp:1;
	bool FLT_PerfDeratingMotorTemp:1;
	bool FLT_MotorStall:1;
	bool FLT_FusaPbit:1;
	bool FLT_FusaCbit:1;
	bool FLT_I2T:1;
	bool FLT_CurrentFactory:1;
	bool FLT_Project0:1;
	bool FLT_Project1:1;
	bool FLT_Project2:1;
	bool FLT_Project3:1;
	bool FLT_Project4:1;
	bool FLT_Project5:1;
	bool FLT_Project6:1;
	bool FLT_Project7:1;
	bool FLT_Project8:1;
	bool FLT_Project9:1;
	bool FLT_Project10:1;

}IRP_Mcu_rx_id0x30_t;

/**********irp end***************/

typedef struct
{
	uint8_t reserved_00:1;
	uint8_t reserved_01:1;
	uint8_t Steering_Wheel_Angle_Validity:1;
	uint8_t reserved_03:1;
	uint8_t reserved_04:1;
	uint8_t reserved_05:1;
	uint8_t Steering_Wheel_Angle_Sensor_Calibration_Status:1;
	uint8_t Steering_Wheel_Angle_Sensor_Initialized:1;

	uint8_t reserved_10:1;
	uint8_t reserved_11:1;
	uint8_t reserved_12:1;
	uint8_t reserved_13:1;
	uint8_t reserved_14:1;
	uint8_t reserved_15:1;
	uint8_t reserved_16:1;
	uint8_t Steering_Wheel_Angle:1;

	uint8_t reserved_2:8;

	uint8_t reserved_30:1;
	uint8_t reserved_31:1;
	uint8_t Steering_Load_EPS_Active:1;
	uint8_t reserved_33:1;
	uint8_t Power_Steering_Fault_Indication_On_EPS:1;
	uint8_t reserved_35:1;
	uint8_t reserved_36:1;
	uint8_t reserved_37:1;

	uint8_t reserved_40:1;
	uint8_t reserved_41:1;
	uint8_t reserved_42:1;
	uint8_t reserved_43:1;
	uint8_t reserved_44:1;
	uint8_t reserved_45:1;
	uint8_t reserved_46:1;
	uint8_t EPS_Working_Current_EPS:1;

	uint8_t reserved_5 :8;

	uint8_t reserved_60:1;
	uint8_t reserved_61:1;
	uint8_t reserved_62:1;
	uint8_t reserved_63:1;
	uint8_t reserved_64:1;
	uint8_t reserved_65:1;
	uint8_t reserved_66:1;
	uint8_t Steering_Wheel_Angle_Alive_Rolling_Count:1;

	uint8_t reserved_70:1;
	uint8_t reserved_71:1;
	uint8_t reserved_72:1;
	uint8_t reserved_73:1;
	uint8_t reserved_74:1;
	uint8_t reserved_75:1;
	uint8_t reserved_76:1;
	uint8_t Steering_Wheel_Angle_CheckSum:1;

}eps_status_t;

typedef struct
{
	/* byte 5 */
	uint8_t hardware_failure :1;
	uint8_t temperature_of_charger :1;
	uint8_t input_voltage :1;
	uint8_t starting_state :1;
	uint8_t communication :1;

	uint8_t reserved_5 :1;
	uint8_t reserved_6 :1;
	uint8_t reserved_7 :1;

}obc_madhura_byte5_t;

typedef enum
{
	can_0x1806E5F4 = 0,
	can_0x18FF50E5,
	can_obc_max
}obc_madhura_index_t;

typedef struct instrument_clustor_buzzer
{

	//uint8_t low_battery :1;
	uint8_t charging_connected :1;
	//uint8_t charging_completed :1;
	uint8_t seat_belt_warning :1;
	uint8_t door_ajar :1;
	uint8_t light_kept_on :1;
	uint8_t imminent_danger :1;
	uint8_t wrong_gear :1;

	uint8_t reserved_1 :8;

	uint8_t reserved_2 :8;
	uint8_t reserved_3 :8;

	uint8_t reserved_4 :8;

	uint8_t reserved_5 :8;
	uint8_t reserved_6 :8;

	uint8_t reserved_7 :8;

}instrument_clustor_buzzer_t;

 typedef struct instrument_clustor_indicators
{
	 uint8_t reserved_0 :8;

	 uint8_t reserved_1 :8;

	 uint8_t reserved_2 :8;

	uint8_t left_indicator:1;
	uint8_t right_indicator:1;
	uint8_t low_beam:1;
	uint8_t high_beam:1;
	uint8_t brake_fluid_flow:1;
	uint8_t eps_failure:1;
	uint8_t aux_battery_low:1;
	uint8_t battery_high_temp:1;

	uint8_t reserved_4 :8;

	uint8_t charging_on:1;
	uint8_t generic_alarm:1;
	uint8_t regen:1;
	uint8_t parking_brake_light:1;
	uint8_t seat_belt:1;
	uint8_t hold_assist:1;
	uint8_t overspeed:1;

}instrument_clustor_indicators_t;

typedef enum
{
	eco_mode_cluster = 0,
	city_mode_cluster = 1,
	sport_mode_cluster = 2,
	invalid_data_cluster = 3

}DriveMode_Cluster;

typedef enum
{
	Fault_condition = 0,
	left_door ,
	right_door,
	left_right,
	hood,
	hood_left,
	hood_right,
	hood_left_right,
	tailgate,
	tailgate_left,
	tailgate_right,
	tailgate_left_right,
	tailgate_hood,
	tailgate_hood_left,
	tailgate_hood_right,
	tailgate_hood_left_right,
	/*hood_left,
	hood_right,
	hood_left_right,
	tailgate*/
}instrument_clustor_doors_t;

typedef struct eps
{
	uint32_t mess_id;
	uint8_t can_matrix[8];
}eps_t;

typedef struct obc_triphase
{
	uint32_t mess_id;
	uint8_t can_matrix[8];
}obc_triphase_t;

typedef enum
{
	can_0x0391 = 0,
	can_0x0388,
	obc_total_id
}obcindex_t;

typedef enum
{
	can_0x1E5 = 0,
	can_0x605,
	can_0x16c,
	can_0x120,
	can_0x17d,
	can_0x4c5,
	can_0x36a,
	can_0x53d,
	eps_total_id
}epsindex_t;

/**************************** BMS ******************************/



typedef enum
{
	CAN_0X180EA7F3,
	CAN_0X180FA7F3,
	CAN_0X1810A7F3,
	CAN_0X1811A7F3,
	CAN_0X1813A7F3,
	CAN_0X1814A7F3,
	CAN_0X1815A7F3,
	CAN_0X180CA7F3,
	CAN_0X1808A7F3,
	CAN_0X180AA7F3,
	CAN_0X180BA7F3,
	bms_total_id29bit
}bmsIndex_t;


typedef struct bmsFault1
{
	uint8_t Cell_High_Voltage_Fault :1;
	uint8_t Pack_High_Voltage_Fault :1;
	uint8_t Cell_High_temperature_Drive_Fault :1;
	uint8_t Cell_High_temperature_Charge_Fault :1;
	uint8_t Charge_Gun_high_temperature_Fault :1;
	uint8_t BMS_onboard_high_temperature_Fault :1;
	uint8_t Discharge_drive_high_current_Fault :1;
	uint8_t Slow_Charge_high_current_Fault_Charge :1;
	uint8_t Regenerative_high_current_Fault :1;
	uint8_t Cell_Low_Voltage_Fault :1;
	uint8_t Pack_Low_Voltage_Fault :1;
	uint8_t Cell_Low_temperature_Drive_Fault :1;
	uint8_t Cell_Low_temperature_Charge_Fault :1;
	uint8_t Open_Wire_Fault :1;
	uint8_t Pack_Voltage_mismatch_Fault :1;
	uint8_t AFE_IC_Communication_Fault :1;
	uint8_t Cell_Delta_high_Voltage_Fault :1;
	uint8_t Cell_Delta_high_temperature_Fault :1;
	uint8_t EEPROM_readwrite_Fault :1;
	uint8_t Internal_communication_Fault_MastertoSlave :1;
	uint8_t Balancing_stuck_Fault :1;
	uint8_t Isolation_Resistance_Fault :1;
	uint8_t Weak_cell_Fault :1;

}bmsFault1_t;

typedef struct bmsFault2
{
	uint8_t Cell_High_Voltage_Alarm;
	uint8_t Pack_High_Voltage_Alarm;
	uint8_t Cell_Low_Voltage_Alarm;
	uint8_t Pack_Low_Voltage_Alarm;
	uint8_t Discharge_drive_high_current_Alarm;
	uint8_t Slow_Charge_high_current_Alarm;
	uint8_t Fast_Charge_high_current_Alarm;
	uint8_t Regenerative_high_current_Alarm;
	uint8_t Charge_Gun_high_temperature_Alarm;
	uint8_t BMS_onboard_high_temperature_Alarm;
	uint8_t Cell_Low_temperature_Drive_Alarm;
	uint8_t Cell_Low_temperature_Charge_Alarm;
	uint8_t SOC_Jump_Alarm;
	uint8_t SOH_Jump_Alarm;
	uint8_t Pack_Voltage_mismatch_Alarm;
	uint8_t Cell_Delta_high_Voltage_Alarm;
	uint8_t Cell_Delta_high_temperature_Alarm;

}bmsFault2_t;


typedef enum
{
	CAN_0x102 = 0,
	CAN_0x103,
	CAN_0x104,
	CAN_0x105,
	CAN_0x113,
	CAN_0x114,
	CAN_0x116,
	CAN_BMS_MAX
}eCanMSGIndexBMS_t;

/*************************** BMS END *********************************/


/***************************cluster **********************************/
typedef enum
{
	CAN_18FF0921 = 0,
	CAN_0CF00400,
	CAN_18FFC621,
	CAN_18FFB632,
	CAN_0CF10121,
	CAN_18FEEE00,
	CAN_18FF2021,
	CAN_18FF2121,
	CAN_18FED911,
	CAN_CLUSTER_MAX
}eCanMSGIndexCluster_t;

typedef struct
{
	uint8_t cluster_Fault_Indicator;
}cluster_Fault_Indicator_t;

typedef enum
{
	powermode_cluster = 2,
	normalmode_cluster = 1,
	ecomode_cluster = 0
}clususter_DriveMode_t;
/***************************cluster end **********************************/

extern CAN_MSG_t CAN_MSG_DB[CAN_CLUSTER_MAX];

typedef enum
{
//	CAN_0x00 = 0,
//	CAN_0x626,
//	CAN_0x226,
//	CAN_0x326,
//	CAN_0x80,
	CAN_0x1A6 = 0,
	CAN_0x2A6,
	CAN_0xA6,
	CAN_MC_MAX
}eCanMSGIndexMC_t;

typedef enum
{
	CAN_0x121 = 0,
	CAN_0x201,
	CAN_0x211,
	CAN_0x221,
	CAN_0x231,
	CAN_MC_GTAKE_MAX
}eCanMSGIndexMCGTake_t;

typedef struct
{
	uint8_t speed_5th_byte;
	uint8_t speed_6th_byte;
}speed_cluster_t;

typedef enum
{
	CAN_0x238 = 0,
	CAN_0x100,
	CAN_0x248,
	CAN_0x8000250,
	CAN_0x8000530,
	CAN_0x8000100,
	CAN_HVAC_MAX
}eCanMSGIndexHVAC_t;

typedef struct
{
	uint8_t Fault_indicator;
	uint8_t Hvbatt_Fault;
	uint8_t Mcu_Fault;
}allFault_indicator_t;

/* Prototypes */
uint8_t calculate_speed(int16_t motor_rpm);
void delay(uint32_t delay_ms);
//inline void delay(uint32_t delay_ms)

void CAN_OUTPUT_CLUSTER(void);
void CAN_OUTPUT_COMPRESSOR(void);
void CAN_INPUT_HVAC(void);
void Process_Read_CAN_0x100(void);
void Process_Read_CAN_0x248(void);
void Process_CAN_0x248(void);
void Process_CAN_0x100(void);
void Read_CAN_0x248(void);
void Read_CAN_0x100(void);
void Read_CAN_0x8000100(void);
void Process_Read_CAN_0x8000100(void);
void Read_CAN_Hifire_0x8000250(void);
void Process_CAN_Hifire_0x8000250(void);

void Process_Read_CAN_0x102(void);
void Process_Read_CAN_0x103(void);
void Process_Read_CAN_0x104(void);
void Process_Read_CAN_0x105(void);
void Process_Read_CAN_0x113(void);
void Process_Read_CAN_0x114(void);
void Process_Read_CAN_0x116(void);
void Process_CAN_0x102(void);
void Process_CAN_0x103(void);
void Process_CAN_0x104(void);
void Process_CAN_0x105(void);
void Process_CAN_0x113(void);
void Process_CAN_0x114(void);
void Process_CAN_0x116(void);
void Read_CAN_BMS(void);

void Read_CAN_0x102_250kbps(void);
void Read_CAN_0x103_250kbps(void);
void Read_CAN_0x104_250kbps(void);
void Read_CAN_0x105_250kbps(void);
void Read_CAN_0x113_250kbps(void);
void Read_CAN_0x114_250kbps(void);
void Read_CAN_0x116_250kbps(void);
void Read_CAN_0x102_250kbps(void);
void Read_CAN_0x103_250kbps(void);
void Read_CAN_0x104_250kbps(void);
void Read_CAN_0x105_250kbps(void);
void Read_CAN_0x113_250kbps(void);
void Read_CAN_0x114_250kbps(void);
void Read_CAN_0x116_250kbps(void);

void Update_CAN_id0x1806E5F4(void);
void Process_CAN_0x0388(void);
void Read_CAN_0x0388(void);


void update_id0x4c5();
void update_id0x36a();

void CAN_Tx_id0x8000111(void);
void CAN_Tx_id0x8000121(void);
void Gtake_Tx_29bit(void);

void OBDII_CAN_Tx(void);

long map(long x, long in_min, long in_max, long out_min, long out_max);

uint8_t BMS_SOC;
extern CAN_MSG_t CAN_MSG_DB[CAN_CLUSTER_MAX];
extern CAN_MSG_t CAN_MSG_DB_BMS[CAN_BMS_MAX];
extern CAN_MSG_t CAN_MSG_DB_GTAKE[CAN_MC_GTAKE_MAX];

CAN_MSG_t CAN_MSG_DB_HVAC[CAN_HVAC_MAX];

extern instrument_clustor_indicators_t *instrument_clustor_indicators;
extern eps_t eps_n[eps_total_id];
eps_status_t *eps_status;
extern obc_triphase_t obc_triphase_n[obc_total_id];

extern uint16_t current_rpm;
extern uint16_t vspeed;

extern CAN_MSG_t obc_madhura[can_obc_max];
extern obc_madhura_index_t obc_madhura_index;
extern obc_madhura_byte5_t obc_madhura_status_flags;

extern instrument_clustor_buzzer_t *instrument_clustor_buzzer;

instrument_clustor_doors_t instrument_clustor_doors;

extern Gtake_Mcu_tx_id0x121_t *Gtake_Mcu_drive_states;
extern Gtake_tx_0x8000121_t *Gtake_Mcu_drive_states_29bit;
extern Gtake_tx_0x8000111_t *Gtake_Mcu_drive_states_additional_29bit;
extern CAN_MSG_t CAN_Gtake_29bit[CAN_Gtake_Total_id29bit];
CAN_MSG_t CAN_BMS_29bit[bms_total_id29bit];
CAN_MSG_t CAN_IRP_29bit[CAN_IRP_Total_id29bit];

uint8_t charge_complete, charging_started;
uint16_t Bms_SOC, Bms_SOH;
uint8_t Mapped_BMS_SOC;
int16_t Bms_minTemp,Bms_maxTemp;
int PackCurrent, PackVoltage;
uint16_t RegenerativeCurrentLimit;
uint16_t ChargeCurrentLimit;
int16_t DischargeCurrentLimit;
int HvBatteryPower;

bmsFault1_t *bmsFault1;
bmsFault2_t *bmsFault2;

GtakeFault_t *GtakeFaults;

allFault_indicator_t allFault_indicator;

cluster_Fault_Indicator_t *cluster_Fault_Indicator;

int Mcu_Temp, Motor_Temp;

uint16_t VehicleSpeedglb;

OBD_CAN_MSG_t OBDII_CAN[can_OBD_max];
uint16_t OBD_data;

IRP_Mcu_tx_id0x10_t *Irp_Mcu_drive_states_29bit;
IRP_Mcu_tx_id0x20_t *Irp_Mcu_BMS_states_29bit;
IRP_Mcu_rx_id0x13_t *Irp_Mcu_Torques_29bit;
IRP_Mcu_tx_id0x21_t *Irp_Mcu_BMS_Currents_29bit;
IRP_Mcu_rx_id0x12_t *Irp_MCU_Status_29bit;
IRP_Mcu_rx_id0x30_t *Irp_MCU_Faults_29bit;
int16_t DC_Current_irp, MotorPower_Irp, Torque_Estimation;
uint16_t DC_Voltage_irp;
uint16_t Mcu_Temp_Irp, Motor_Temp_Irp;
uint16_t RPM;
bool Regenration_flag;
uint16_t hv_count;

//Adding BMS Avg temperature
int BMS_Avg_temp;

//Adding AC status
bool AC_ON_4g;
//Adding speed for 4g
uint16_t speed_4g;
