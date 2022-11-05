
#include <asf.h>
#include "driver_ds3231.h"
#include "driver_ds3231_interface.h"
#include "I2C.h"
#include "LCD.h"

#define IICDEBUG 0
#define WRITETIME 0		//1 - write time; 0 - read time
#define READTIME 1

int main (void)
{
	initLCD();
	i2c_init();
	//ds3231_basic_init();

	
#if WRITETIME
	ds3231_time_t setTime;
	
	ds3231_basic_get_time(ds3231_time_t &setTime);
	
#if 0	
	setTime.hour = 11;
	setTime.minute = 10;
	setTime.second = 7;

	/* Initialize time */	
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_SECOND);
	i2c_write(a_ds3231_hex2bcd(setTime.second));
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_MINUTE);
	i2c_write(a_ds3231_hex2bcd(setTime.minute));
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
 	i2c_write(DS3231_REG_HOUR);
 	i2c_write(a_ds3231_hex2bcd(setTime.hour));
#endif
#endif


#if !WRITETIME // Read time

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

}