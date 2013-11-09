#include "peripherals.h"
#include <p24fj128ga010.h>

void PWMdutyCycle(unsigned int dutyCycle){
	OC1RS=dutyCycle;
	}

void initPWM1(unsigned int period){
	PR2=period;				//set period
	OC1RS=0x0000;			//next high time is zero
	OC1R=0x0000;			//present high time is zero
	OC1CONbits.OCTSEL=0;	//use timer 2
	OC1CONbits.OCM=6;		//PWM without fault pin
	T2CONbits.TCS=0;		//Fcyc clock source
	T2CONbits.TGATE=0;		//no timer gate
	T2CONbits.TCKPS=0;		//prescaer 1:1
	T2CONbits.TON=1;		//turn on timer 2
	}

unsigned int write(int handle, void *buffer, unsigned int len){
	int cnt;
	char ch;
	static unsigned char virtualCursor=0x80;
	Nop();
	switch(handle){
		case 0:					//standard in not yet implemented
				len=0;
				break;
		case 1:					//standard out
				for(cnt=len;cnt >0; --cnt){
					ch=*(char *)buffer++;
   					switch(ch) {
						case '\n' :
							if(virtualCursor < 0x90)
								virtualCursor=0xC0;
							else
								virtualCursor=0x80;
							cmdLCD(virtualCursor);
							break;
						case '\t' : virtualCursor=(virtualCursor+4)&0b11001100;
							cmdLCD(virtualCursor);
							break;
						case '\v' :	virtualCursor=virtualCursor^0b01000000;
							cmdLCD(virtualCursor);
							break;
						case '\b' : if(virtualCursor == 0x80)
								virtualCursor=0x80;
							else if(virtualCursor==0xC0)
								virtualCursor=0xC0;
							else
								virtualCursor=virtualCursor-1;
							cmdLCD(virtualCursor);
							putLCD(' ');
							cmdLCD(virtualCursor);
							break;
						case '\r' :	virtualCursor=virtualCursor&0b11110000;
							cmdLCD(virtualCursor);
							break;
						case '\f' : cmdLCD(LCD_CLEAR);
							virtualCursor=0x80;
							break;
						default :
							virtualCursor=(virtualCursor+1)&0b11001111;
							putLCD(ch);
						}
					}
				break;
		case 2:					//standard error not yet implemented
				len = 0;
				break;
		default:
				len = 0;
				}
		return(len);
	}

void cmdLCD(unsigned char cmd){
	switch(cmd){
		case LCD_CLEAR:
		case LCD_HOME:
				PMADDR=0x0000;
				PMDIN1=cmd;
				msDelay(2);
				break;
		default:
				PMADDR=0x0000;
				PMDIN1=cmd;
				_10usDelay(5);
		}
	}

void putLCD(unsigned char ch){
	PMADDR=0x0001;
	PMDIN1=ch;
	_10usDelay(5);
	}

void initLCD(unsigned char cursor){
	msDelay(100);		// power-on wait
	PMADDR=0;			//select command registers
	PMDIN1=0b00111100;	//8-bit function set
	_10usDelay(5);		// fast instruction
	PMDIN1=0b00001100|cursor;	// Display on, cursor ctrl, blink ctrl
	_10usDelay(5);		// fast instruction
	PMDIN1=0b00000001;	// home cursor
	msDelay(2);			// slow instruction
	PMDIN1=0b00000110;	//entry mode with no shift inc on
	msDelay(2);			//slow instruction
	}

void initPMP(void){
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

void initADC(unsigned int initChannel){
	AD1CON1=0x00E0;				//Turn off, auto sample, auto start, auto convert
	AD1CON2=0x0000;				//AVdd, AVss, int every conversion, MUXA only
	AD1CON3=0x1F05;				//31 auto-sample, Tad = 5 Tcy
	AD1CHS=initChannel;
	AD1CSSL=0;					//ignore all on scan select
	TRISBbits.TRISB3=1;
	TRISBbits.TRISB4=1;
	TRISBbits.TRISB5=1;
	AN_POT_PIN=0;				//disable digital input on AN5
	AN_TEMP_PIN=0;				//disable digital input on AN4
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

