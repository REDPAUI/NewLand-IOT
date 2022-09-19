#include "ioCC2530.h"
#include "stdio.h"
#define  LED1   P1_0
#define  LED2   P1_1
#define  SW1   P1_2
void Init_Port()
{
  P1SEL &= ~0x03;      
  P1DIR |= 0x03;        
P1SEL&=~0x04;
P1DIR&=~0x04;
P1INP&=~0x04;
P2INP&=~0x40;
} 
void C_32M(){
CLKCONCMD&=0x40;
while(CLKCONCMD&0x40);
CLKCONCMD&=~0x07;
}
void uart(){
PERCFG&=~0x01;
P1SEL|=0x0C;
U0BAUD=59;
U0GCR=8;
U0UCR|=0x80;
U0CSR|=0xC0;
}
void UR0SendByte(unsigned char dat)
{
  U0DBUF = dat;         
  while(UTX0IF==0);       
  UTX0IF = 0;           
}
void UR0SendString(unsigned char *str)
{
  while(*str != '\0')       
  {
    UR0SendByte(*str++);    
  }
}
void delay(unsigned int t){
while(t--);
}
void key(){
  if(SW1==0){
  delay(200);
  if(SW1==0);
  while(SW1==0);
  LED1=~LED1;
  UR0SendString("LED1\r\n");
  }
}
void main()
{
  C_32M();
  Init_Port();         
  uart();        
  while(1)
  {
key();
}
}