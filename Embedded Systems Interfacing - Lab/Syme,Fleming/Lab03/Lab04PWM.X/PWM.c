
#include <p24fj128ga010.h>

int main(void) {
    initPWM1(0x400);
    while(1)
        dutyCyclePWM(0x100);

    return 0;
}

void dutyCyclePWM(unsigned int dutyCycle)
{
if(dutyCycle<PR2)
OC1RS=dutyCycle; //update duty cycle
else
OC1RS=OC1RS;
}

void initPWM1(unsigned int period)
{
PR2=period; //set period
OC1RS=0x0000; //next high time is zero
OC1R=0x0000; //present high time is zero
OC1CONbits.OCTSEL=0; //use timer 2
OC1CONbits.OCM=6; //PWM without fault pin
TMR2=0;
T2CONbits.TCS=0; //Fcyc clock source
T2CONbits.TGATE=0; //no timer gate
T2CONbits.TCKPS=0; //prescaer 1:1
T2CONbits.TON=1; //turn on timer 2
}