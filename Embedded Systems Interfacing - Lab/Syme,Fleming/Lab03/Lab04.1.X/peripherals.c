#include <p24fj128ga010.h>

#define US_SCALE 8
#define MS_SCALE 333L

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

void dutyCyclePWM(unsigned int dutyCycle)
{
    if(dutyCycle<PR2)
        OC2RS=dutyCycle; //update duty cycle
    else
        OC2RS=OC2RS;
}

void initPWM1(unsigned int period)
{
    PR2=period; //set period
    OC2RS=0x0000; //next high time is zero
    OC2R=0x0000; //present high time is zero
    OC2CONbits.OCTSEL=0; //use timer 2
    OC2CONbits.OCM=6; //PWM without fault pin
    TMR2=0;
    T2CONbits.TCS=0; //Fcyc clock source
    T2CONbits.TGATE=0; //no timer gate
    T2CONbits.TCKPS=0; //prescaer 1:1
    T2CONbits.TON=1; //turn on timer 2
}