/*
 * Vcu_Out.h
 *
 *  Created on: 27-Jun-2023
 *      Author: Suchit Sawant
 */

#ifndef VCU_OUT_VCU_OUT_H_
#define VCU_OUT_VCU_OUT_H_

#include "DAVE.h"
//#include "VCU_PROCESS/Vcu_Process.h"
#endif /* VCU_OUT_VCU_OUT_H_ */


void OutPutAction_Update(void);

void ALL_CONDITION_ON(void);
void ALL_CONDITION_OFF(void);

void ignition1_d_on(void);
void ignition1_d_off(void);

void ignition2_d_on(void);
void ignition2_d_off(void);

void State_1(void);

void State_2(void);

void VcuOut_IoExp_U24(void);
void VcuOut_IoExp_U25(void);
void VcuOut_IoExp_U38(void);
void VcuOut_IoExp_U45(void);

void Lights_on_off(void);
void State2_Lights(void);
void VcuOut_MotorController(void);
void VcuOut_MotorController_off(void);

void Can_Outputs_State1(void);
void Can_Outputs_State2(void);

void all_direct_controlled_relay_off(void);

void charger_tx(void);
