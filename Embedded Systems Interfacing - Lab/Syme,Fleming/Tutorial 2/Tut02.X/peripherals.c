

#include <p24fj128ga010.h>
#define SCALE 308L





void initBargraph(void){

PORTA=0x0000; //clear port A
TRISA=0xFF80; //set PORTA <6:0> to output

}

void initButtons(unsigned int mask)

{
if(mask&0x0008) TRISDbits.TRISD6=1;

if(mask&0x0004) TRISDbits.TRISD7=1;

if(mask&0x0002) TRISAbits.TRISA7=1;

if(mask&0x0001) TRISDbits.TRISD13=1;
}
unsigned int getButton(unsigned int mask)

{

unsigned int button;

switch(mask) {

case 0x0008: button=!PORTDbits.RD6;
    break;

case 0x0004: button=!PORTDbits.RD7;
    break;

case 0x0002: TRISAbits.TRISA7=1;

button=!PORTAbits.RA7;
    break;

case 0x0001: button=!PORTDbits.RD13;
    break;

default:
button=0;
}
return (button); }

void setBargraph(unsigned int display)
{ TRISAbits.TRISA7=0;
PORTA=0x00FF&display; //transfer to bargraph
}
void msDelay(unsigned int ms)
{ unsigned long i;
for(i=(unsigned long)(ms+1)*SCALE;i>0;i-=1)
    Nop();
}