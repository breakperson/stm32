#ifndef __beep_h
#define __beep_h
#include "delay.h"
#include "stm32f10x.h"
#define BEEP_H GPIOA->ODR|=0x0100
#define BEEP_L GPIOA->BRR|=0x0100
void beep(void);
void beep_init(void);
#endif
