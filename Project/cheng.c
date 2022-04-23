#include "cheng.h"
unsigned long cheng(void)
{
	unsigned long count;
	unsigned char send;
	count=0;
	while(DTIN);
	for(send=0;send<24;send++)
	{
		SCLK_H;
		delay_us(50);
		count=count<<1;
		if(DTIN)
			count++;
		SCLK_L;
		delay_us(1);
	}
			SCLK_H;
		delay_us(50);
		count=count^0x800000;
		SCLK_L;
		delay_us(1);
	return(count);
}
void cheng_init(void)
{
	RCC->APB2ENR|=1<<3;
	GPIOB->CRL&=0xFFFFFF00;
	GPIOB->CRL|=0x00000083;
	SCLK_L;
	DT_L;
}
unsigned long get_cheng(void)
{
	unsigned long i=0,j=0;
	i+=cheng();
	i/=2;
	j=i/100;
	j=j*0.2105-17986;
	return j;
}
