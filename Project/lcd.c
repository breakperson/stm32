#include "lcd.h"
unsigned char table[][16]={"                ","                ","                ","                "};
void write_lcd_zijie(unsigned char zijie)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(zijie&0x80)
		{
			RW_H;
		}
		else
		RW_L;
		E_H;
		delay_us(10);
		E_L;
		delay_us(10);
		zijie<<=1;
	}
}
void write_cmd(unsigned char cmd)
{
write_lcd_zijie(0xf8);
write_lcd_zijie(cmd&0xf0);
write_lcd_zijie(cmd<<4);	
}
void write_data(unsigned char data)
{
write_lcd_zijie(0xfa);
write_lcd_zijie(data&0xf0);
write_lcd_zijie(data<<4);	
}
void lcd_xy(unsigned char x,unsigned char y)
{
switch(y)
{
	case 0:write_cmd(0x80+x);break;
	case 1:write_cmd(0x90+x);break;
	case 2:write_cmd(0x88+x);break;
	case 3:write_cmd(0x98+x);break;
}
}
void lcd_flushed(void)
{
	unsigned char i,j;
	for(i=0;i<4;i++)
	{
		lcd_xy(0,i);
		for(j=0;j<16;j++)
		{
			if((table[i][j])!=0)
			{
				write_data(table[i][j]);
			}
		}
	}
}
void lcd_init(void)
{

RCC->APB2ENR|=1<<2;
GPIOA->CRL&=0xFFFF0000;
GPIOA->CRL|=0x00003333;
RW_L;
RS_L;
E_L;
PSB_L;

RS_H;
write_cmd(0x01);
write_cmd(0x0c);	
}
