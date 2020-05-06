 #include <avr/io.h>
// #define F_CPU 16000000
#include <inttypes.h>
#include <util/delay.h>
#include<avr/interrupt.h>



void USARTInit(uint16_t ubrr_value)
{

      
   UBRRL = ubrr_value;
   UBRRH = (ubrr_value>>8);
   
   //UCSRC|=(1<<URSEL);
   UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);


   UCSRB=(1<<RXEN)|(1<<TXEN);


}
unsigned char USARTReadChar()
{


   while(!(UCSRA & (1<<RXC)));



   return UDR;
}

void USARTWriteChar(char data)
{

   while(!(UCSRA & (1<<UDRE)));
   UDR=data;
}
void USART_StringTransmit(unsigned char s[])
{
int i=0;
while(s[i]!='\0')
{
USARTWriteChar(s[i]);
i++;
}
}

void main()
{
DDRB=255;

   unsigned char data;
PORTB=0b01010101;

_delay_ms(1000);
 USARTInit(51);  
_delay_ms(6000);

while(1)
{
int c=PINA&0b00000001;
 USARTWriteChar('A');
	  _delay_ms(100);
	  USARTWriteChar('T');
	  _delay_ms(500);
      USARTWriteChar('\n\r');
	  
	  _delay_ms(500);

        USARTWriteChar('A');
		USARTWriteChar('T');
		USARTWriteChar('+');
		USARTWriteChar('C');
		USARTWriteChar('M');
		USARTWriteChar('G');
        USARTWriteChar('F');
		USARTWriteChar('=');
		USARTWriteChar('1');
		USARTWriteChar('\n\r');


_delay_ms(2000);


if(c==0b00000001)
{
PORTB=~PORTB;
_delay_ms(1000);

                USARTWriteChar('A');
		USARTWriteChar('T');
		USARTWriteChar('+');
		USARTWriteChar('C');
		USARTWriteChar('M');
		USARTWriteChar('G');
                USARTWriteChar('S');
		USARTWriteChar('=');
		USARTWriteChar('"');
		USARTWriteChar('+');
		USARTWriteChar('9');
		USARTWriteChar('1');
		USARTWriteChar('9');
        	USARTWriteChar('7');
		USARTWriteChar('1');
		USARTWriteChar('6');
		USARTWriteChar('8');
		USARTWriteChar('1');
		USARTWriteChar('7');
		USARTWriteChar('7');
        	USARTWriteChar('1');
		USARTWriteChar('0');
	    USARTWriteChar('"');
	    USARTWriteChar('\n\r');
		_delay_ms(1000);
USART_StringTransmit(" Alert! Motion has been detected   ");
USARTWriteChar(26);
USARTWriteChar('\n\r');
}


}		
}	










