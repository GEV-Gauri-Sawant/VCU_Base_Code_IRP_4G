/*
 * Vcu_Config.h
 *
 *  Created on: 27-Jun-2023
 *      Author: Suchit Sawant
 */

#ifndef VCU_CONFIG_H_
#define VCU_CONFIG_H_

#include "DAVE.h"

#endif /* VCU_CONFIG_H_ */

#define U38 0x92

typedef enum
{
	LOW = 0,
	HIGH
}ON_OFF;

typedef enum
{
	IGNITION_1 = 0,
	IGNITION_2,
	charger_connect
}VcuStates_t;

typedef struct
{
	bool IGNITION_1_IN;
	bool IGNITION_2_IN;
	bool charger_connect_IN;

}Vcu_InPuts_t;

typedef struct
{
	bool IGNITION_1_OUT;
	bool IGNITION_2_OUT;
	bool charger_connect_OUT;

}Vcu_OutPuts_D_t;

typedef struct
{
	bool low_beam_IN;
	bool high_beam_IN;
	bool pos_light_IN;
	bool left_indicator_IN;
	bool right_indicator_IN;
	bool hazzard_sw_IN;
	bool wiper_IN;
	bool horn_sw_IN;

}Combi_Switch_IN_t;

typedef struct
{
	bool seat_belt_d_IN;
	bool seat_belt_p_IN;
	bool seat_occup_p_IN;

}Seat_Switch_IN_t;

typedef struct
{
	bool door_lock_IN;
	bool driver_door_IN;
	bool passenger_door_IN;
	bool passenger_2l_IN;
	bool passenger_2r_IN;
	bool hatch_IN;
	bool bonnet_IN;

}Door_Switch_IN_t;

typedef struct
{

	bool low_beam_OUT;
	bool high_beam_OUT;
	bool pos_light_OUT;
	bool left_indicator_OUT;
	bool right_indicator_OUT;
	bool hazzard_sw_OUT;
	bool wiper_OUT;
	bool horn_sw_OUT;
	bool ac_blower1_OUT;
	bool ac_blower2_OUT;
	bool ac_blower3_OUT;

	bool ac_radiator_pwr_out;
	bool audio_amp_pwr_out;
	bool wiper_pwr_out;
	bool pwr_window_out;
	bool cigarette_lighter_en_out;
	bool door_lock_pwr_out;
	bool sunroof_pwr_out;
	bool orvm_pwr_out;
	bool vacuum_pump_out;
	bool horn_pwr_out;
	bool pwr_steering_out;
	bool infotainment_pwr_out;
	bool vcu_fan_pwr_out;
	bool instrument_con_pwr_out;
	bool orvm_fold_out;
	bool orvm_open_out;
	bool headlamp_adj_pwr_out;
	bool lights_pwr_out;
	bool pos_light_out;
	bool rev_light_out;
	bool pwr_window_r_out;
	bool brake_light_out;
	bool cabin_light_out;
	bool ac_sol_pwr_out;
	bool mc_fan_pwr_out;
	bool hv_batt_fan_pwr_out;
	bool elec_handbrake_pwr_out;
	bool mc_relay_pwr_out;
	bool aux_efuse_1_out;
	bool aux_efuse2_out;
	bool aux_efuse3_out;
	bool aux_efuse4_out;
	bool aux_efuse5_out;
	bool compressor_a_pwr_out;
	bool door_lock_enable_out;
	bool mc_contactor_relay;

}Relay_Control_Switch_OUT_t;

typedef struct
{

	int set_temperature;
	bool blower_speed1_IN;
	bool blower_speed2_IN;
	bool blower_speed3_IN;
	bool ac_mode; //(semi auto/fully auto)
	bool circulation_on_off;
	int heater_cooler; // (analog)
	int external_air_intake_on_off;
	bool ac_solenoid;

}Hvac_IN_t;


typedef struct
{
	bool charging_connected_IN;
	bool accl_pedal_sw_IN;
	bool orvm_fold_IN;
	bool orvm_open_IN;
	bool accelerator_input;
	bool electronic_brake_in_d;
	bool brake_oil_IN;
	bool vacuum_sensor_IN;
	bool handbrake_sw_IN;
	bool gear_sw1_IN;
	bool gear_sw2_IN;
	bool gear_sw3_IN;
	bool gear_sw4_IN;
	bool sunroof_enable_IN;
	bool ac_on_in;
	bool regen_enable_IN;
	bool power_window_in_d;
	bool buzzer_en_d_IN;
	bool brake_sw_in_d;
	bool charging_started_IN_d;

}Switch_Ios_IN_t;

typedef struct
{
	bool regen_relay;
	bool reverse_relay;
	bool park_relay;
	bool forward_Relay;
	bool neutral;

}Motor_controller_OUT_t;

typedef struct
{

	bool pos_light_out;
	bool brake_switch_out_d;
	bool reverse_light_out;
	bool left_indicator_out;
	bool right_indicator_out;
	bool hazard_lights_out;
	bool high_beam_out;
	bool low_beam_out;

}Lights_OUT_T;

typedef struct
{
	int Speed_Sensor;
	bool VACUUM_SENSOR_IN_D;
	bool day_light_sensors_IN;

}Sensors_IN_t;

typedef struct
{
	bool AUX_IN2_D;
	bool AUX_IN3_D;
	bool AUX_IN4_D;
	bool AUX_IN5_D;
	bool AUX_ANALOG1_IN_D;
	bool AUX_IN1_D;
}Aux_Inputs_t;

typedef struct
{
	bool door_driver_out;

	bool door_passenger_out;
	bool door_passenger_2L_out;
	bool door_passenger_2R_out;
	bool door_hatch_out;
	bool cluster_door_bonnet_out;
	bool set_left_indicator;
	bool set_right_indicator;
	bool set_low_beam;
	bool set_high_beam;
	bool set_brake_oil;
	bool aux_vtg_critical;
	bool eps_status;
	bool battery_temp_exceeded;
	bool charging_connected;
	bool regen_enabled;
	bool SOC_critical;

	bool main_vtg_critical;

}Instrument_Cluster_OUT_t;



typedef struct
{
	bool seat_belt_driver;
	bool seat_belt_passenger;
	bool seat_occupied;

}Seat_Belt_OUT_t;


typedef struct
{
	bool door_lock_OUT;
	bool driver_door_OUT;
	bool passenger_door_OUT;
	bool passenger_2l_OUT;
	bool passenger_2r_OUT;
	bool hatch_OUT;
	bool bonnet_OUT;

}Door_Switch_OUT_t;


typedef union
{
	uint8_t neutral;
	uint8_t forward;
	uint8_t reverse;
	uint8_t park;

}Gear_OUT_t;

typedef union
{
	uint8_t eco;
	uint8_t normal;
	uint8_t power;
	uint8_t DriveMode;
}Instrumetcluster_DriveMode_OUT_t;

typedef struct instrument_cluster_doorsvar_t
{
	uint8_t door_lock_OUT;
	uint8_t driver_door_OUT;
	uint8_t passenger_door_OUT;
	uint8_t passenger_2l_OUT;
	uint8_t passenger_2r_OUT;
	uint8_t hatch_OUT;
	uint8_t bonnet_OUT;

}instrument_cluster_doorsvar_t;

typedef union Drive_Mode_OUT_t
{
	uint8_t eco_mode;
	uint8_t normal_mode;
	uint8_t power_mode;

}Drive_Mode_OUT_t;


typedef struct GPS_data
{
	uint32_t longitude;
    uint32_t latitude;
    int32_t altitude;
    int32_t direction;
}GPS_data_t;


int *cluster_door_in;

extern Vcu_InPuts_t Vcu_InPuts;

Vcu_OutPuts_D_t Vcu_OutPuts;

Combi_Switch_IN_t Combi_Switch_IN;

Seat_Switch_IN_t Seat_Switch_IN;

Door_Switch_IN_t Door_Switch_IN;

Relay_Control_Switch_OUT_t Relay_Control_Switch_OUT;

Hvac_IN_t Hvac_IN;

Switch_Ios_IN_t Switch_Ios_IN;

Motor_controller_OUT_t Motor_controller_OUT;

Lights_OUT_T Lights_OUT;

Sensors_IN_t Sensors_OUT;

Aux_Inputs_t Aux_Inputs;

Instrument_Cluster_OUT_t Instrument_Cluster_OUT;

Seat_Belt_OUT_t Seat_Belt_OUT;

Gear_OUT_t *Gear_OUT;

Instrumetcluster_DriveMode_OUT_t *Instrumetcluster_DriveMode_OUT;

Door_Switch_OUT_t Door_Switch_OUT;

instrument_cluster_doorsvar_t instrument_cluster_doorsvar;

int cluster_door_out;

//uint8_t CState, PreState;



XMC_RTC_TIME_t current_time,timeval;

GPS_data_t GPS_data_val;
time_t epoch;
// Adding for ambient_temp
uint8_t ambient_temp;

//flag added to check if vehicle is in drive mode or not (i.e ign 1) used for packet publishing using 4G
bool is_drive_mode;
