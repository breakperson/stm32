#include "at24c02.h"
unsigned int number=0;
void IIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<3;		//使能外设IO
	GPIOB->CRL&=0X00FFFFFF;	//PB6/7推挽输出
	GPIOB->CRL|=0X33000000;	   
	GPIOB->ODR|=3<<6;     	//PB6,7 输出高
}
//产生IIC起始信号
//IIC起始信号产生的条件为：SCL为高电平时，SDA变为低电平
void IIC_Start(void)
{
	IIC_SDA_H;	  	//设置初始状态都为高电平  
	IIC_SCL_H;
	delay_us(4);
 	IIC_SDA_L;//起始信号，SDA由高变低
	delay_us(4);
	IIC_SCL_L; //钳住I2C总线，准备发送或接收数据
}	  
//产生IIC停止信号
//产生停止信号的条件为：SCL为高电平时，SDA由低变高
void IIC_Stop(void)
{
	IIC_SCL_L;
	IIC_SDA_L;//起始都是低电平
 	delay_us(4);
	IIC_SCL_H; //SCL变为高电平
	IIC_SDA_H;//SDA由低电平转变为高电平产生停止信号
	delay_us(4);							   	
}

//IIC主设备传输一个数据完成后，从设备产生应答信号，主设备等待应答信号到来
//产生条件：SCL为高电平期间，SDA时钟保持低电平。
//返回值：1，接收应答失败；0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_H;delay_us(1);	 //刚开始都为高电平
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)//读取数据线SDA的电平状态，如果持续低电平，则不会产生IIC_Stop信号，返回0
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();//如果在SCL高电平期间，SDA信号线产生了一定时间的高电平则认为应答失败
			return 1;
		}
	}
	IIC_SCL_L;//应答结束，时钟输出0
	return 0;  
} 
//产生ACK应答信号
//产生条件为：SCL为高电平期间，SDA始终保持低电平
void IIC_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//产生非应答信号
//产生条件为：SCL为高电平期间，SDA也出现了高电平  
void IIC_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}					 				     
//IIC发送一个字节  
//发送条件为：SCL为低电平期间准备好数据，SCL为高电平期间保持数据
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    IIC_SCL_L;//拉低时钟准备数据
    for(t=0;t<8;t++)
    {              
      if((txd&0x80)>>7) //从数据的最高位开始传输
      		IIC_SDA_H;	//如果为1，则数据位为1
      	else IIC_SDA_L; //不为1，数据位为0
        txd<<=1; 	  //逐个传输
		delay_us(2);   
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    
//读一个字节，ack=1时，发送ACK,ack=0，发送nACK
//读取条件为：SCL为高电平期间，读取SDA的电平状态
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
    for(i=0;i<8;i++ ) //逐个读8位
	{
        IIC_SCL_L; 
        delay_us(2);
		IIC_SCL_H; //SCL为高电平
        receive<<=1; //逐个移动数据位
        if(READ_SDA)receive++;   //如果SDA为高，则相应的数据为+1，反之为0
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//不产生ACK应答
    else
        IIC_Ack(); //产生ACK应答
    return receive;
}
unsigned char Read24c02 (unsigned char addres)
{
	unsigned char DATA;
	IIC_Start();
	IIC_Send_Byte(0xa0);
	IIC_Wait_Ack();
	IIC_Send_Byte(addres);	
	IIC_Wait_Ack();
  
   IIC_Start();
	IIC_Send_Byte(0xa1);
	IIC_Wait_Ack();
	DATA = IIC_Read_Byte(1);
	IIC_Ack();
	IIC_Stop();
	
	return DATA;		
}
void Write24c02 (unsigned char addres,unsigned char cmd)	
{	
	IIC_Start();
	IIC_Send_Byte(0xa0);
	IIC_Wait_Ack();
	IIC_Send_Byte(addres);	
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd);
	IIC_Wait_Ack();
	IIC_Stop();		
}
void write_number(void)
{
  number++;
	Write24c02(0x00,number);
}
void read_number(void)
{
	number=Read24c02(0x00);
}
