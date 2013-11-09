/*
 * File:   TempSensor.c
 * Author: student
 *
 * Created on September 16, 2013, 2:32 PM
 */


#include "xc.h"
#include <p24FJ128GA010.h>
_CONFIG1(JTAGEN_OFF&GCP_OFF&GWRP_OFF&BKBUG_OFF&COE_OFF&FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD&OSCIOFNC_ON&POSCMOD_HS&FNOSC_PRI)

#include "peripherals.h"

int main(void) {
    unsigned int tempc;
    unsigned int temp;
    initADC(0x0004);
    initButtons(0x0001);
    initBargraph();
    while(1){
        tempc = getADC(0x0004);
        temp = (unsigned char)(((330L*(long)tempc)-51200L)/1024L);
        if(getButton(0x0001)){
        setBargraph(temp);
        }
        else{
        temp = (unsigned char)(((9*temp)/5)+32);
        setBargraph(temp);
        }
        msDelay(100);
    }
    return 0;
}
