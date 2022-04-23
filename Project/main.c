#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"
#include "stdio.h"
#include "ds1820.h"
#include "digital.h"
#include "beep.h"
#include "led.h"
#include "at24c02.h"
#include "cheng.h"
#include "servo.h"
#include "key.h"
#include "uart.h"
int main(void)
{
//static unsigned int cnt=0;
//	servo_init(11249,127);
	lcd_init();
//	cheng_init();
	ds_init();
//	beep_init();
//	led_init();
//	digital_init();
//	read_number();
//  key_init();
//	uart_init(72,9600);
	while(1)
	{
//    uart_IRQHandler();	
//    key();		
//		write_number();
//		breathing_led();
//		beep();
//		digital();
//		sprintf((char*)table[0],"hello word");
//		sprintf((char*)table[2],"%d",get_cheng());
		sprintf((char*)table[1],"%2.2f",get_ds()/100);
		lcd_flushed();
//    TIM_SetCompare2(TIM3,606+6.2*cnt);//270¶È10000~11000
//    TIM_SetCompare2(TIM3,606+6.2*(cnt+1480));//270¶È1480~1680 
//	  TIM_SetCompare2(TIM3,9800+6.5*cnt);//180¶È9800~11000   
	}
}
