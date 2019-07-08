#include <spiConverter.h>
/*DEBUG*/
#include <stdio.h>
/*DEBUG*/

void spiConvert(uint8_t map[MAP_HEIGHT][MAP_WIDTH],uint8_t converted[CONVERTED_HEIGHT][CONVERTED_WIDTH]){
    int r,c,x,y,offset;
    
    int CASE,   NORMAL_CASE = CONVERTED_WIDTH,  SPECIAL_CASE = (CONVERTED_WIDTH-1);
    
    uint8_t converted_buff, *work_array;
    
    if((MAP_WIDTH%5)==0)
        CASE = NORMAL_CASE;//No seg-fault if iterating until last 5-chunk
    else
        CASE = SPECIAL_CASE;//last 5-chunk must be converted in special way
    
    for(r=0;r<MAP_HEIGHT;r++){
        

        for(c=0;c<CASE;c++){
            converted_buff = 0x00;
            offset = c*5;
            work_array = &map[r][offset];;
            for(x=0;x<5;x++){
                if(work_array[5-1-x]==TRUE)
                    converted_buff|=(1<<x);
            }
            converted[r][c] = converted_buff;
        }//FOR COLS
        
        if(CASE==SPECIAL_CASE){
            int remaining_bits = MAP_WIDTH%5;
            converted_buff = 0x00;
            work_array = &map[r][MAP_WIDTH-remaining_bits];
            for(y=0;y<remaining_bits;y++){
                if(work_array[remaining_bits-1-y]==TRUE)
                    converted_buff|=(1<<(y+(5-remaining_bits)));
            }
            converted[r][SPECIAL_CASE]=converted_buff;
        }//IF SPECIAL CASE
    }//FOR ROWS
    for(;r<CONVERTED_HEIGHT;r++){
        for(c=0;c<CONVERTED_HEIGHT;c++)
            converted[r][c]=0x00;
    }
}//SPI_CONVERT

void debug_LCD_display(uint8_t converted[CONVERTED_HEIGHT][CONVERTED_WIDTH]){
    int r,c,x;
    printf("\nLCD Chars : \n");
    printf("\n");
    for(r=0;r<CONVERTED_HEIGHT;r++){
        for(c=0;c<CONVERTED_WIDTH;c++){
            uint8_t current = converted[r][c];
            for(x=0;x<5;x++)
                if(current & (1<<(5-1-x)))
                    printf(" 1");
                else
                    printf(" _");
            printf(" |");
        }
        printf("\n");
    }
    printf("\n");
}
