#include "ioCC2530.h"
#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4
#define SW1 P1_2
unsigned int F=0;//时间
unsigned int a=0;//按键次数
void delay(unsigned int time){
  while(time--);
}
void Init_Port(){
P1SEL&=~0x1B;
P1DIR|=0x1B;

P1SEL&=~0x04;
P1DIR|=0x04;
P1INP&=~0x04;
P2INP&=~0x40;
}

void Init_key(){
  D4=~D4;D3=0;D5=0;D6=0;
  if(SW1==0){
  delay(200);
  if(SW1==0){
    a=0;
  while(SW1==0);
  a=1; 
}
  }
}
void Init_T1(){
T1CC0L=0xD4;
T1CC0H=0x30;
T1CCTL0|=0x04;
T1IE=1;
EA=1;
T1CTL=0x0E;
}
#pragma vector=T1_VECTOR
__interrupt void serT1(){
if(a==1){ 
    F++;
    if(F==0){D5=1;D6=1;} 
    Init_key();
    if(F==20){D5=0;D6=0;a=0;F=0;} 
  }

}


void main(){
  Init_Port();
  Init_T1();
while(1){ Init_key();}

}