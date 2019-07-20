/*
 * avrUtils.h
 *
 * Created: 06/06/2019 18:15:23
 *  Author: Alessio Portaro
 */ 


#ifndef AVRUTILS_H_
#define AVRUTILS_H_

void initTimer(void);

void initExternalInterrupts(void);

void initUSARTCommunication(void);

void initI2CMonitor(void);

void displayMapLCD(void);

void debugPrintLCD(const char* string);

#endif /* AVRUTILS_H_ */
