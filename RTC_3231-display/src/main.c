
#include <asf.h>

#include "driver_ds3231_interface.h"
#include "driver_ds3231.h"
#include "driver_ds3231_basic.h"
#include "I2C.h"
#include "LCD.h"

#define IICDEBUG 0
#define WRITETIME 1

int main (void)
{
	ds3231_time_t t;
	
	ds3231_basic_init();	
	i2c_init();
	initLCD();

#if WRITETIME
	ds3231_time_t setT;
	uint8_t res;
	
	setT.am_pm = DS3231_AM;
	setT.date = 8;
	setT.format = DS3231_FORMAT_24H;
	setT.hour = 20;
	setT.minute = 20;
	setT.month = 11;
	setT.second = 0;
	setT.week  = 3;
	setT.year = 2022;
	res = ds3231_basic_set_time(&setT);
	if (res != 0)
	{
		//(void)ds3231_basic_deinit();

		return 1;
	}
#endif

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