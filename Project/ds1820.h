#ifndef __ds1820_h
#define __ds1820_h
#include "delay.h"
#include "stm32f10x.h"
#define DS_H GPIOA->ODR|=0x10
#define DS_L GPIOA->BRR|=0x10
#define DS   GPIOA->IDR&1<<4
void ds_rst(void);
extern unsigned char read_ds(void);
void write_ds(unsigned char dat);
float get_ds(void);
void ds_init(void);
#endif
