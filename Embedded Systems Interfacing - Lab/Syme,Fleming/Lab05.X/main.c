/*
 * File:   main.c
 * Author: student
 *
 * Created on October 16, 2013, 2:30 PM
 */


#include "xc.h"
#include <p24fj128ga010.h>


enum STATE_TYPE {NEW, LEADING, CHARACTER, TRAILING, DECODE, ERROR};
enum STATE_TYPE state = NEW;
unsigned char stb_cnt = 0;
unsigned char ones_cnt = 0;
unsigned char bit_cnt = 0;
unsigned char character;
unsigned char char_buf[40];

void initSwipe(void);

//void __attribute__((interrupt,no_auro_psv)) _INT1Interrupt(void)
//{
//    _INT1IF = 0;
//    if(_RE9 == 0)
//        ++ones_cnt;
//    ++stb_cnt;
//}
void __attribute__((interrupt,no_auro_psv)) _INT1Interrupt(void)
{
    _INT1IF=0; //clear external interrupt
    ++bit_cnt;
    switch(state)
    {
    case NEW:
        if(_RD14==0)
            state=LEADING;
        break;
    case LEADING:
        if(_RE9==0)
        {
            state=CHARACTER;
            bit_cnt+=1;
        }
        break;
    case CHARACTER:
        //Add the code for this.
        break;
    case TRAILING:
        //check for errors
        if(_RD14==1)
            state=DECODE;
        break;
    case DECODE:
//        character >> 1;
//        ++bit_cnt;
//        if(_RE9 == 1)
//        {
//            ++ones_cnt;
//        }
        break;
    default: state = ERROR;
    }
}

int main(void) {
    initBargraph();
    initSwipe();
    while(1)
    {
        setBargraph(state);
        //setBargraph(bit_cnt);
    }

    return 0;
}

void initSwipe(void)
{
    PORTD = 0;
    PORTE = 0;
    TRISDbits.TRISD14 = 1;
    TRISEbits.TRISE8 = 1;
    TRISEbits.TRISE9 = 1;
    INTCON2bits.INT1EP = 1;
    IFS1bits.INT1IF = 0;
    IEC1bits.INT1IE = 1;
}
