#include "at24c02.h"
unsigned int number=0;
void IIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<3;		//ʹ������IO
	GPIOB->CRL&=0X00FFFFFF;	//PB6/7�������
	GPIOB->CRL|=0X33000000;	   
	GPIOB->ODR|=3<<6;     	//PB6,7 �����
}
//����IIC��ʼ�ź�
//IIC��ʼ�źŲ���������Ϊ��SCLΪ�ߵ�ƽʱ��SDA��Ϊ�͵�ƽ
void IIC_Start(void)
{
	IIC_SDA_H;	  	//���ó�ʼ״̬��Ϊ�ߵ�ƽ  
	IIC_SCL_H;
	delay_us(4);
 	IIC_SDA_L;//��ʼ�źţ�SDA�ɸ߱��
	delay_us(4);
	IIC_SCL_L; //ǯסI2C���ߣ�׼�����ͻ��������
}	  
//����IICֹͣ�ź�
//����ֹͣ�źŵ�����Ϊ��SCLΪ�ߵ�ƽʱ��SDA�ɵͱ��
void IIC_Stop(void)
{
	IIC_SCL_L;
	IIC_SDA_L;//��ʼ���ǵ͵�ƽ
 	delay_us(4);
	IIC_SCL_H; //SCL��Ϊ�ߵ�ƽ
	IIC_SDA_H;//SDA�ɵ͵�ƽת��Ϊ�ߵ�ƽ����ֹͣ�ź�
	delay_us(4);							   	
}

//IIC���豸����һ��������ɺ󣬴��豸����Ӧ���źţ����豸�ȴ�Ӧ���źŵ���
//����������SCLΪ�ߵ�ƽ�ڼ䣬SDAʱ�ӱ��ֵ͵�ƽ��
//����ֵ��1������Ӧ��ʧ�ܣ�0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_H;delay_us(1);	 //�տ�ʼ��Ϊ�ߵ�ƽ
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)//��ȡ������SDA�ĵ�ƽ״̬����������͵�ƽ���򲻻����IIC_Stop�źţ�����0
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();//�����SCL�ߵ�ƽ�ڼ䣬SDA�ź��߲�����һ��ʱ��ĸߵ�ƽ����ΪӦ��ʧ��
			return 1;
		}
	}
	IIC_SCL_L;//Ӧ�������ʱ�����0
	return 0;  
} 
//����ACKӦ���ź�
//��������Ϊ��SCLΪ�ߵ�ƽ�ڼ䣬SDAʼ�ձ��ֵ͵�ƽ
void IIC_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//������Ӧ���ź�
//��������Ϊ��SCLΪ�ߵ�ƽ�ڼ䣬SDAҲ�����˸ߵ�ƽ  
void IIC_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}					 				     
//IIC����һ���ֽ�  
//��������Ϊ��SCLΪ�͵�ƽ�ڼ�׼�������ݣ�SCLΪ�ߵ�ƽ�ڼ䱣������
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    IIC_SCL_L;//����ʱ��׼������
    for(t=0;t<8;t++)
    {              
      if((txd&0x80)>>7) //�����ݵ����λ��ʼ����
      		IIC_SDA_H;	//���Ϊ1��������λΪ1
      	else IIC_SDA_L; //��Ϊ1������λΪ0
        txd<<=1; 	  //�������
		delay_us(2);   
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    
//��һ���ֽڣ�ack=1ʱ������ACK,ack=0������nACK
//��ȡ����Ϊ��SCLΪ�ߵ�ƽ�ڼ䣬��ȡSDA�ĵ�ƽ״̬
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
    for(i=0;i<8;i++ ) //�����8λ
	{
        IIC_SCL_L; 
        delay_us(2);
		IIC_SCL_H; //SCLΪ�ߵ�ƽ
        receive<<=1; //����ƶ�����λ
        if(READ_SDA)receive++;   //���SDAΪ�ߣ�����Ӧ������Ϊ+1����֮Ϊ0
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//������ACKӦ��
    else
        IIC_Ack(); //����ACKӦ��
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
