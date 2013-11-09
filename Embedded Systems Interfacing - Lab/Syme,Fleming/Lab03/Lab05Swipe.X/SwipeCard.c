/*
 * File:   SwipeCard.c
 * Author: student
 *
 * Created on October 14, 2013, 2:35 PM
 */


#include <p24fj128ga010.h>
_CONFIG1(JTAGEN_OFF&GCP_OFF&GWRP_OFF&BKBUG_OFF&COE_OFF&FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD&OSCIOFNC_ON&POSCMOD_HS&FNOSC_PRI)

unsigned int stb_cnt=0;
unsigned int ones_cnt=0;
unsigned int bit_cnt=0;
enum STATE_TYPE {NEW, LEADING, CHARACTER, TRAILING, DECODE, ERROR} state;

void __attribute__((interrupt,no_auto_psv)) _INT1Interrupt(void)
{
_INT1IF=0; //clear external interrupt
switch(state)
{
case NEW:
    if(_RD14==0)state=LEADING;
    break;
case LEADING:
    if(_RE9==0)
    {
    state=CHARACTER;
    bit_cnt+=1;
    }
break;
case CHARACTER:
// Add code to break data stream into characters and search for end sentinel
//
break;
case TRAILING:
    //check for errors
    if(_RD14==1)
    state=DECODE;
    break;
case DECODE:
    break;
default: state = ERROR;
}
}

int main(void) {
    initBargraph();
    initSwipe();


    while(1){
        setBargraph(state);
    }
    return 0;
}



void initSwipe(void){
    PORTD = 0;
    PORTE = 0;
    TRISDbits.TRISD14 = 1;
    TRISEbits.TRISE8 = 1;
    TRISEbits.TRISE9 = 1;
    INTCON2bits.INT1EP = 1;
    IFS1bits.INT1IF = 0;
    IEC1bits.INT1IE = 1;

}

/*void __attribute__((interrupt,no_auto_psv))
INT1Interrupt(void)
{
INT1IF=0; //clear external interrupt
switch(state)
{
case NEW:
    if(RD14==0)state=LEADING;
    break;
case LEADING:
    if(RE9==0)
    {
    state=CHARACTER;
    bit_cnt+=1;
    }
break;
case CHARACTER:
// Add code to break data stream into characters and search for end sentinel
//
break;
case TRAILING:
    //check for errors
    if(RD14==1)
    state=DECODE;
    break;
case DECODE:
    break;
default: state=ERROR;
}
}
*/