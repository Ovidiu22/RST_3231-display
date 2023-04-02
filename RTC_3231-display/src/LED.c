/*
 * LED.c
 *
 * Created: 02.04.2023 08:42:13
 *  Author: lenovo
 */ 

#include "LED.h"

void init_LED(void)
{
	LED_DDR |= (1<<LED_pin); //set pins as outputs
}