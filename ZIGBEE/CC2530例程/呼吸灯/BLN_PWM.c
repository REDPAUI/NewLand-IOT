/*
BLN_PWM的实现原理同BLN_Delay相同,利用延迟函数实现呼吸灯效果
*/
#include<ioCC2530.h>
#define LED1 P1_0

void Init_Port()
{
  P1SEL &= ~0X01;
  P1DIR |= 0X01;
  P1 &= ~0X01;
}
void Delay(int time)
{
  while(time--);
}
void main()
{
  Init_Port();
  int i,j=1000;
  int flag = 1;
  while(1)
  {
    if(flag)
    {
      LED1 = 1;
      Delay(i++);
      LED1 = 0;
      Delay(j--);
      if(j == 0)
        flag = 0;
    }
    else
    {
      LED1 = 1;
      Delay(i--);
      LED1 = 0;
      Delay(j++);
      if(i == 0)
        flag = 1;
    }
  }
}
