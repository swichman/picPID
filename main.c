/* 
 * File:   main.c
 * Author: seightonn
 *
 * Created on May 3, 2015, 8:18 PM
 */
#include <pic12f1572.h>
#include "helper.h"
// PIC12F1572 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    //  (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

/*
 * 
 */

volatile int rpm;
//volatile int set_point = 1000;
volatile double kp=1, ki=2, kd=.5;
volatile char * buffer;

void main(){
    setup();
    ei();
    
    for(;;){
        xmit(rpm);
        pid(set_point,rpm, kp, ki, kd);
        wait(5000);
    }
}

void interrupt IOC_rising(void){
    if (IOCIE && IOCIF){
        //TMR2ON = 0;
        rpm = 3300000/TMR1;               // save timer value
        TMR1 = 0;                   // reset timer
        //TMR2ON = 1;
        IOCIF = 0;                  // clear IOC flag
        IOCAF5 = 0;
    }
}



