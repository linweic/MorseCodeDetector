#include <hidef.h>
#include <mc9s12c128.h>
#include "stdio.h"
#include "termio.h"

int edge_cnt, i;
unsigned diff, edge1, overflow;
unsigned long pulse_width, real_width;


void interrupt 10 IC2ISR(void){
  if (edge_cnt == 2) {
      edge1 = TC2;
      overflow = 0;      
  }
  --edge_cnt;
  for(i = 0; i<30000;i++)
  TFLG1 = 0x04;
}

void interrupt 16 TOFISR() {
  TFLG2 = 0x80; //clear TOF flag
  overflow ++;
}


void main(void){
  TERMIO_Init(); //Initialize the Serial Port
  EnableInterrupts;
  TSCR1 |= 0x80;
  TIOS = 0x00;
  TCTL4 = 0x30; //capture rising and falling edge,chanel 2
  TFLG2 = 0x80; //clear TOF register
  TSCR2 = 0x80; //presaclar to 16 & enable local interrupt
  TFLG1 = 0x04;
  TIE |= 0x04;//enable timer interrupt on channel 2
  DDRB |= 0x60;//set PORTB 6,5 as output
  PORTB = 0x60;//set PORTB 5,6 as high;
  edge_cnt = 2;
  
  while(1){
    edge_cnt = 2;
    overflow = 0;
    PORTB = 0x60; //reset PORTB
    while(edge_cnt>0);
    if(1<=overflow && overflow<=6){
      putchar('.');
      PORTB = 0x20; //set PORTB 6 as low
    }
    if(6<overflow && overflow<=12){
      PORTB = 0x40; //set PORTB 5 as low
      putchar('-');
    }
    if(12<overflow){
      putchar(' ');
    }
    for(i=0;i<10000;i++); //let the light be lit for a brief period of time
  }
}
