/*
 * led.c
 *
 * Created: 24-07-2019 20:20:48
 * Author : Praveen Kumar
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRC = 0xff;
    while (1) 
    {
		PORTC = 0x0f;
		_delay_ms(1000);
		PORTC = 0xf0;
		_delay_ms(1000);
    }
}

