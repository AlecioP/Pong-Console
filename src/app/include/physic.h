/*
 * physic.h
 *
 * Created: 05/06/2019 16:42:03
 *  Author: Alessio Portaro
 */ 


#ifndef PHYSIC_H_
#define PHYSIC_H_
#include <headers.h>

void moveball(ball*,racket,racket,uint8_t map[MAP_HEIGHT][MAP_WIDTH],int*,int*);

void moveracket(int direction,racket* rkt,uint8_t map[MAP_HEIGHT][MAP_WIDTH]);

void autoMove(uint8_t map[MAP_HEIGHT][MAP_WIDTH],int DIFFICULTY,racket* r,ball b);

void gameover(int* GO ,int LPP,int RPP,int* WINNER);



#endif /* PHYSIC_H_ */