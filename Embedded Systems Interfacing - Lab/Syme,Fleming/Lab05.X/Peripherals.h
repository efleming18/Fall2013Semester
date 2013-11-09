#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#define POT_CHANNEL 5
#define AN_POT_PIN AD1PCFGbits.PCFG5
#define TEMP_CHANNEL 4
#define AN_TEMP_PIN AD1PCFGbits.PCFG4
#define SPEED_CHANNEL 3
#define AN_SPEED_PIN AD1PCFGbits.PCFG3

#define US_SCALE 8
#define MS_SCALE 333L
#define LCD_CLEAR 1
#define LCD_HOME 2
#define CURSOR_ON	2
#define CURSOR_OFF	0
#define CURSOR_BLINK 3

void PWMdutyCycle(unsigned int dutyCycle);
void initPWM1(unsigned int period);
unsigned int write(int handle, void *buffer, unsigned int len);
void cmdLCD(unsigned char cmd);
void putLCD(unsigned char ch);
void initLCD(unsigned char cursor);
void initPMP(void);
void initADC(unsigned int initChannel);
unsigned int getADC(unsigned int channel);
void initButtons(unsigned int mask);
unsigned int getButton(unsigned int mask);
void _10usDelay(unsigned char _10us);
void msDelay(unsigned int ms);
void initBargraph(void);
void setBargraph(unsigned int display);

#endif
