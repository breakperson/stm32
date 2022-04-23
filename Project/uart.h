#ifndef __uart_h
#define __uart_h
#include "stm32f10x.h"
extern unsigned int Receivedata;
void uart_IRQHandler(void);
void uart_init(unsigned int pcl,unsigned long bound);
#endif
