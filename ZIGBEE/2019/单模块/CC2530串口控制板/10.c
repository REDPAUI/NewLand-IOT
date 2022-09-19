#include "ioCC2530.h"
#define LED1 P1_0
#define LED2 P1_1
#define SW1 P1_2
unsigned int a=0;
void Init(){
  P1SEL &=~0x03;
  P1DIR |=0x03;
  LED1=1;LED2=1;
  P1SEL &=~0x04;
  P1DIR &=~0x04;
  P1INP &=~0x04;
  P2INP &=~0x40;
}
void delay(unsigned int t){
  while(t--);
}
void InitLED(){
LED1=1;
LED2=0;
delay(60000);
delay(60000);
LED1=0;
LED2=1;
delay(60000);
delay(60000);
}
void scan_key(){
  if(SW1==0){
  delay(200);
  if(SW1==0){
  while(SW1==0);
  a=1;
  }
  }
}
void main(){
Init();
while(1){
  scan_key();
  if(a==1){InitLED();}}
}