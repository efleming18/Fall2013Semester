/*
 * File:   newmainXC16.c
 * Author: student
 *
 * Created on September 11, 2013, 2:34 PM
 */


#include <p24fj128ga010.h>
//Conguration words for Explorer-16 when using ICD-3
_CONFIG1(JTAGEN_OFF&GCP_OFF&GWRP_OFF&BKBUG_OFF&COE_OFF&FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD&OSCIOFNC_ON&POSCMOD_HS&FNOSC_PRI)
#define SCALE 308L
int main(void){
    unsigned long i;
    unsigned char display=0;

    PORTA=0x0000;
    TRISA=0xFF00;
    TRISD=0xFFFF; 
    while(1)
    {
        Nop();
        PORTA=(unsigned int) display;
        for(i=1001L*SCALE; i > 0; i--) Nop();
        if(PORTDbits.RD13 == 0)
            display = display+1;
        else if(PORTDbits.RD6 == 0)
            display = 0;
        else
            display = display-1;

    }
}
