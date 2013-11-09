/*
 * File:   newmainXC16.c
 * Author: student
 *
 * Created on October 2, 2013, 2:28 PM
 */


#include "xc.h"
#include <p24fj128ga010.h>


//Task 1
/*int main(void)
{
    char datumOut;
    //initialization
    initPMP(); // Initalize PMP
    PMADDR = 0x0000; // Initally access LCD Controller registers
    datumOut=0x3C; // Data to be written to LCD
    //endless loop
    while(1)
    {
        PMDIN1 = datumOut; // Write to LCD
        while(PMMODEbits.BUSY == 1) // Wait for PMP (not LCD) to be done
            Nop();
        _10usDelay(4);
        if (PMADDR == 0x0000)
            PMADDR=0x0001; // Access LCD DDRAM or CGRAM
        else
            PMADDR=0x0000; // Access LCD Controller Registers
        //one more time
    }
    return (0);
}*/

//Task 2
/*int main(void)
{
    initPMP();
    cmdLCD(1);
    cmdLCD(2);
    initLCD(3);
    while(1)
        Nop();
    return 0;
}*/

//Task 3
int main(void){
    initPMP();
    cmdLCD(1);
    cmdLCD(2);
    initLCD(2);
    while(1){
        putLCD('#');
        putLCD('Y');
        putLCD('O');
        putLCD('L');
        putLCD('O');
        putLCD(' ');
        putLCD('S');
        putLCD('W');
        putLCD('A');
        putLCD('G');
        
        msDelay(1000);
        cmdLCD(1);
        msDelay(500);
        
        cmdLCD(2);

    }

}


