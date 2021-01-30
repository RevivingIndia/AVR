/*
 * SSD.c
 *
 * Created: 04-08-2019 21:09:43
 * Author : Praveen Kumar
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA =  0b11111111;
    while (1) 
    {
		PORTA = 0b00000000;  // 8
		_delay_ms(2000);
		PORTA = 0b01101011;  // 7
		_delay_ms(2000);
		PORTA = 0b00001100;  // 6
		_delay_ms(2000);
		PORTA = 0b01001100;  // 5
		_delay_ms(2000);
		PORTA = 0b11101000;  // 4
		_delay_ms(2000);
		PORTA = 0b01001010;  // 3
		_delay_ms(2000);
		PORTA = 0b00011010;  // 2
		_delay_ms(2000);
		PORTA = 0b11101011;  // 1
		_delay_ms(2000);	
    }
}

