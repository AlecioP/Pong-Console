#include <spiConverter.h>
/*DEBUG*/
#include <stdio.h>
/*DEBUG*/

void spiConvert(uint8_t map[MAP_HEIGHT][MAP_WIDTH],uint8_t converted[16][4]){
    int r,c,x,offset;
    
    
    
    uint8_t converted_buff;
	
	uint8_t *work_array;

    for(r=0;r<16;r++){
        

        for(c=0;c<4;c++){
            converted_buff = 0x00;
            offset = c*5;
            work_array = &(map[r][offset]);
            for(x=0;x<5;x++){
                if(work_array[5-1-x]==TRUE)
                    converted_buff|=(1<<x);
            }
            converted[r][c] = converted_buff;
        }//FOR COLS
        
        
    }//FOR ROWS
    
}//SPI_CONVERT


