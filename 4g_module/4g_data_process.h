
#include "pb_encode.h"
#include "pb_common.h"
#include "V26_10sec_fleet.pb.h"


void Process_4G_Event_Data(void);
void epoch_time(void);

extern vcu_fleet_fleet_10_sec TD1;
extern uint8_t Eventbuffer_4Gcomm[512];

uint32_t CalOdometer();
