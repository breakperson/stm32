#include "uart.h"
unsigned int Receivedata;
void uart_init(unsigned int pcl,unsigned long bound)
{
	float temp;
	unsigned int xiaoshu;
	unsigned int zhengshu;
	temp=(float)(pcl*1000000)/(bound*16);
	zhengshu=temp;
	xiaoshu=(temp-zhengshu)*16;
	zhengshu<<=4;
	zhengshu+=xiaoshu;
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<14;
	GPIOA->CRH&=0xFFFFF00F;
	GPIOA->CRH|=0x000008b0;
	USART1->BRR=zhengshu;
	USART1->CR1|=0x200C;
	USART1->CR1|=1<<5;	
}
void uart_IRQHandler(void)
{
	if(USART1->SR&(1<<5))
	{
		Receivedata=USART1->DR;
		if(Receivedata==1)
		{
			GPIOB->ODR&=0x00;
		}
	}
}
