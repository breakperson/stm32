#include "servo.h"

void servo_init(unsigned int arr,unsigned int psc)
{
	RCC->APB1ENR|=1<<1;
	RCC->APB2ENR|=1<<2;
  GPIOA->CRL&=0x0fffffff;
	GPIOA->CRL|=0xb0000000;
	GPIOA->ODR|=1<<7;
	TIM3->ARR=arr;
	TIM3->PSC=psc;
	TIM3->CCMR1|=7<<12;
	TIM3->CCMR1|=1<<1;
	TIM3->CCER|=1<<4;
	TIM3->CR1|=0x0081;
}
