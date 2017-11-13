/* 
 * File:   helper.h
 * Author: seightonn
 *
 * Created on May 4, 2015, 10:44 PM
 */
#ifndef HELPER_H
#define	HELPER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* HELPER_H */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>



void setup(void);
void debug1(void);
void debug2(void);
void pid(int ref, int in, double kp, double ki, double kd);
int error, error_old;
int out;
void xmit(int rpm);
void wait(int i);
void putch(char data);

int switch_set = 0;
volatile int set_point=1400;

void setup(){
    // enable 8MHz PLL clock
    OSCCON = 0x68;
    
    // ensure that the i/o is disabled
    TRISA = 0x22;
    WPUA5 = 1;
    LATA = 0x0;
    
    // reconfigurable pin settings
    APFCON = 0x2;
    
    // turn on PWM3 pin 5
    PWM2PR = 0x7d00;
    PWM2PH = 0;
    PWM2DC = 0;
    PWM2CON = 0xC0;
    
    // interrupt on change
    IOCAP = 0x20;                // interrupt on positive edge
    INTCON = 0xC8;              // enable GIE and IOCIE
    
    // set up timer
    T1CON = 0x31;
    TMR1 = 0x0;
    
    // set up UART1
    SPEN = 1;
    BRGH = 1;                   // 58820 baud
    SPBRG = 12;                 // 
    CREN = 1;
    TXEN = 1;
    //RCIE = 1;
    
    
    
    

}

void pid(int ref, int in, double kp, double ki, double kd){
    error_old = error;
    error = ref - in;
    out = kp*error + ki*(error_old + error) + kp*(error - error_old);
    PWM2DC = PWM2DC + out;
    PWM2LDCON = 0x80;
    error_old = error;
}

void xmit(int rpm){
    printf("%d,%d\n\r",rpm, set_point);
}

void putch(char data){
    while (! TXIF)
        continue;
    TXREG = data;
}
    
void wait(int c){
    for (int i = 0; i <= c; i++)i = i;
    switch_set++;
    
    if(switch_set >= 100 && set_point == 1400){
        set_point = 2900;
        switch_set = 0;
    }
        
    if(switch_set >= 100 && set_point == 2900){
        set_point = 1400;
        switch_set = 0;
    }
        
}

