#include "wifi.h"   
#include "DHT11.h"
#include "RGB.h"
#include "stdio.h"

unsigned char dat_arr[7] = "abc";

void main()
{
    UartInit();
    Timer0Init();
    RGBInit();
    
    //����pwm��
    //ÿ20ms����һ����ʪ����Ϣ
    while(1);
}

void UartInit(void)		//9600bps@11.0592MHz
{
//	TMOD = 0x20;
//  SCON = 0x50;
//  TH1 = 0xFA;
//  TL1 = TH1;
//  PCON = 0x80;
//  ES = 1;
//  TR1 = 1;
//  EA = 1;
  //������ 12MHz  2400baud/s
    SCON |= 0X50;
		TMOD |= 0X20; //������������Ҫ��
		PCON |= 0X80;
		TH1 = 0XF3;
		TL1 = 0XF3;
		TR1 = 1;
		ES = 1;
		EA = 1;
}

void Timer0Init(void)		//200΢��@11.0592MHz
{                                     //��ʱ��Ƶ��50Hz
	TMOD |= 0x01; //��ʱ��0��ʽ1
  TH0  = 0xFF;
  TL0  = 0x38;
  ET0  = 1;
  TR0  = 1;
  EA   = 1;
}

//�����жϽ���RGBָ��
void uart() interrupt 4
{
  unsigned char recev;
  static unsigned char flag = 0;
  
  if(RI)
  {
    recev = SBUF;
    RI = 0;
    //�������ݽ�������ȡ��Ч����
    if(recev == 0xff && flag == 0)
      flag = 1;
    else if(flag == 1)
    {
       pwm_l.r = recev;
       flag = 2;
    }
    else if(flag == 2)
    {
       pwm_l.g = recev;
       flag = 3;
    }
    else if(flag == 3)
    {
       pwm_l.b = recev;
       flag = 4;
    }
    else if(flag == 4)
    {
       pwm_r.r = recev;
       flag = 5;
    }
    else if(flag == 5)
    {
       pwm_r.g = recev;
       flag = 6;
    }
    else if(flag == 6)
    {
       pwm_r.b = recev;
       flag = 0;
    }
    else 
       flag = 0;
    
  }
  else 
    TI = 0;
}

void Send_Str(unsigned char* fun)
{
    while((*fun)!='\0')
    {
        SBUF = *fun; //����
        while(!TI);  //�ȴ��������
        TI=0;        //��շ�������ж������־λ
        fun++;
    }
}

