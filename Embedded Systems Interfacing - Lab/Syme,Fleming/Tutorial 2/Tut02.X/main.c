/*
 * File:   main.c
 * Author: student
 *
 * Created on September 11, 2013, 2:58 PM
 */


#include "xc.h"
#include <p24fj128ga010.h>
//#include <peripherals.h>

int main(void) {
    unsigned char display=0;
    //initialization
    initButtons(0x0009);
    initBargraph();
    //endless loop
    while(1)
    {
        Nop(); //breakpoint access point
        setBargraph(display); //sent count to display
        msDelay(1000); //delay approximately 1 second
        if(getButton(0x0001))
            display=display+1; //if S4 pressed increment display counter
        else if(getButton(0x0008))
            display=0; //else if RD6 pressed reset display counter
        else
            display=display-1; //else decrement display counter
    }
    return 0;
}
