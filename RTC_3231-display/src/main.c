
#include <asf.h>
#include "driver_ds3231.h"
#include "I2C.h"
#include "LCD.h"


#define WRITE 0
#define IICDEBUG 0
#define READTIME 1
#define ALARM 1

int main (void)
{
	initLCD();
	i2c_init();

	ds3231_time_t myTime;
	ds3231_time_t setTime;
	
	setTime.hour = 11;
	setTime.minute = 10;
	setTime.second = 7;
	
#if WRITE

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

#if ALARM
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_CONTROL);
	i2c_write(0x5);

	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_SECOND);
	i2c_write(0x5);

	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_MINUTE);
	i2c_write(128);
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_HOUR);
	i2c_write(128);
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_WEEK);
	i2c_write(128);
#endif

#if READTIME
		
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
	
	#if ALARM	
		/* Receive data */
		i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_STATUS);
		/* Send START condition with SLA+R */
		i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
		/* Receive data */
		uint8_t st_reg = i2c_readNak();
		if (st_reg & 0x01)
		{
			uint8_t temp_st_reg = st_reg & 0xFE;
			i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
			i2c_write(DS3231_REG_STATUS);
			i2c_write(temp_st_reg);
		}
		i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_CONTROL);
		/* Send START condition with SLA+R */
		i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
		/* Receive data */
		uint8_t ctrl_reg = i2c_readNak();
		displayLCD_main(1, "Ctrl register: ", ctrl_reg, "NONE");
		
	#endif
		//displayLCD_main(1, "Current time", NONE, "NONE");
		displayLCD_main(2, "Hour: ", myTime.hour, "NONE");
		displayLCD_main(3, "Minute:", myTime.minute, "NONE");
		displayLCD_main(4, "Second:", myTime.second, "NONE");
		
	}

#endif

#if 0
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_SECOND);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M1 = i2c_readNak();

	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_MINUTE);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M2 = i2c_readNak();
	
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_HOUR);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M3 = i2c_readNak();
	
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_WEEK);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M4 = i2c_readNak();
	
	displayLCD_main(1, "A1M1: ", A1M1, "NONE");
	displayLCD_main(2, "A1M2: ", A1M2, "NONE");
	displayLCD_main(3, "A1M3: ", A1M3, "NONE");
	displayLCD_main(4, "A1M4: ", A1M4, "NONE");
#endif
}
