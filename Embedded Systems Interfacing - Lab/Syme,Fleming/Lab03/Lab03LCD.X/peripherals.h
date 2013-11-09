#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#define POT_CHANNEL 5
#define AN_POT_PIN AD1PCFGbits.PCFG5
#define TEMP_CHANNEL 4
#define AN_TEMP_PIN AD1PCFGbits.PCFG4

#define US_SCALE 8
#define MS_SCALE 333L

void initADC(unsigned int initChannel);
unsigned int getADC(unsigned int channel);
void initButtons(unsigned int mask);
unsigned int getButton(unsigned int mask);
void _10usDelay(unsigned char _10us);
void msDelay(unsigned int ms);
void initBargraph(void);
void setBargraph(unsigned int display);
void initPMP(void);
void initLCD(unsigned char);
void cmdLCD(char);
void putLCD(char);

#endif
