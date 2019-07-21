/*
 * avrUtils.c
 *
 * Created: 06/06/2019 18:16:28
 *  Author: Alessio Portaro
 */ 

#include <headers.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define CONVERTED_WIDTH ((MAP_WIDTH-1)/5)+1
#define CONVERTED_HEIGHT ((/*MH*/(MAP_HEIGHT-1)/*MH*//8)+1)*8
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

void initI2CMonitor(void){
	
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	lcd_home();
	uint8_t led = 0;
	lcd_led(led);
	int Pin4_SDA = 4, Pin5_SCL = 5;
	//Configure portc for output of twi
	DDRC |= (1<<Pin4_SDA)|(1<<Pin5_SCL);
}

void displayMapLCD(void){
	
	volatile int display_line,display_char,char_line;
	/*DEBUG*/
	//volatile int ret_value;
	//volatile uint8_t char_sum;
	char str[5];
	/*DEBUG*/
	
	/*Workaround corrupted CGRAM[2]*/
	const uint8_t SUP_MAP_CHAR_EMPTY  [8] = {
		0b00011111,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000}; 
	
	/**/
	
	uint8_t char_address = 0;
	spiConvert(map,converted);
	
	cgram1_empty = 1;
	cgram2_empty = 1;
	
	for(display_line = 0;display_line<2;display_line++)
		for(display_char = 0;display_char<4;display_char++){
			
			for(char_line = 0;char_line<8;char_line++){
				custom_char[display_line][display_char].value[char_line]=converted[(display_line*8)+char_line][display_char];
				if(custom_char[display_line][display_char].value[char_line]!=SUP_MAP_CHAR_EMPTY[char_line] && char_address==1)
					cgram1_empty = 0;
				if(custom_char[display_line][display_char].value[char_line]!=SUP_MAP_CHAR_EMPTY[char_line] && char_address==2)
					cgram2_empty = 0;
			}
			char_address++;
		}
			
	char_address = 0;
			
	for(display_line = 0;display_line<2;display_line++)
		for(display_char = 0;display_char<4;display_char++){
			
			if(cgram1_empty && !cgram2_empty && char_address==1){
				lcd_gotoxy(display_char+8,display_line);
				lcd_putc(' ');
				char_address++;
				continue;
			}
			
			
			lcd_create_custom_char(char_address,custom_char[display_line][display_char].value);
			/**/
			
			if(char_address==2){
				if(cgram1_empty && cgram2_empty){
					lcd_gotoxy(display_char+8,display_line);
					lcd_putc(char_address-1);
					char_address++;
					continue;
				}
				if(cgram1_empty){
					lcd_create_custom_char(char_address-1,custom_char[display_line][display_char].value);
					lcd_gotoxy(display_char+8,display_line);
					lcd_putc(char_address-1);
					char_address++;
					continue;
				}
				if(cgram2_empty){
					lcd_gotoxy(display_char+8,display_line);
					lcd_putc(' ');
					char_address++;
					continue;
				}
			}
			lcd_gotoxy(display_char+8,display_line);
			lcd_putc(char_address);
			/**/
			
			char_address++;
		}
		
		/*DEBUG*/
		sprintf(str,"%d",cgram1_empty);
		lcd_gotoxy(0,0);
		lcd_puts("        ");
		//lcd_puts(str);
		sprintf(str,"%d",cgram2_empty);
		lcd_gotoxy(0,1);
		lcd_puts("       ");
		//lcd_puts(str);
		/*DEBUG*/
}

void debugPrintLCD(const char* string){
	lcd_home();
	lcd_puts(string);
	lcd_gotoxy(0,1);
	lcd_puts("                ");
}
