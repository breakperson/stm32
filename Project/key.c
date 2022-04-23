#include "key.h"
void key_init(void)
{
	RCC->APB2ENR|1<<2;
	GPIOA->CRL&=0x00000000;
	GPIOA->CRL|=0x44443333;
}
void key(void)
{
  R1_L;R2_H;R3_H;R4_H;
	delay_us(400);
	if(!(key1))
	{
		delay_us(1000);
		if(!(key1))
		{
			
		}
	}
	if(!(key2))
	{
		delay_us(1000);
		if(!(key2))
		{
			
		}
	}
	if(!(key3))
	{
		delay_us(1000);
		if(!(key3))
		{
			
		}
	}
	if(!(key4))
	{
		delay_us(1000);
		if(!(key4))
		{
			
		}
	}
	R1_H;R2_L;R3_H;R4_H;
	delay_us(400);
	if(!(key1))
	{
		delay_us(1000);
		if(!(key1))
		{
			
		}
	}
	if(!(key2))
	{
		delay_us(1000);
		if(!(key2))
		{
			
		}
	}
	if(!(key3))
	{
		delay_us(1000);
		if(!(key3))
		{
			
		}
	}
	if(!(key4))
	{
		delay_us(1000);
		if(!(key4))
		{
			
		}
	}
	 R1_H;R2_H;R3_L;R4_H;
	delay_us(400);
	if(!(key1))
	{
		delay_us(1000);
		if(!(key1))
		{
			
		}
	}
	if(!(key2))
	{
		delay_us(1000);
		if(!(key2))
		{
			
		}
	}
	if(!(key3))
	{
		delay_us(1000);
		if(!(key3))
		{
			
		}
	}
	if(!(key4))
	{
		delay_us(1000);
		if(!(key4))
		{
			
		}
	}
	 R1_H;R2_H;R3_H;R4_L;
	delay_us(400);
	if(!(key1))
	{
		delay_us(1000);
		if(!(key1))
		{
			
		}
	}
	if(!(key2))
	{
		delay_us(1000);
		if(!(key2))
		{
			
		}
	}
	if(!(key3))
	{
		delay_us(1000);
		if(!(key3))
		{
			
		}
	}
	if(!(key4))
	{
		delay_us(1000);
		if(!(key4))
		{
			
		}
	}
}
