/*
 * globalVariables.c
 *
 * Created: 03/07/2019 13:15:10
 *  Author: Alessio Portaro
 */ 
#include <headers.h>


ball b = {.x=MAP_WIDTH/2,.y=MAP_HEIGHT/2,.vx=1,.vy=0};
racket left={.x=1,.y=MAP_HEIGHT/2};
racket right={.x=MAP_WIDTH-2,.y=MAP_HEIGHT/2};
uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {{0}};

//left  ;

//right ;

int WINNER = -1;
int LEFT_PLAYER_POINTS=0;
int RIGHT_PLAYER_POINTS=0;
int GAME_OVER=0;
int ACTUALLY_TRANSMITTED_BYTES=0;
int START_TRANSMITTED=0;
int ENTER_USART_INTERRUPT=1;
int DIFFICULTY = 15;
//map = { { 0 } };
/**/

uint8_t TRANSMISSION_START = 0b10101010;
uint8_t TRUE = 0b00000001;
uint8_t FALSE = 0b00000000;

int TIMER_COUNT = 0;