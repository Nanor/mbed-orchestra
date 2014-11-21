#include <lpc17xx_rtc.h>

#include "rtc.h"

void RTC_init()
{
	RTC_Init(LPC_RTC);
	RTC_Cmd(LPC_RTC, ENABLE);
}

void RTC_set_time(int year, int month, int day, int hour, int minute, int second)
{
	RTC_TIME_Type time;
	
	time.SEC = second;
	time.MIN = minute;
	time.HOUR = hour;
	time.DOM = day;
	time.MONTH = month;
	time.YEAR = year;
	
	RTC_SetFullTime(LPC_RTC, &time);
}

uint32_t RTC_get_time()
{
	RTC_TIME_Type time;
	RTC_GetFullTime(LPC_RTC, &time);
	
	return(time.SEC + time.MIN*60 + time.HOUR*3600);
}


