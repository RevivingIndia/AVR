
#include<avr/io.h>
#include<util/delay.h>



void USARTInit(uint16_t ubrr_value)
{
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value>>8);
	
	//UCSRC|=(1<<URSEL);
	UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);


	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);

}

unsigned char USARTReadChar()
{


	while(!(UCSRA & (1<<RXC)));

	

	return UDR;
}

void USARTWriteChar(char data)
{

	while(!(UCSRA & (1<<UDRE)))
	;
	

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
	DDRD=255;

	char Recieved_command;

	_delay_ms(50);

	USARTInit(51);  // 103 for 16 Mhz 51 for 8mhz
	
	while(1)
	{
		Recieved_command=USARTReadChar();

		if((Recieved_command=='F')||(Recieved_command=='f'))
		{
			USART_StringTransmit("\n Move Forward ");
			// PORTB=0b00001001;
			PORTB=0xff;
		}
		
		if((Recieved_command=='B')||(Recieved_command=='b'))
		{
			USART_StringTransmit("\n Move Backward ");
			//PORTB=0b00000110;
			PORTB=0xf0;
		}

		if((Recieved_command=='L')||(Recieved_command=='l'))
		{
			USART_StringTransmit("\n Turn Left ");
			PORTB=0b00001000;
		}

		if((Recieved_command=='R')||(Recieved_command=='r'))
		{
			USART_StringTransmit("\n Turn Right ");
			PORTB=0b00000001;
		}


		if((Recieved_command=='S')||(Recieved_command=='s'))
		{
			USART_StringTransmit("\n STOP!!  ");
			PORTB=0b00000000;
		}

	}
}
