/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	09th November 2022	 ***/
/*******************************/

#include <asf.h>
#include "driver_ds3231_interface.h"
#include "driver_ds3231.h"
#include "driver_ds3231_basic.h"
#include "I2C.h"
#include "LCD.h"

#define WRITETIME 0

int main (void)
{
	ds3231_time_t t;
	
	ds3231_basic_init();	
	initLCD();

#if WRITETIME
	/* Set time */
	ds3231_time_t setT;
	
	setT.am_pm = DS3231_PM;
	setT.date = 9;
	setT.format = DS3231_FORMAT_24H;
	setT.hour = 18;
	setT.minute = 39;
	setT.month = 11;
	setT.second = 0;
	setT.week  = 4;
	setT.year = 2022;
	
	/* Write time to module */
	ds3231_basic_set_time(&setT);

#endif
	
	/* Read and disply current time */
 	while(1)
 	{
		ds3231_basic_get_time(&t);
		displayLCD_main(1, "Date:", t.date, "NONE");
		displayLCD_main(2, "Hour:", t.hour, "NONE");
		displayLCD_main(3, "Minute:", t.minute, "NONE");
		displayLCD_main(4, "Second:", t.second, "NONE");
	 }
	return 0;
}
