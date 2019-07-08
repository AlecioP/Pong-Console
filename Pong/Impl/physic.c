/*
 * physic.c
 *
 * Created: 05/06/2019 15:20:09
 *  Author: Alessio Portaro
 */ 


#include <headers.h>

void moveball(ball* b,racket r,racket l,uint8_t map[MAP_HEIGHT][MAP_WIDTH],int* LPP, int* RPP){
	
	map[b->y][b->x]=FALSE;
	if(( (b->x)+(b->vx) )== 0){
		(*RPP)++; //RIGHT PLAYER SCORES
		b->y = MAP_HEIGHT/2;
		b->x = MAP_WIDTH/2;
		b->vy = 0;
		b->vx = -1;//Who concedes a goal gets a free kick
		
		map[b->y][b->x]=TRUE;
		return;
	}
	
	if(( (b->x)+(b->vx) )== (MAP_WIDTH-1)){
		(*LPP)++; //LEFT PLAYER SCORES
		b->y = MAP_HEIGHT/2;
		b->x = MAP_WIDTH/2;
		b->vy = 0;
		b->vx = 1;//Who concedes a goal gets a free kick
		
		map[b->y][b->x]=TRUE;
		return;
	}
	
	
	if(( (b->x)+(b->vx) )== l.x){//LEFT RACKET HIT
		
		if(b->y == l.y){
			b->vy =-1;
			b->vx = 1;
			map[b->y][b->x]=TRUE;
			return;
		}else if(b->y == l.y+1){
			b->vy = 0;
			b->vx = 1;
			map[b->y][b->x]=TRUE;
			return;
		}else if(b->y == l.y+2){
			b->vy = 1;
			b->vx = 1;
			map[b->y][b->x]=TRUE;
			return;
		}
		
	}
	
	if(( (b->x)+(b->vx) )== r.x){//RIGHT RACKET HIT
		
		if((b->y) == (r.y)){
			b->vy =-1;
			b->vx =-1;
			map[b->y][b->x]=TRUE;
			return;
		}else if((b->y) == (r.y+1)){
			b->vy = 0;
			b->vx =-1;
			map[b->y][b->x]=TRUE;
			return;
		}else if((b->y) == (r.y+2)){
			b->vy = 1;
			b->vx =-1;
			map[b->y][b->x]=TRUE;
			return;
		}
	}
	int debug = 0;
	while(debug<10){
		debug++;
		/*
		 * IF NEXT CELL IS FREE THAN BALL MOVES NORMALLY. 
		 * OTHERWISE THE BALL BOUNCES AND THAN CAN MOVE NORMALLY. 
		 * FOR THIS REASON THE "while(true)"
		 */
		volatile int GET = map[(b->y)+(b->vy)][(b->x)+(b->vx)];
		if(GET == FALSE){
			(b->y)+=(b->vy);
			(b->x)+=(b->vx);
			map[b->y][b->x]=TRUE;
			return;
		}
		
		if(( (b->y)+(b->vy) )== 0)
			(b->vy) = 1;
		if(( (b->y)+(b->vy) )== (MAP_HEIGHT-1))
			(b->vy) = -1;
	}
	
}

void moveracket(int direction,racket* rkt,uint8_t map[MAP_HEIGHT][MAP_WIDTH]){
		volatile int debug_dir = direction;
		
		if(debug_dir==GO_UP){
			
			if(map[(rkt->y)+debug_dir][rkt->x]==FALSE){
				
				map[(rkt->y)+2][rkt->x] = FALSE;
				
				map[(rkt->y)+debug_dir][rkt->x] = TRUE;
				
				(rkt->y)=(rkt->y)+debug_dir;
			}
			
		}else if(debug_dir==GO_DOWN){
			
			if(map[(rkt->y)+2+debug_dir][rkt->x]==FALSE){
				
				map[rkt->y][rkt->x]=FALSE;
				
				map[(rkt->y)+2+debug_dir][rkt->x]=TRUE;
				
				(rkt->y)=(rkt->y)+debug_dir;
			}
			
		}
	
}

void autoMove(uint8_t map[MAP_HEIGHT][MAP_WIDTH],int DIFFICULTY,racket* r,ball b){
	if(b.x < DIFFICULTY)
		return;
	
	
	int rnd = rand()%2;
	
	if(rnd==0)
		return;
	
	if(r->y+1<b.y)
		moveracket(GO_DOWN,r,map);
	else if(r->y+1>b.y)
		moveracket(GO_UP,r,map);
}

void gameover(int* GAME_OVER,int LPP,int RPP,int* WINNER){
	if(LPP>=GAME_OVER_LIMIT){
		(*GAME_OVER)=TRUE;
		(*WINNER) = LEFT_PLAYER;
	}
	if(RPP>=GAME_OVER_LIMIT){
		(*GAME_OVER)=TRUE;
		(*WINNER) = RIGHT_PLAYER;
	}
}
