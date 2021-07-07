## Display library

A simple test to explain the usage of i2c display

~~~c
#include <avr/io.h>


int main(void)
{
    /* scl frequency Should be >10 if in master mode*/
	TWBR = 0x00;
	 
	/*Bitrate prescaler bits*/ 
	TWSR = (1<<TWPS1)|(1<<TWPS1);
	
	/*
	* TWINT -> Auto-set when i2c finshes. This will cause ISR (If enabled). 
	*		   Clearing it by software will start i2c operation
	* 
	* TWEA -> Enable ACKs
	* TWSTA -> In master mode setting this bit will generate START condition 
	* TWSTO -> //											 STOP //
	* TWWC -> If set there was an error. Someone tried to access data register while transmission was on
	* TWEN -> Enable peripheral 
	* TWIE -> Enable Interrupts
	*
	*
	*/
	
	/*
	* i2c init : 
	*				1) Set SCL Freq
	*				2) Set Bitrate Prescaler
	*				3) Enable Peripheral
	*
	*/
	
	/*
	* i2c send data
	*				1) Send START condition
	*				2) Set TWINT (which means logically clearing it, for the reverse logic of this pin)
	*
	*					When TWINT is set again the start was transmitted then :
	*
	*				3) Write data in TWDR
	*				5) Set TWINT 
	*
	*					When TWINT is set again the data was transmitted then :
	*
	*				6) Send STOP condition
	*				7) Set TWINT
	*/
	/*
	*	VERY IMPORTANT :
	*				The first data transmitted must be SLA + W (or SLA + R = in read mode) 
	*					meaning we want to write on the channel and specifies the address of 
	*					the slave we want to communicate with.
	*					Since an address is a 7bit string we will write that plus 1bit
	*					which will be 0 in write mode (or 1 in read mode)
	*
	*
	**/
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWSTA)|(1<<TWSTO)|(1<<TWWC)|(1<<TWEN)|(1<<TWIE);
	
	/*Data register*/
	TWDR = 0x00;
	/*Address register -> 7bit*/
	TWAR = 0x00;
    while (1) 
    {
    }
}
~~~

## Bibliography

- [Cables on Raspberry _pic16f628a_](https://www.youtube.com/watch?v=1p1rgkslO0U&t=387s)
- [Pinout of Raspberry _pic16f628a_](http://www.onlinepiccompiler.com/PinOut16f628aENG.html)
- [Pinout Arduino Uno](https://upload.wikimedia.org/wikipedia/commons/c/c9/Pinout_of_ARDUINO_Board_and_ATMega328PU.svg)
- [Basics of Avr and I2C tutorial](https://www.exploreembedded.com/wiki/Basics_of_I2C_with_AVR)
- [LCD Pins Explained](https://focuslcds.com/journals/lcd-voltage-inputs-for-lcd-displays-explained/)
- [Qapass _1602a_ LCD controller datasheet _ST7066U_](https://electronics.stackexchange.com/questions/170557/lcd-16-x-2-1602a-interfacing)