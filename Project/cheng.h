#ifndef __cheng_h
#define __cheng_h
#include "stm32f10x.h"
#include "delay.h"
#define SCLK_H GPIOB->ODR|=0x01
#define DT_H GPIOB->ODR|=0x02
#define SCLK_L GPIOB->ODR&=0xFE
#define DT_L GPIOB->ODR&=0xFD
#define DTIN GPIOB->IDR&1<<1
unsigned long cheng(void);
void cheng_init(void);
unsigned long get_cheng(void);
#endif
