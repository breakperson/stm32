#ifndef __key_h
#define __key_h
#include "stm32f10x.h"
#include "delay.h"
#define R1_H GPIOA->ODR|=0x01
#define R2_H GPIOA->ODR|=0x02
#define R3_H GPIOA->ODR|=0x04
#define R4_H GPIOA->ODR|=0x08
#define R1_L GPIOA->BRR|=0x01
#define R2_L GPIOA->BRR|=0x02
#define R3_L GPIOA->BRR|=0x04
#define R4_L GPIOA->BRR|=0x08
#define key1 GPIOA->IDR&1<<4
#define key2 GPIOA->IDR&1<<5
#define key3 GPIOA->IDR&1<<6
#define key4 GPIOA->IDR&1<<7
void key_init(void);
void key(void);
#endif
