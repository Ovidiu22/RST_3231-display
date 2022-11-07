
#include <asf.h>

#include "driver_ds3231_interface.h"
#include "driver_ds3231.h"
#include "driver_ds3231_basic.h"
#include "I2C.h"
#include "LCD.h"

#define IICDEBUG 0
#define WRITETIME 0		//1 - write time; 0 - read time
#define READTIME 1

int main (void)
{
	i2c_init();
	initLCD();

	
#if READTIME
	ds3231_time_t t;
	ds3231_basic_init();
	
 	while(1)
 	{
		ds3231_basic_get_time(&t);
		displayLCD_main(1, "Year:", t.year, "NONE");
		displayLCD_main(2, "Hour:", t.hour, "NONE");
		displayLCD_main(3, "Minute:", t.minute, "NONE");
		displayLCD_main(4, "Second:", t.second, "NONE");
		
	 }
#endif


#if WRITETIME // Read time

	ds3231_time_t myTime;
	while(1)
	{
		i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_SECOND);
		/* Send START condition with SLA+R */
		i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
		/* Receive data */
		myTime.second = a_ds3231_bcd2hex(i2c_readNak());
			
		i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_MINUTE);
		/* Send START condition with SLA+R */
		i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
		/* Receive data */
		myTime.minute = a_ds3231_bcd2hex(i2c_readNak());
			
 		i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
 		i2c_write(DS3231_REG_HOUR);
 		/* Send START condition with SLA+R */
 		i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
 		/* Receive data */
 		myTime.hour = a_ds3231_bcd2hex(i2c_readNak());
	
	
		//displayLCD_main(1, "Current time", NONE, "NONE");
		displayLCD_main(2, "Hour: ", myTime.hour, "NONE");
		displayLCD_main(3, "Minute:", myTime.minute, "NONE");
		displayLCD_main(4, "Second:", myTime.second, "NONE");
		
	}

#endif

	

	return 0;
}