/*
 * avrUtils.c
 *
 * Created: 06/06/2019 18:16:28
 *  Author: Alessio Portaro
 */ 

//#include "headers.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*
	*	To have a delay of 0.1 seconds with XTAL = 1 MHz
	*
	*	F = 10^6 Hz -> T=1/F -> T = 10^(-6)s 
	*	With a prescaler of 1024 it means 
	*	every 1024 periods (T) TCNT is incremented of 1
	*	For this reason TCNT is incremented every 1024*[10^(-6)] s
	*	
	*	We want a delay of 10^(-1). 
	*	How many times we must increment TCNT value ?
	*
	*	The answer is 10^(-1)/{1024*[10^(-6)]} ~= 97
	*	
	*
	*	VALUE = DESIRED_DELAY / (PRESCALER/XTAL)
	*/ 
void initTimer(void){
	// Set CS02 and CS01 to have clk/1024 prescaler
	// Set WGM01 to have CTC Mode
	TCCR0B = (1<<CS02)|(1<<CS00);
	TCCR0A = (1<<WGM01);
	//Reset Timer 
	TCNT0 = 0;
	//volatile F_CPU = 16*(1024)*(1024);
	volatile int VALUE = /*0.1 / (1024/F_CPU)*/255;
	
	OCR0A = VALUE;
	
	//Enable interrupt on Timer0 output compare match
	TIMSK0=(1<<OCIE0A);
}

void initExternalInterrupts(void){
	
	
	DDRC = 0b11111100;
	PORTC = 0x03;
	//DDRB = (1<<1)|(1<<0);
	
	//Let interrupt pin receive inputs
	DDRD = 0b11111011;
	//DDRD = (1<<2);
	
	//External interrupt enable
	EIMSK = (1<<INT0);
	
	//Trigger mode in falling edge for INT0
	EICRA = (1<<ISC01)|(1<<ISC00);
}

void initUSARTCommunication(void){
	
	//2400 baud at 16MHz
	unsigned int baud_rate = 416;
	
	//UCSRA (Usart Control Status Register A) has only bits set automatically
	
	//Enable interrupt when transmission buffer empty. Enable USART transmitter
	UCSR0B = (1<<TXCIE0)|(1<<TXEN0);
	
	//Synch mode - Even Parity - 8bit character [USBS is 0, meaning there is only 1 start/stop bit]
	UCSR0C = /*(1<<UMSEL00)|(1<<UPM01)|(1<<UPM00)|*/(1<<UCSZ01)|(1<<UCSZ00);
	
	//9600 baud rate for XTAL = 8 MHz (Standard baud rate I think, not any particular calculation)
	
	//UBRR0H = (unsigned char) (baud_rate>>8);
	//UBRR0L = (unsigned char) (baud_rate); 
	UBRR0 = baud_rate;
}
