#include "delay.h"
void delay_us(unsigned int i)
{
	i*=10;
	while(--i);
}
void delay_ms(unsigned long i)
{
	i*=12000;
	while(--i);
}
