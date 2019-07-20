/*
 * globalVariables.h
 *
 * Created: 05/06/2019 17:17:46
 *  Author: Alessio Portaro
 */ 


#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_
#include <constants.h>
#include <structs.h>
#include <inttypes.h>
#include <spiConverter.h>

extern ball b;
extern racket left;
extern racket right;

extern int WINNER;
extern int DIFFICULTY;
extern int LEFT_PLAYER_POINTS, RIGHT_PLAYER_POINTS;
extern int GAME_OVER;

extern int ACTUALLY_TRANSMITTED_BYTES;
extern int START_TRANSMITTED;
extern int ENTER_USART_INTERRUPT;

extern uint8_t map[MAP_HEIGHT][MAP_WIDTH];

extern uint8_t TRANSMISSION_START;
extern uint8_t TRUE;
extern uint8_t FALSE;

extern int TIMER_COUNT;


//LCD MONITOR

extern uint8_t custom_char[8][8];

#endif /* GLOBALVARIABLES_H_ */