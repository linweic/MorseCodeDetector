#include <hidef.h>
#include <mc9s12c128.h>
#include "stdio.h"
#include "termio.h"

int edge_cnt, i;
unsigned diff, edge1, overflow;
unsigned long pulse_width, real_width;
char result,tmp;
char num[6];


void interrupt 10 IC2ISR(void){
    
  if (edge_cnt == 2) {
      edge1 = TC2;
      //PORTB = 0x40;
      overflow = 0;
      //printf("rise\n");
      
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
  result = '\0';
  num[0] = '\0';
  
  while(1){
    edge_cnt = 2;
    overflow = 0;
    PORTB = 0x60; //reset PORTB
    while(edge_cnt>0){
      if(result!='\0' && overflow>20){
        break;
      }
    }
    if(1<=overflow && overflow<=8){
      //putchar('.');
      tmp = '.';
      strncat(num,&tmp,1);
      if(result == '\0') 
      {
        result = 'E';
      } 
      else if(result == 'E'){
        result = 'I';
      }
      else if (result == 'I'){
        result = 'S';
      }
      else if (result == 'S'){
        result = 'H';
      }
      else if(result == 'U')
      {
        result = 'F';
      } 
      else if(result == 'A')
      {
        result = 'R';
      } 
      else if(result == 'R')
      {
        result = 'L';
      } 
      else if(result == 'W')
      {
        result = 'P';
      } 
      else if(result == 'M')
      {
        result = 'G';
      } 
      else if(result == 'G')
      {
        result = 'Z';
      } 
      else if(result == 'T')
      {
        result = 'N';
      } 
      else if(result == 'N')
      {
        result = 'D';
      }
      else if(result == 'D')
      {
        result = 'B';
      } 
      else if(result == 'K')
      {
        result = 'C';
      }
    }
    else if(8<overflow && overflow<=20){
      //putchar('-');
      tmp = '-';
      strncat(num,&tmp,1);
      if(result == '\0')
      {
        result = 'T';
      } 
      else if(result == 'T')
      {
        result = 'M';
      } 
      else if(result == 'M')
      {
        result = 'O';
      } 
      else if(result == 'G')
      {
        result = 'Q';
      } 
      else if(result == 'N')
      {
        result = 'K';
      } 
      else if(result == 'K')
      {
        result = 'Y';
      } 
      else if(result == 'D')
      {
        result = 'X';
      } 
      else if(result == 'E')
      {
        result = 'A';
      } 
      else if(result == 'A')
      {
        result = 'W';
      } 
      else if(result == 'W')
      {
        result = 'J';
      } 
      else if(result == 'I')
      {
        result = 'U';
      } 
      else if(result == 'S')
      {
        result = 'V';
      }
    }
    else if(20<overflow){
      if(strlen(num) == 5){
        if(strcmp(num,".----")==0){
          putchar('1');
        } else if(strcmp(num,"..---")==0){
          putchar('2');
        } else if(strcmp(num,"...--")==0){
          putchar('3');
        } else if(strcmp(num,"....-")==0){
          putchar('4');
        } else if(strcmp(num,".....")==0){
          putchar('5');
        } else if(strcmp(num,"-....")==0){
          putchar('6');
        } else if(strcmp(num,"--...")==0){
          putchar('7');
        } else if(strcmp(num,"---..")==0){
          putchar('8');
        } else if(strcmp(num,"----.")==0){
          putchar('9');
        } else if(strcmp(num,"-----")==0){
          putchar('0');
        }
        num[0] = '\0';
        result = '\0';
      } 
      else
      {
        putchar(result);
        result = '\0';
        num[0] = '\0';
      }
    }
  }
}
