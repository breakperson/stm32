#include "beep.h"
void beep_init(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRH&=0xFFFFFFF0;
	GPIOA->CRH|=0x00000003;
}
void beep(void)
{
  BEEP_H;
	delay_us(1000);
	BEEP_L;
	delay_us(1000);
}
