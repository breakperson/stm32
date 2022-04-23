#include "digital.h"
unsigned int BUFF[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void digital_init(void)
{
RCC->APB2ENR|=1<<2;
RCC->APB2ENR|=1<<3;
GPIOA->CRL&=0x000FFFFF;
GPIOA->CRL|=0x33300000;
GPIOB->CRL&=0x00000000;
GPIOB->CRL|=0x33333333;	
}
void digital(void)
{
	A0_L;A1_L;A2_L;GPIOB->ODR&=0xFF00;GPIOB->ODR|=BUFF[2];delay_us(1000);
	A0_H;A1_L;A2_L;GPIOB->ODR&=0xFF00;GPIOB->ODR|=BUFF[3];delay_us(1000);
	A0_L;A1_H;A2_L;GPIOB->ODR&=0xFF00;GPIOB->ODR|=BUFF[4];delay_us(1000);
	A0_H;A1_H;A2_L;GPIOB->ODR&=0xFF00;GPIOB->ODR|=BUFF[5];delay_us(1000);GPIOA->ODR&=0x00FF;
}

