/*
 * RGB.c
 *
 * Created: 12-08-2019 10:21:25
 * Author : Praveen Kumar
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0b11111111;
	
    while (1) 
    {
		PORTD = 0b00000001;
		_delay_ms(1000);
		PORTD = 0b00000010;
		_delay_ms(1000);
		PORTD = 0b00000100;
		_delay_ms(1000);
    }
}

