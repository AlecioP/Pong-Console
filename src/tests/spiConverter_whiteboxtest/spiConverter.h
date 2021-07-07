#include<inttypes.h>
#include<constants.h>
#include<globalVariablesCHANGED.h>
#define CONVERTED_WIDTH ((MAP_WIDTH-1)/5)+1
#define CONVERTED_HEIGHT ((/*MH*/(MAP_HEIGHT-1)/*MH*//8)+1)*8

void spiConvert(uint8_t map[MAP_HEIGHT][MAP_WIDTH],uint8_t converted[CONVERTED_HEIGHT][CONVERTED_WIDTH]);

void debug_LCD_display(uint8_t converted[CONVERTED_HEIGHT][CONVERTED_WIDTH]);
