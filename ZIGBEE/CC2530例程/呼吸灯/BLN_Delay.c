#include <ioCC2530.h> 

#define LED1 P1_0 /*宏定义 P1_0端口*/

/*
void Init_Port():该函数为端口初始函数
@PxSEL:端口功能寄存器
	0: 通用I/O
	1：外设功能
@PxDIR:端口方向寄存器
	0：输入
	1：输出
*/

void Init_Port()
{
  P1SEL &=~0x01;
  P1DIR |= 0x01; 
  LED1 = 0; 
  /* LED1=0:将P1_0端口写入0*/
}
/*
void Delay(unsigned int j):用户自定义延迟函数
unsigned int j：无符号整型参数（也可以直接定义为int类型）
使用while循环，让计算机跑空代码，而达到延时目的
*/
void Delay(unsigned int j)
{
  while(j--);
}

/*
void main():程序入口函数
结构体：
void main(){
	//code1
	while(1){
	//code2
	}
}
将所需要使用的的代码块放入主函数中
code1为初始函数
code2为执行函数
*/
/*
若要修改呼吸的速度，需要修改for循环次数,或延迟时间
*/
void main()
{
  Init_Port();
  while(1)
  {
    unsigned char i;		//定义变量i用于for循环 ;也可以在for循环中定义
    for(i=0; i<100; i++)	//for循环1
    {
      LED1 = 1;				//LED1写1（亮）
      Delay(100*i);			//传入延迟时间
      LED1 = 0;				//LED1写0（灭）
      Delay(100*(100-i));   //传入延迟时间
        }
    for(i=0; i<100; i++)
    {
      LED1 = 1;
      Delay(100*(100-i));
      LED1 = 0;
      Delay(100*i);
        }
    }
}
/*
参考文献：2.4GHz IEEE802.15.4和ZigBee®应用的CC253X片上系统解决方案
*/