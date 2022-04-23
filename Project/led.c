#include "led.h"
void led_init(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRH&=0xFFFFFF0F;
	GPIOA->CRH|=0x00000030;	
}
//led正极接PA9负极接地
void breathing_led(void)
{
static unsigned int i=0,j=0,plot=0;
	for(i=0;i<1500;i++)
	{
		if(i<j)
		LED_H;
		else
		LED_L;
	}
	if(j==0||plot==0)
	{
		j++;
		plot=0;
	}
	if(j==1500||plot==1)
	{
		j--;
		plot=1;
	}
}
