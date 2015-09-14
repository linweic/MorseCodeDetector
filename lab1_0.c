#include <hidef.h>
#include <mc9s12c128.h>
#include "stdio.h"
#include "termio.h"

void main(void){
   
  TERMIO_Init(); //Initialize the Serial Port
  EnableInterrupts;
  TSCR1 |= 0x80;
  TIOS = 0x00;
  TCTL4 = 0x30; //capture rising and falling edge,chanel 2
  TFLG1 = 0x04; //clear input capture flag
  DDRB = 0x40; //set PORTB 6 as output
  
  while(1){
    PORTB = 0x00;//reset PORTB
    if(PTT & 0x04){ //Whenever the key is pressed, PTT2 gets high, set PORTB6 as high
      PORTB = 0x40; //LED lit up
    }
  }
}
