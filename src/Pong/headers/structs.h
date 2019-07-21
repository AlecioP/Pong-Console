/*
 * structs.h
 *
 * Created: 05/06/2019 14:53:30
 *  Author: Alessio Portaro
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct ball_str {
	int x;
	int y;
	int vx;
	int vy;
} ball;

typedef struct racket_str
{
	int x;
	int y;
} racket;

typedef struct LCD_CHARACTER {
	uint8_t value[8];
} lcd_char;


#endif /* STRUCTS_H_ */