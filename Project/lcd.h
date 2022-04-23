#ifndef __lcd_h
#define __lcd_h
#include "stm32f10x.h"
#include "delay.h"
#define RS_H  GPIOA->ODR|=0x01
#define RW_H  GPIOA->ODR|=0x02
#define E_H   GPIOA->ODR|=0x04
#define PSB_H GPIOA->ODR|=0x08
#define RS_L  GPIOA->BRR|=0x01
#define RW_L  GPIOA->BRR|=0x02
#define E_L   GPIOA->BRR|=0x04
#define PSB_L GPIOA->BRR|=0x08
extern unsigned char table[][16];
void write_lcd_zijie(unsigned char zijie);
void write_cmd(unsigned char cmd);
void write_data(unsigned char data);
void lcd_xy(unsigned char x,unsigned char y);
void lcd_flushed(void);
void lcd_init(void);
#endif
