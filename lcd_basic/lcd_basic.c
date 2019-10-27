 
#include<avr/io.h>
#include<util/delay.h>

#define lcd PORTC
#define rs PC0
#define rw PC1
#define en PC2
//void lcd_init();
 void lcd_cmd(unsigned char com);
void lcd_data(unsigned char data);
void lcd_string(unsigned char *str);
//------------------------------------------------------------------------

void main()
{
  DDRC=0xFF;
 
  lcd_cmd(0x02);//home location
  lcd_cmd(0x28);//2x16 lcd 4bit mode
  lcd_cmd(0x0C);//dispy on cursor blink
  lcd_cmd(0x06);//increament

 
  while(1)
  {
    lcd_cmd(0x80);
   lcd_data('I');
   lcd_cmd(0xc0);
   lcd_string("praveen ");	
  }
}
void lcd_cmd(unsigned char com)
{
  //for command rs=0,rw=0,en=1,en=0
 char cmd1;
cmd1=(com&(0xF0));//upper 4 bit data
lcd=cmd1;
lcd&=~(1<<rs);//rs=0
lcd&=~(1<<rw);//rw=0
lcd|=(1<<en);//en=1
_delay_ms(1);
lcd&=~(1<<en);


cmd1=((com<<4)&(0xF0));//upper 4 bit data
lcd=cmd1;
lcd&=~(1<<rs);//rs=0
lcd&=~(1<<rw);//rw=0
lcd|=(1<<en);//en=1
_delay_ms(1);
lcd&=~(1<<en);
}
void lcd_data(unsigned char data)
{
  unsigned char data1;
  data1=(data&(0xF0));// upper 4 bit
  lcd=data1;
  lcd|=(1<<rs); //rs=1
  lcd&=~(1<<rw);//rw=0
  lcd|=(1<<en);//en=1
  
  _delay_ms(1);
  lcd&=~(1<<en);//en=0

  data1=((data<<4)&(0xF0));//lower 4 bit data
lcd=data1;
lcd|=(1<<rs);//rs=1
lcd&=~(1<<rw);//rw=0
lcd|=(1<<en);//en=1
_delay_ms(1);
lcd&=~(1<<en);

}
//--------------------------------------------------------------
void lcd_string(unsigned char *str)
{
   int i=0;
   while(str[i]!='\0')
    {
	  lcd_data(str[i]);
	  i++;
	}
}




//----------------------------------------------------------------------------
