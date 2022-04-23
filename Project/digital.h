#ifndef __digital_h
#define __digital_h
#include "stm32f10x.h"
#include "delay.h"
#define A0_H GPIOA->ODR|=0x20
#define A1_H GPIOA->ODR|=0x40
#define A2_H GPIOA->ODR|=0x80
#define A0_L GPIOA->BRR|=0x20
#define A1_L GPIOA->BRR|=0x40
#define A2_L GPIOA->BRR|=0x80
void digital_init(void);
void digital(void);
#endif
