#include "ioCC2530.h"
 
#define LED1  P1_0
#define LED2  P1_1
#define SW1 P1_2
 
unsigned char count_t = 0;
unsigned char K_Num = 0;
 unsigned char f = 0;

/*=======================�򵥵���ʱ����========================*/
void Delay(unsigned int t)
{
  while(t--);
}
 
/*======================�˿ڳ�ʼ������========================*/
void Init_Port()
{
  P1SEL &= ~0x1b;     //P1_0��P1_1��P1_3��P1_4��Ϊͨ��I/O�˿�
  P1DIR |= 0x1b;      //P1_0��P1_1��P1_3��P1_4�˿����
  
  P1SEL &= ~0x04;     //P1_2��Ϊͨ��I/O�˿�
  P1DIR &= ~0x04;     //P1_2�˿�����
  P1INP &= ~0x04;     //P1_2����Ϊ����/����ģʽ
  P2INP &= ~0x40;     //P1_2����Ϊ����
}
 
/*=======================��ʱ��1��ʼ��========================*/
void Init_Timer1()
{
  T1CC0L = 0xd4;      
  T1CC0H = 0x30;        //16MHzʱ�ӣ�128��Ƶ����ʱ0.1��
  T1CCTL0 |= 0x04;      //����ͨ��0������Ƚ�ģʽ
  T1IE = 1;
  EA = 1;
  T1CTL = 0x0e;         //��Ƶϵ����128,ģģʽ
}
 
/*====================��ʱ��1������========================*/
#pragma vector = T1_VECTOR
__interrupt void Timer1_int()
{
f++;
if(f==0){LED1=1;LED2=1;}
if(f==30){LED1=0;LED2=0;}
  if(K_Num != 0 && SW1 != 0)      
  {
    count_t++;        //��ʱ��1���һ�μ�1���������Ϊ0.1S
  }
}
 
/*====================����ɨ�账����========================*/
void Scan_Keys()
{
  if(SW1 == 0)
  {
    Delay(100);         //ȥ��������
    if(SW1 == 0)
    {
      while(SW1 == 0);  //�ȴ������ɿ�
      count_t = 0;      //ÿ���а������£���ʱ���¿�ʼ
      K_Num++;          //�ı䰴��״̬
      if(K_Num > 4)     //���������Ͼ���Ϊ������
      {
        K_Num = 4;
      }
    }
  }
  if(count_t > 5)       //�������ʱ�䵽
  {    
    switch(K_Num)
    {
      case 1:           //��������
        LED1=~LED1;
      break;
      case 2:           //����˫��
       LED2=~LED2;
      break;
      case 3:           //����������
       LED1=~LED1;
       LED2=~LED2;
      break;
      case 4:           //����������
       LED1=0;LED2=0;
      break;
    }
    K_Num = 0;     //ÿ������һ�ΰ�����״̬����
    count_t = 0;   //��ʱ����
  }
}
 
/*=========================������=============================*/
void main()
{
  Init_Port();
  Init_Timer1();

  while(1)
  {
    Scan_Keys();
  }
}