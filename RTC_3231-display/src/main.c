
#include <asf.h>
#include "I2C.h"
#include "LCD.h"
#include "driver_ds3231.h"

#define WRITE 0
#define IICDEBUG 0
#define READTIME 1

int main (void)
{
	initLCD();
	i2c_init();

	uint8_t minutes = 0;
	uint8_t seconds = 0;
	ds3231_time_t myTime;
	
#if WRITE
	/* Initialize clock */	
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_SECOND);
	i2c_write(seconds);
	i2c_write(DS3231_REG_MINUTE);
	i2c_write(minutes);
	
#endif

#if READTIME
		
	while(1)
	{
			i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
			i2c_write(DS3231_REG_SECOND);
			/* Send START condition with SLA+R */
			i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
			/* Receive data */
			myTime.second = i2c_readNak();
			
			i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
			i2c_write(DS3231_REG_MINUTE);
			/* Send START condition with SLA+R */
			i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
			/* Receive data */
			myTime.minute = i2c_readNak();
			
			displayLCD_main(1, "Current time", NONE, "NONE");
			displayLCD_main(2, "Minute: ", myTime.minute, "NONE");
			displayLCD_main(3, "Second:", myTime.second, "NONE");
	}

#endif

	i2c_stop();
	
	
}
