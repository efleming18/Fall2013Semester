/*
 * File:   MainLCD.c
 * Author: student
 *
 * Created on September 30, 2013, 2:21 PM
 */

#include <p24fj128ga010.h>

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF &COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)

//Task 01
/*
int main(void)
{
char datumOut;
//initialization
initPMP(); // Initalize PMP
PMADDR = 0x0000; // Initally access LCD Controller registers
datumOut=0x3C; // Data to be written to LCD
//endless loop
again:
PMDIN1 = datumOut; // Write to LCD
while(PMMODEbits.BUSY == 1) // Wait for PMP (not LCD) to be done
    Nop();
_10usDelay(4);
if (PMADDR == 0x0000)
PMADDR=0x0001; // Access LCD DDRAM or CGRAM
else
PMADDR=0x0000; // Access LCD Controller Registers
goto again; //one more time
return (0);
}
 */

//Task 2
/*
int main(void) {
    initPMP();
    cmdLCD(1);
    cmdLCD(2);
    initLCD(3);
    while(1)
        Nop();
}
*/

//Task 3
int main(void){
    initPMP();
    cmdLCD(1);
    cmdLCD(2);
    initLCD(2);
    while(1){
        putLCD(0x48);
        putLCD(0x65);
        putLCD(0x6C);
        putLCD(0x6C);
        putLCD(0x6F);
        putLCD(0x20);
        putLCD(0x45);
        putLCD(0x53);
        msDelay(1000);
        cmdLCD(1);
        msDelay(500);
        putLCD(0x48);
        putLCD(0x65);
        putLCD(0x6C);
        putLCD(0x6C);
        putLCD(0x6F);
        putLCD(0x20);
        putLCD(0x45);
        putLCD(0x53);
        cmdLCD(2);
    }

}