#include "RGB.h"
#include "wifi.h"
//P22��P27
//    �ұ�            ���
//P24 P23 P22      P27 P26 P25
// R   G   B        R   G   B
struct pwm pwm_l = {0, 0, 0};
struct pwm pwm_r = {0, 0, 0};


void RGBInit()
{
  //��ʼ״̬������������ɫ
  //�趨pwm�Ƚ�ֵ
  pwm_l.r = 20;
  pwm_l.g = 50;
  pwm_l.b = 80;
  
  pwm_r.r = 20;
  pwm_r.g = 50;
  pwm_r.b = 80;
  
}

void rgb() interrupt 1 //0.2ms��һ���ж�
{
  static unsigned char cnt = 0;
  static unsigned int count = 0;
  TH0 = 0x0FF; //���ó�ֵ
  TL0 = 0x38;
  
  count++;
  cnt++;
  
  if(cnt == 100)
    cnt = 0;
  if(count == 500) //100ms����һ��
  {
     count = 0;
     //Send_Str(unsigned char* fun); ������ʪ�ȴ�������Ϣ
  }
  R1 = cnt < pwm_l.r ? 1 : 0;
  G1 = cnt < pwm_l.g ? 1 : 0;
  B1 = cnt < pwm_l.b ? 1 : 0;
  R2 = cnt < pwm_r.r ? 1 : 0;
  G2 = cnt < pwm_r.g ? 1 : 0;
  B2 = cnt < pwm_r.b ? 1 : 0;  
//  if(count == 5000)
//  {
//    count = 0;
//    Send_Uart(0xf0);
//  }
}
