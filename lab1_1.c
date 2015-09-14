#include <hidef.h>
#include <mc9s12c128.h>
#include "stdio.h"
#include "termio.h"

int edge_cnt, i;

void interrupt 10 IC2ISR(void){
  if (edge_cnt == 2) {//when firt edge (rising) edge comes, turn on the LED light
      PORTB = 0x40;
  }
  if (edge_cnt == 1) {//when second edge (falling) edge comes, turn off the LED light
      PORTB = 0x00;
  }
  --edge_cnt;
  for(i = 0; i<30000;i++)//wait for a period of time to avoid bouncing
  TFLG1 = 0x04; //clear the input capture flag
}

void main(void){
   
  TERMIO_Init(); //Initialize the Serial Port
  EnableInterrupts;
  TSCR1 |= 0x80;
  TIOS = 0x00;
  TCTL4 = 0x30; //capture rising and falling edge,chanel 2
  TFLG1 = 0x04; //clear input capture flag
  TIE |= 0x04;//enable timer interrupt on channel 2
  DDRB = 0x40; //set PORTB 6 as output
  edge_cnt = 2; //set edge count as 2
  
  while(1){
    edge_cnt = 2; //reset edge count to 2
    PORTB = 0x00;//reset PORTB
    while(edge_cnt!=0); //loop until edge_cnt becomes zero, meaning both rising and falling edges have arrived
  }
}
