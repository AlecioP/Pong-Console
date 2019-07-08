/*
 * interruptRoutines.c
 *
 * Created: 05/06/2019 17:07:46
 *  Author: Alessio Portaro
 */ 
#include <headers.h>


ISR(INT0_vect){
	//The switch for instruction GO_UP was pressed
	
	
	int PC_0 = 0;
	int PC_1 = 1;
	racket* left_p = &left;
	if((PINC & (1<<PC_0))!=0){
		moveracket(GO_DOWN,left_p,map);
		return;
	}
	if(( PINC &(1<<PC_1))!=0){
		moveracket(GO_UP,left_p,map);
		return;
	}
	
		
	//DDRB = 0xFF;
	//PORTB = 0x00;
	//DDRB = 0XFC;
}

ISR(TIMER0_COMPA_vect){
	if(TIMER_COUNT<45*3){//45 = 2D FF 
		TIMER_COUNT++;
		return;
	}
	else
	TIMER_COUNT = 0;
	
	racket* right_p = &right;
	ball* b_p = &b;
	int* LPP_p=&LEFT_PLAYER_POINTS;
	int* RPP_p=&RIGHT_PLAYER_POINTS;
	
	autoMove(map,DIFFICULTY,right_p,b);
	moveball(b_p,right,left,map,LPP_p,RPP_p);
	
	if(ACTUALLY_TRANSMITTED_BYTES == 0 && ENTER_USART_INTERRUPT){
		UDR0 = TRANSMISSION_START;
		ENTER_USART_INTERRUPT = 0;
	}
	
}

ISR(USART_TX_vect){
	ENTER_USART_INTERRUPT = 1;
	if(!START_TRANSMITTED){
		UDR0 = map[0][0];
		START_TRANSMITTED = 1;
		return;
	}
	volatile int bytes_per_row = MAP_WIDTH;
	volatile int total_to_transmit = MAP_HEIGHT * bytes_per_row;
	ACTUALLY_TRANSMITTED_BYTES++;
	if(ACTUALLY_TRANSMITTED_BYTES!=total_to_transmit){
		UDR0 = map[(ACTUALLY_TRANSMITTED_BYTES)/bytes_per_row][(ACTUALLY_TRANSMITTED_BYTES)%bytes_per_row];
	}else{
		ACTUALLY_TRANSMITTED_BYTES = 0;
		START_TRANSMITTED = 0;
		return;
	}
}
