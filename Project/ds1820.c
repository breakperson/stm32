#include "ds1820.h"
void ds_rst(void)
{
	DS_L;
	delay_us(450);
	DS_H;
	delay_us(10);
}
unsigned char read_ds(void)
{
	unsigned char i=0,j=0,k=0;
	for(i=1;i<=8;i++)
	{
		DS_L;
		delay_us(1);
		DS_H;
		delay_us(10);
		if(DS)
			k=1;
		else
			k=0;
		delay_us(30);
		j=((k<<7)|(j>>1));
	}
	return j;
}
void write_ds(unsigned char dat)
{
	unsigned char send,i;
	for(i=1;i<=8;i++)
	{
		send=dat&0x01;
		dat>>=1;
		if(send)
		{
			DS_L;
			delay_us(1);
			DS_H;
			delay_us(45);
		}
		else
			{
			DS_L;
			delay_us(45);
			DS_H;
			delay_us(1);
		  }
	}
}
float get_ds(void)
{
	unsigned char tmp=0,TH=0,TL=0;
	short tem;
  ds_rst();
	delay_us(750);
	write_ds(0xcc);
	write_ds(0x44);
	ds_rst();
	delay_us(750);
	write_ds(0xcc);
	write_ds(0xbe);
	TL=read_ds();
	TH=read_ds();
	if(TH>7)
	{
		TH=~TH;
		TL=~TL;
		tmp=0;
	}
	else
		tmp=1;
	  tem=TH;
   	tem<<=8;
    tem+=TL;
	  tem=(float)tem*6.25;
	if(tmp)
		return tem;
	else
		return -tem;
}
void ds_init(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0xFFF0FFFF;
	GPIOA->CRL|=0x00030000;
	DS_H;
	ds_rst();
}
