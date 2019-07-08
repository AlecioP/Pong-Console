#include <spiConverter.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char** argv){
    uint8_t map[MAP_HEIGHT][MAP_WIDTH];
    srand(time(0));
    int r,c;
    printf("\n INPUT MATRIX : \n");
    for(r=0;r<MAP_HEIGHT;r++){
        for(c=0;c<MAP_WIDTH;c++){
            int value = rand()%2;
            if(value){
                map[r][c]=TRUE;
                printf(" T");
            }
            else{
                map[r][c]=FALSE;
                printf(" F");
            }
        }
        printf("\n");
    }
    uint8_t converted [CONVERTED_HEIGHT][CONVERTED_WIDTH];
    spiConvert(map,converted);
    debug_LCD_display(converted);
    printf("\n SIZE OF INPUT = %d . SIZE OF OUTPUT = %d \n",sizeof(map),sizeof(converted));
    return 0;
}
