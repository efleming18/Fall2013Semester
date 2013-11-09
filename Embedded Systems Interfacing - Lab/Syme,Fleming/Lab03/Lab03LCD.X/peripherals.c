#include "peripherals.h"
#include <p24fj128ga010.h>

#define US_SCALE 8
#define MS_SCALE 333L

#define LCD_CLEAR 1
#define LCD_HOME 2
#define cursor_ON 2
#define cursor_OFF 0
#define cursor_BLINK 3

void initADC(unsigned int initChannel){
	AD1CON1=0x00E0;				//Turn off, auto sample, auto start, auto convert
	AD1CON2=0x0000;				//AVdd, AVss, int every conversion, MUXA only
	AD1CON3=0x1F05;				//31 auto-sample, Tad = 5 Tcy
	AD1CHS=initChannel;
	AD1CSSL=0;					//ignore all on scan select
	TRISBbits.TRISB4=1;
	TRISBbits.TRISB5=1;
	AD1PCFGbits.PCFG5;				//disable digital input on AN5
	AD1PCFGbits.PCFG4;				//disable digital input on AN4
	AD1CON1bits.ADON=1;			//turn on ADC
	}

unsigned int getADC(unsigned int channel){
	AD1CHS=channel;					//select channel
	AD1CON1bits.SAMP=1;				//start sample
	while(AD1CON1bits.DONE==0);		//twiddle thumbs until convertion done
	AD1CON1bits.DONE=0;
	return(ADC1BUF0);
	}

void initButtons(unsigned int mask){
	if(mask&0x0008)
		TRISDbits.TRISD6=1;
	if(mask&0x0004)
		TRISDbits.TRISD7=1;  
	if(mask&0x0002)
		TRISAbits.TRISA7=1;
	if(mask&0x0001)
		TRISDbits.TRISD13=1;
	}

unsigned int getButton(unsigned int mask){
	unsigned int button;
	switch(mask){
		case 0x0008:
					button=!PORTDbits.RD6;
					break;	
		case 0x0004:
					button=!PORTDbits.RD7;
					break;
		case 0x0002:
					button=!PORTAbits.RA7;
					break;
		case 0x0001:
					button=!PORTDbits.RD13;
					break;
		default:
					button=0;
		}
	return (button);
	}


void _10usDelay(unsigned char _10us){
	unsigned int i;
	for(i=_10us*US_SCALE;i>0;i--) Nop();;
	}

void msDelay(unsigned int ms){
	unsigned long i;
	for(i=(unsigned long)(ms+1)*MS_SCALE;i>0;i-=1) Nop();
	}

void initBargraph(void){
	PORTA=0x0000;		//clear port A
	TRISA=0xFF00;		//set PORTA <7:0> to output
	}

void setBargraph(unsigned int display){
		PORTA=0x00FF&display;
		}
void initPMP(void)
{
    PMCONbits.PMPEN=1;
    PMCONbits.PSIDL=1;
    PMCONbits.ADRMUX=0;
    PMCONbits.PTWREN=1;
    PMCONbits.PTRDEN=1;
    PMCONbits.WRSP=1;
    PMCONbits.RDSP=1;
    PMMODEbits.MODE=3;
    PMMODEbits.WAITB=0;
    PMMODEbits.WAITM=2;
    PMMODEbits.WAITE=0;
    PMAENbits.PTEN0=1;
}
void initLCD(unsigned char cursor)
{
    msDelay(100);
    PMADDR =0;
    PMDIN1 = 0b00111100;
    _10usDelay(5);
    PMDIN1 = (0b00001100 | cursor);
    _10usDelay(5);
    PMDIN1 = 0b00000001;
    msDelay(2);
    PMDIN1 = 0b00000110;
    msDelay(2);
}
void cmdLCD(char cmd){
    switch(cmd){
        case LCD_CLEAR:
        case LCD_HOME:
            PMADDR = 0;
            PMDIN1 = cmd;
            msDelay(2);
            break;
        default:
            PMADDR = 0;
            PMDIN1 = cmd;
            _10usDelay(5);

    }
}
void putLCD(char ch){
  PMADDR=0x0001;
  PMDIN1 = ch;
  _10usDelay(5);
}

