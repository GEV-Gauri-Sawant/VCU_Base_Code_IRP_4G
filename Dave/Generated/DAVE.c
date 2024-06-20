
/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2014-06-16:
 *     - Initial version<br>
 * 2015-08-28:
 *     - Added CLOCK_XMC1_Init conditionally
 * 2018-08-08:
 *     - Add creation of projectData.bak file
 * 2019-01-30:
 *     - Fix creation of projectData.bak file
 * 2019-04-29:
 *     - Make DAVE_Init() weak, the user can reimplement the function
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "DAVE.h"

/***********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/*******************************************************************************
 * @brief This function initializes the APPs Init Functions.
 *
 * @param[in]  None
 *
 * @return  DAVE_STATUS_t <BR>
 ******************************************************************************/
__WEAK DAVE_STATUS_t DAVE_Init(void)
{
  DAVE_STATUS_t init_status;
  
  init_status = DAVE_STATUS_SUCCESS;
     /** @Initialization of APPs Init Functions */
     init_status = (DAVE_STATUS_t)CLOCK_XMC4_Init(&CLOCK_XMC4_0);

  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DC_DC_EN_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DC_DC_EN_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance VACUUM_PUMP_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&VACUUM_PUMP_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HEADLAMPS_ADJ_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HEADLAMPS_ADJ_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance AC_RADIATOR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&AC_RADIATOR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance INSTRUMENT_CON_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&INSTRUMENT_CON_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ACCEL_CS_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ACCEL_CS_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ELECT_HANDBRAKE_EN_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ELECT_HANDBRAKE_EN_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_CONTACTOR_RELAY_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_CONTACTOR_RELAY_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_PARK_RELAY_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_PARK_RELAY_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_REV_RELAY_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_REV_RELAY_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_FWD_RELAY_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_FWD_RELAY_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_REGEN_RELAY_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_REGEN_RELAY_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_ELOCK_RELAY_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_ELOCK_RELAY_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance POS_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&POS_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance VCU_FAN_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&VCU_FAN_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance AUX_EFUSE_1_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&AUX_EFUSE_1_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance WIPER_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&WIPER_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance THROTTLE_POT_CS_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&THROTTLE_POT_CS_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LIGHTS_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LIGHTS_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance INFOTAINMENT_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&INFOTAINMENT_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance AUDIO_AMP_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&AUDIO_AMP_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance VACUUM_SENSOR_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&VACUUM_SENSOR_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance BRAKE_LIGHT_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&BRAKE_LIGHT_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HORN_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HORN_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DOOR_LOCK_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DOOR_LOCK_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance RIGHT_INDICATOR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&RIGHT_INDICATOR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HIGH_BEAM_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HIGH_BEAM_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LOW_BEAM_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LOW_BEAM_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance REV_LIGHT_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&REV_LIGHT_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ELEC_HANDBRAKE_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ELEC_HANDBRAKE_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance AUX_ANALOG1_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&AUX_ANALOG1_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance INT_ACCEL_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&INT_ACCEL_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance CIGARETTE_LIGHTER_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&CIGARETTE_LIGHTER_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance BUZZER_EN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&BUZZER_EN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_RELAY_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_RELAY_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MC_FAN_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MC_FAN_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance VEHICLE_SPEED_PWM_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&VEHICLE_SPEED_PWM_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance VEHICLE_RPM_PWM_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&VEHICLE_RPM_PWM_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance PWR_WINDOW_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&PWR_WINDOW_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance PWR_STEERING_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&PWR_STEERING_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LEFT_INDICATOR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LEFT_INDICATOR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ADC3_CS_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ADC3_CS_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance INPUTS_3V3_PWR_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&INPUTS_3V3_PWR_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance COMM_3V3_PWR_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&COMM_3V3_PWR_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance SENSOR_3V3_PWR_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&SENSOR_3V3_PWR_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance CABIN_LIGHT_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&CABIN_LIGHT_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ADC2_CS_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ADC2_CS_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ADC1_CS_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ADC1_CS_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance SPEED_SENSOR_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&SPEED_SENSOR_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance VACUUM_SENSOR_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&VACUUM_SENSOR_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance BRAKE_OIL_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&BRAKE_OIL_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance CHARGING_STARTED_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&CHARGING_STARTED_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance CHARGER_CONNECTED_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&CHARGER_CONNECTED_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance IGNI_POS2_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&IGNI_POS2_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance IGNI_POS1_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&IGNI_POS1_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ACC_PEDAL_SW_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ACC_PEDAL_SW_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HANDBRAKE_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HANDBRAKE_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance BRAKE_SW_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&BRAKE_SW_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DOOR_LOCK_PWR_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DOOR_LOCK_PWR_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance GEAR_SW1_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&GEAR_SW1_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance GEAR_SW2_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&GEAR_SW2_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance GEAR_SW3_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&GEAR_SW3_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance GEAR_SW4_IN_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&GEAR_SW4_IN_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_IO_5 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_IO_5); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_IO_6 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_IO_6); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of I2C_MASTER APP instance I2C_MASTER_0 */
	 init_status = (DAVE_STATUS_t)I2C_MASTER_Init(&I2C_MASTER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of I2C_MASTER APP instance I2C_MASTER_1 */
	 init_status = (DAVE_STATUS_t)I2C_MASTER_Init(&I2C_MASTER_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of CAN_NODE APP instance CAN_NODE_0 */
	 init_status = (DAVE_STATUS_t)CAN_NODE_Init(&CAN_NODE_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of CAN_NODE APP instance CAN_NODE_1 */
	 init_status = (DAVE_STATUS_t)CAN_NODE_Init(&CAN_NODE_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of TIMER APP instance TIMER_0 */
	 init_status = (DAVE_STATUS_t)TIMER_Init(&TIMER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of WATCHDOG APP instance WATCHDOG_0 */
	 init_status = (DAVE_STATUS_t)WATCHDOG_Init(&WATCHDOG_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of TIMER APP instance TIMER_1 */
	 init_status = (DAVE_STATUS_t)TIMER_Init(&TIMER_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of TIMER APP instance TIMER_2 */
	 init_status = (DAVE_STATUS_t)TIMER_Init(&TIMER_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance INTERRUPT_0 */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&INTERRUPT_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of UART APP instance UART_0 */
	 init_status = (DAVE_STATUS_t)UART_Init(&UART_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of CAN_NODE APP instance CAN_NODE_2 */
	 init_status = (DAVE_STATUS_t)CAN_NODE_Init(&CAN_NODE_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance CTS */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&CTS); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance RTS */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&RTS); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_IO_PWRKEY */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_IO_PWRKEY); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MODULE_4G_EN_OUT_D */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MODULE_4G_EN_OUT_D); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of SYSTIMER APP instance SYSTIMER_0 */
	 init_status = (DAVE_STATUS_t)SYSTIMER_Init(&SYSTIMER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of FATFS APP instance FATFS_0 */
	 init_status = (DAVE_STATUS_t)FATFS_Init(&FATFS_0); 
   }  
  return init_status;
} /**  End of function DAVE_Init */

