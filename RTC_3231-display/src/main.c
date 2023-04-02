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
#include "LED.h"

#define WRITETIME 1
#define LCDPRESENT 0
int main (void)
{
	ds3231_basic_init();
#if LCDPRESENT
	initLCD();
	ds3231_time_t t;
#else
	init_LED();
#endif	
	

#if WRITETIME
	/* Set time */
	ds3231_time_t setT;
	uint8_t setTime_b = 0;
	setT.am_pm = DS3231_PM;
	setT.date = 02;		/* Between 1 - 31 */
	setT.format = DS3231_FORMAT_24H;
	setT.hour = 23;		/* Between 0 - 23 / 0-11 in case of 12h time format */
	setT.minute = 56;	/* Between 0 - 59 */
	setT.month = 04;	/* Between 1 - 12 */
	setT.second = 0;	/* Between 0 - 59 */
	setT.week  = 1;		/* Between 1 - 7 */
	setT.year = 2023;	/* Between 1900 - 2190 */
	
	/* Write time to module */
	ds3231_basic_set_time(&setT);
	if (!setTime_b)
	{
#if LCDPRESENT
		displayLCD_main(1, "Time set successfully.", NONE, "NONE");
#else
		set_LED_high; 
		_delay_ms(100); 
		turnOff_LED;
#endif
	}
	else
	{
#if LCDPRESENT
		displayLCD_main(1, "Time set failed.", NONE, "NONE");
#else
		set_LED_high; 
		_delay_ms(1000); 
		turnOff_LED; 
#endif
	}

#endif

#if LCDPRESENT	
	/* Read and display current time */
 	while(1)
 	{
		ds3231_basic_get_time(&t);
		displayLCD_main(2, "Hour:", t.hour, "NONE");
		displayLCD_main(3, "Minute:", t.minute, "NONE");
		displayLCD_main(4, "Second:", t.second, "NONE");
	 }
#endif
	return 0;
}

