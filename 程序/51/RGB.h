#ifndef _RGB_H_
#define _RGB_H_
#include "reg52.h"
//P22µ½P27
//    ÓÒ±ß            ×ó±ß
//P24 P23 P22      P27 P26 P25
// R   G   B        R   G   B

sbit R1 = P2^7;
sbit G1 = P2^6;
sbit B1 = P2^5;
sbit R2 = P2^4;
sbit G2 = P2^3;
sbit B2 = P2^2;

struct pwm{ 
  unsigned char r; 
  unsigned char g; 
  unsigned char b;
};
extern struct pwm pwm_l, pwm_r;


void RGBInit(void);

#endif
