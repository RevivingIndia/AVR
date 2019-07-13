#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
int main()
{
DDRA=0x00;
DDRB=0xff;
while(1)
{
if((PINA&0b00000011)==0b00000011)
{
PORTB=0b00000101;
}
else if((PINA&0b00000011)==0b00000000)
{
PORTB=0b00000001;
}
else
{
PORTB=0b00000000;
}
}
return 0;
}
