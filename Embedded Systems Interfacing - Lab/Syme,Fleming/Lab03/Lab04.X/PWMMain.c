
#include <p24fj128ga010.h>

void __attribute__((interrupt,no_auto_psv))_T3Interrupt (void)
{
    _T3IF=0; //clear interrupt
    AD1CON1bits.SAMP=1; //start sampling
}
volatile unsigned int rawSpeed;
void __attribute__((interrupt,no_auto_psv))_ADC1Interrupt (void)
{
    rawSpeed = ADC1BUF0 & 0x3FF; //read and mask conversion
    AD1CON1bits.DONE=0; //clear conversion done
    _AD1IF=0; //clear interrupt
}

int main(void)
{
    initPWM1(0x400);
    //while(1)
    //{
        dutyCyclePWM(0x100);
    //}
    return 0;
    
}



















/*//Declarations
    unsigned int pulseWidth=0;
    //initialzation
    initADC(5);
    initPWM1(0x03FF);
    initBargraph();
    PR3=6250-1;
    TMR3=0;
    T3CONbits.TON=1;
    T3CONbits.TCKPS=2;
    _T3IF=0;
    _T3IE=1;
    _AD1IF=0;
    _AD1IE=1;
    while(1)
    {
        pulseWidth=(rawSpeed)&0x03FF; //next pulse width step //clear interrupt ag
        dutyCyclePWM(pulseWidth); //setup next pulse width
        setBargraph(pulseWidth>>2);
     }*/