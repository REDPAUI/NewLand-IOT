#include "ioCC2530.h"
 
#define LED1  P1_0
#define LED2  P1_1
#define SW1 P1_2
 
unsigned char count_t = 0;
unsigned char K_Num = 0;
 unsigned char f = 0;

/*=======================简单的延时函数========================*/
void Delay(unsigned int t)
{
  while(t--);
}
 
/*======================端口初始化函数========================*/
void Init_Port()
{
  P1SEL &= ~0x1b;     //P1_0、P1_1、P1_3和P1_4作为通用I/O端口
  P1DIR |= 0x1b;      //P1_0、P1_1、P1_3和P1_4端口输出
  
  P1SEL &= ~0x04;     //P1_2作为通用I/O端口
  P1DIR &= ~0x04;     //P1_2端口输入
  P1INP &= ~0x04;     //P1_2设置为上拉/下拉模式
  P2INP &= ~0x40;     //P1_2设置为上拉
}
 
/*=======================定时器1初始化========================*/
void Init_Timer1()
{
  T1CC0L = 0xd4;      
  T1CC0H = 0x30;        //16MHz时钟，128分频，定时0.1秒
  T1CCTL0 |= 0x04;      //开启通道0的输出比较模式
  T1IE = 1;
  EA = 1;
  T1CTL = 0x0e;         //分频系数是128,模模式
}
 
/*====================定时器1服务函数========================*/
#pragma vector = T1_VECTOR
__interrupt void Timer1_int()
{
f++;
if(f==0){LED1=1;LED2=1;}
if(f==30){LED1=0;LED2=0;}
  if(K_Num != 0 && SW1 != 0)      
  {
    count_t++;        //定时器1溢出一次加1，溢出周期为0.1S
  }
}
 
/*====================按键扫描处理函数========================*/
void Scan_Keys()
{
  if(SW1 == 0)
  {
    Delay(100);         //去抖动处理
    if(SW1 == 0)
    {
      while(SW1 == 0);  //等待按键松开
      count_t = 0;      //每次有按键按下，计时重新开始
      K_Num++;          //改变按键状态
      if(K_Num > 4)     //四连击以上均判为四连击
      {
        K_Num = 4;
      }
    }
  }
  if(count_t > 5)       //按键间隔时间到
  {    
    switch(K_Num)
    {
      case 1:           //按键单击
        LED1=~LED1;
      break;
      case 2:           //按键双击
       LED2=~LED2;
      break;
      case 3:           //按键三连击
       LED1=~LED1;
       LED2=~LED2;
      break;
      case 4:           //按键四连击
       LED1=0;LED2=0;
      break;
    }
    K_Num = 0;     //每处理完一次按键，状态清零
    count_t = 0;   //计时清零
  }
}
 
/*=========================主函数=============================*/
void main()
{
  Init_Port();
  Init_Timer1();

  while(1)
  {
    Scan_Keys();
  }
}