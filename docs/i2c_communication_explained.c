/*
 * TestDisplay.c
 *
 * Created: 08/07/2019 22:53:27
 * Author : Alessio Portaro
 */ 

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

