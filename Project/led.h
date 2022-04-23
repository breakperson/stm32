#ifndef __led_h
#define __led_h
#include "stm32f10x.h"
#define LED_H GPIOA->ODR|=0x0200
#define LED_L GPIOA->BRR|=0x0200
void breathing_led(void);
void led_init(void);
#endif
