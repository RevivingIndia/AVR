

#define lcd PORTB
#define rs PB0
#define rw PB1
#define en PB2
#define F_CPU 1000000UL

#include<avr/io.h>
#include<util/delay.h>
//-------------------------
void lcd_init();
void lcd_cmd(unsigned char com);
void lcd_data(unsigned char data);
void lcd_num(unsigned int value);

void ADC_init();
unsigned int adc_read(unsigned int ch);

//--------main-----------------------------------

int main(void)
{
	DDRA=0x00;
	DDRB=0XFF;   ////LCD OUTP
	lcd_init();
	ADC_init();

	unsigned int value;
	while(1)
	{
		_delay_ms(200);
		lcd_cmd(0x80);
		lcd_string("ADC value=    ");
		lcd_cmd(0xc0);
		lcd_data(48);
		value=adc_read(0);
		lcd_cmd(0xc3);
		lcd_num(value);
	}
}


void ADC_init(void)
{
	ADMUX|=(1<<REFS0);//0B=01000000
	ADCSRA=(1<<ADEN)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//0b10100111
}

unsigned int adc_read(unsigned int cha)
{
	unsigned int channel;
	channel=cha&0b00000111;
	ADMUX|=channel;
	ADCSRA|=(1<<ADSC );
	while(!(ADCSRA&(1<<ADIF)))//ADC CHECKING
	{
	}
	ADCSRA|=(1<<ADIF);
	return ADC;
}


void lcd_init()
{
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x06);
}
void lcd_cmd(unsigned char com)
{
	unsigned char cmd1;
	cmd1=(com&(0XF0));//UPPER 4 BIT DATA
	lcd=cmd1;
	lcd&=~(1<<rs);//rs 0
	lcd&=~(1<<rw);//rw 0
	lcd|=(1<<en);
	_delay_ms(1);
	lcd&=~(1<<en);// en 0

	cmd1=((com<<4)&(0xF0));//LOWER 4 BIT DATA
	lcd=cmd1;
	lcd&=~(1<<rs);//rs 0
	lcd&=~(1<<rw);//rw 0
	lcd|=(1<<en);
	_delay_ms(1);
	lcd&=~(1<<en);// en 0
}
void lcd_data(unsigned char data)
{
	unsigned char data1;
	data1=(data&(0XF0));//UPPER 4 BIT DATA
	lcd=data1;
	lcd|=(1<<rs);//rs 1
	lcd&=~(1<<rw);//rw 1
	lcd|=(1<<en);//en 0
	_delay_ms(1);
	lcd&=~(1<<en);// en=0

	data1=((data<<4)&(0XF0));
	lcd=data1;
	lcd|=(1<<rs);//rs 1
	lcd&=~(1<<rw);//rw 0
	lcd|=(1<<en);
	_delay_ms(1);
	lcd&=~(1<<en);// en 0
}
//------------------------------------
void lcd_string(unsigned char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}

void lcd_num(unsigned int value)
{
	unsigned int rem;
	lcd_cmd(0x04);
	while(value!=0)
	{
		rem=value%10;
		lcd_data(rem+48);
		value=value/10;
	}
	lcd_cmd(0x06);
}

