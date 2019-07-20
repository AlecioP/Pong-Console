/*
* Pong.c
*
* Created: 04/06/2019 15:32:45
* Author : Alessio Portaro
*/
#include <headers.h>

int main(void){
	
	
	
	int i,j;
	srand(time(0));
	
	DIFFICULTY = DIFFICULTY%MAP_WIDTH;
	
	/*CREATE TOP AND BOTTOM WALLS*/
	for(i=0;i<MAP_HEIGHT;i++){
		for(j=0;j<MAP_WIDTH;j++){
			map[i][j]=FALSE;
			if(i==0 || i==MAP_HEIGHT-1)
				map[i][j]=TRUE;
		}
	}
	
	/*Placing ball in map*/
	map[b.y][b.x]=TRUE;
	/*Placing right racket in map*/
	map[right.y][right.x]=TRUE;
	map[right.y+1][right.x]=TRUE;
	map[right.y+2][right.x]=TRUE;
	/*Placing left racket in map*/
	map[left.y][left.x]=TRUE;
	map[left.y+1][left.x]=TRUE;
	map[left.y+2][left.x]=TRUE;
	
	initI2CMonitor();
	//debugPrintLCD("INIT");
	initTimer();
	initExternalInterrupts();
	//initUSARTCommunication();
	
	sei();
	
	//CPU in sleep mode
	//set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	//sleep_enable();
	//sleep_cpu();
	while(1){}
	
	return 0;
}
