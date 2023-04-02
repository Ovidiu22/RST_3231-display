/*
 * LED.h
 *
 * Created: 02.04.2023 08:42:30
 *  Author: lenovo
 */ 
#include <avr/io.h>

#ifndef LED_H_
#define LED_H_

#define LED_DDR		DDRD
#define LED_PORT	PORTD
#define LED_pin		PIND6

#define set_LED_high	LED_PORT |= (1<<LED_pin)
#define turnOff_LED		LED_PORT &= ~(1<<LED_pin)

void init_LED(void);

#endif /* LED_H_ */