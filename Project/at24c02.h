#ifndef __iic_h
#define __iic_h
#include "delay.h"
#include "stm32f10x.h"
#define IIC_SDA_H GPIOB->ODR|=0x40
#define IIC_SCL_H GPIOB->ODR|=0x80
#define IIC_SDA_L GPIOB->BRR|=0x40
#define IIC_SCL_L GPIOB->BRR|=0x80
#define READ_SDA GPIOB->IDR&1<<6
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(unsigned char ack);
void read_number(void);
void write_number(void);
#endif
