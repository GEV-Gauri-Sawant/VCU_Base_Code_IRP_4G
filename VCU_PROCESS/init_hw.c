/*
 * init_hw.c
 *
 *  Created on: 09-Aug-2023
 *      Author: Suchit Sawant
 */

#include "DAVE.h"

void init_hw(void)
{
	DAVE_STATUS_t init_status = DAVE_STATUS_SUCCESS;

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

}
