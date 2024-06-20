/*
 * Vcu_Process.h
 *
 *  Created on: 27-Jun-2023
 *      Author: Suchit Sawant
 */

#ifndef VCU_PROCESS_VCU_PROCESS_H_
#define VCU_PROCESS_VCU_PROCESS_H_

//#include "Vcu_Config.h"

#endif /* VCU_PROCESS_VCU_PROCESS_H_ */

void Process_VcuOutputs_Update(void);
void Process_State1_Inputs(void);
void Process_State2_Inputs(void);
void Process_Io_exp_U24(void);
void Process_Io_exp_U25(void);
void Process_vehicleDrive_Inputs(void);
void Process_vehicleDrive_Inputs_off(void);
void Process_ig2_lights(void);
void Process_ig2_lights_off(void);
void all_Ig1_Inputs_off(void);
void Process_cluster_indicators(void);
void cluster_indicators_off(void);

void init_hw(void);
