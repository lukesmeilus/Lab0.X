/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define ON 1
#define OFF 0

//TODO: Define states of the state machine
//typedef enum stateTypeEnum{
//} stateType;
typedef enum stateTypeEnum{
    led1, led2, led3
} stateType;

//TODO: Use volatile variables that change within interrupts
 volatile stateType state = led1;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    
   
    
    while(1){

        switch(state){
            case led1:
                LATDbits.LATD0 = ON;
                LATDbits.LATD1 = OFF;
                LATDbits.LATD2 = OFF;
                break;
            case led2:
                LATDbits.LATD0 = OFF;
                LATDbits.LATD1 = ON;
                LATDbits.LATD2 = OFF;
                break;
            case led3:
                LATDbits.LATD0 = OFF;
                LATDbits.LATD1 = OFF;
                LATDbits.LATD2 = ON;
                break;
        }
        
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interupt(){
    IFS0bits.T1IF = 0;
    if(state == led1) state = led2;
    else if(state == led2) state = led3;
    else if(state == led3) state = led1;
}