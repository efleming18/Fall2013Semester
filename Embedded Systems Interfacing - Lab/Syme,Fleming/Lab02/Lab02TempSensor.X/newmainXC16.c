/*
 * File:   newmainXC16.c
 * Author: student
 *
 * Created on September 18, 2013, 2:42 PM
 */


#include "xc.h"
#include <p24FJ128GA010.h>

#include "peripherals.h"
#include <p24fj128ga010.h>
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)


int main(void)
{
    unsigned int N,Temp_Celsius,Temp_Fah;

    TRISB=0xFF;

    initBargraph();
    initButtons(0x0001);
    initADC(0x0004);
    while(1)
    {
        N=getADC(4);
        Temp_Celsius= (330L*(long)N-51200L)/1024L;

        
        if(getButton(0x0001))
        {
            setBargraph(Temp_Celsius);
        }
        else
        {
            Temp_Fah=(unsigned int)(9*Temp_Celsius/5)+32;
            setBargraph(Temp_Fah);
        }
        msDelay(1000);
     }
    return 1;
}
