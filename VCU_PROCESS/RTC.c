
#include "VCU_PROCESS/Vcu_Process.h"
#include "Vcu_Config.h"

#include "xmc_rtc.h"
#include <time.h>
void RTC_init(void)
{

	RTC_STATUS_t status_r = RTC_STATUS_FAILURE;
	RTC_Stop();

    status_r =  RTC_SetTime(&timeval);

    if(status_r == RTC_STATUS_SUCCESS)
    {
 	 RTC_Start();
    }
}
