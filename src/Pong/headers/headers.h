/*
 * headers.h
 *
 * Created: 05/06/2019 14:49:49
 *  Author: Alessio Portaro
 */ 


#ifndef HEADERS_H_
#define HEADERS_H_

// C language includes
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// AVR includes

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <avr/pgmspace.h>

//I2C monitor library

#include "../i2c_library/src/lcdpcf8574/lcdpcf8574.h"

//Custom headers includes

//#ifndef CONSTANTS_H_
	#include <constants.h>
//#endif

//#ifndef STRUCTS_H_
	#include <structs.h>
//#endif

//#ifndef PHYSIC_H_
	#include <physic.h>
//#endif

//#ifndef GLOBALVARIABLES_H_
	#include <globalVariables.h>
//#endif

//#ifndef AVRUTILS_H_
	#include <avrUtils.h>
//#endif

#include <spiConverter.h>


#endif /* HEADERS_H_ */