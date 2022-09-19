#include <ioCC2530.h>
#include <string.h>

#define LED1 P1_0 

void Init_Port(void)
{
	 P1SEL &=~0x01;
     P1DIR |= 0x01;           
     LED1 = 1;                //默认灭
}
/*
void Init_TIM():定时器配置函数
*************************************CODE1********************************************
CODE1的代码段将16M的晶振切换为32M的晶振，可以不进行切换

CLKCONCMD:时钟控制命令
CLKCONSTA：时钟控制状态
	扩展：
	  两个高频振荡器：32MHz 晶振、16 MHz RC 振荡器
	  32 MHz 晶振启动时间对一些应用程序来说可能比较长，
	  需要使用 while(CLKCONSTA & 0x40);查询时钟的状态等待时钟稳定
	  有关寄存的配置可以查看CC2530用户使用手册的60页
	  
*************************************CODE2********************************************
CODE2开始为配置定时器
PERCFG：外设寄存器
	选择定时器中的备用位置1或者备用2

*************************************CODE3********************************************
P2SEL：
	P2SEL.PRI1P1 和 P2SEL.PRI0P1 选择为端口 1 指派一些外设的优先顺序。
	当前者设置为低电平而后者设置为高电平时，定时器 1 通道优先。
P2DIR:
	P2DIR.PRIP0 选择为端口 0 指派一些外设的优先顺序。
	当设置为 10，定时器通道 0-1 优先，当设置为 11，定时器通道 2-3 优先。
	要所有定时器 1 通道在备用位置 1 上可见，移动 USART 0 和 USART 1 到备用位置 2。
	
*************************************CODE4********************************************
定时器功能实现的端口LED1 

*************************************CODE5********************************************
x表示通道号
T1CCxH：	定时1通道x捕获/比较值高位
T1CCxL：	定时1通道x捕获/比较值低位
T1CCTL2：	定时1通道x捕获/比较控制
T1CTL:		定时器1的控制和状态
*/
void Init_TIM()
{
	/*CODE1*/
    CLKCONCMD &= ~0x40;      	//设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40); 	//等待晶振为32M
    CLKCONCMD &= ~0x07;      	//设置系统主时钟频率为32MHZ   
    CLKCONCMD |= 0x38;       	//设置定时器所分频率为250KHZ
	/*CODE2*/
    PERCFG |= 0x40;          	//选择定时器1映射的IO口位置，选择备用位置2，映射的IO口就是P1_0 
   /*CODE3*/
    P2SEL &= ~0x10;          	//设置优先级，定时器1优先
    P2DIR |= 0xC0;           	//设定第1优先级：定时器1通道2-3
	/*CODE4*/
    P1DIR |= 0x01;           	//设置P1_0为输出
    P1SEL |= 0x01;           	//P1_0配置为外设功能对应定时器1
	/*CODE5*/
    T1CC2H = 0x00;           	//T1CC2H为T1CC0的高位，T1CC2L为T1CC0的低位
    T1CC2L = 0x00;           	//修改T1CC2L可调整占空比，此处的设置决定比较时的值
    T1CC0H = 0x00;           	//
    T1CC0L = 0xff;       	 	//
    T1CCTL2 = 0x1c;          	//设置模式
    T1CTL = 0x02;            	//频率250KHz 1分频，运行模式为模模式
}
/*
Delay_us(unsigned int t)：延迟函数
while (t--)、while(t--)、while(t--){;;}的作用相同
	
*/
void Delay_us(unsigned int t){
    while (t--)
    {
       asm("NOP");
       asm("NOP");
       asm("NOP");
    }
    
}

void main(void){
Init_Port();					//初始化LED灯
Init_TIM();						//初始化定时器
unsigned int a = 0x00;
unsigned int b = 0x00;
while (1)
{
    a++; 						//改变通道2的定时值
    Delay_us(10000);
    T1CC2H = b;
    T1CC2L = a;
    if(a ==0xff){
        while (1)
        {
          a--;					//改变通道2的定时值
          Delay_us(10000);
          T1CC2H = b;
          T1CC2L = a;
          if (a==0)
          {
           break;
          }
          
        }
        
    }
}

}
/*
参考文献：2.4GHz IEEE802.15.4和ZigBee®应用的CC253X片上系统解决方案
*/