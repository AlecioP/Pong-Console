#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include "boolMatrix.h"


void convertToBinary(char* container,int8_t value){
    int i;
    for(i=0;i<8;i++){
        //printf("Accessing container[%d]",i);
        if( value & (/**/1<<(7-i)/**/) )
            container[i]='D';
        else
            container[i]='_';
    }
}

void printMap(int8_t** map,int h,int w){
    //printf("\nEnter print map\n");
    int i,j,convertedCols;
    convertedCols= w-1;
    convertedCols /=8;
    convertedCols++;
    
    char* container = (char*) calloc(8,sizeof(char));
    
    for(i=0;i<h;i++){
        for(j=0;j<convertedCols;j++){
            //printf("\nAccessing map[%d][%d]\n",i,j);
            convertToBinary(container,map[i][j]);
            //printf("\nConverted!\n");
            printf("%s",container);
        }
        printf("\n");
    }
    free(container);
}



int main(int argc,char** argv){
    int a,b;
    
    
    printf("\nArgc : %d. First is %s\n",argc,argv[0]);
    
    char* endptr;
    
    if(argc!=3){
        printf("\nUnexpected number of args! Exit -1\n");
        return -1;
    }
    
    int w = (int) strtoimax(argv[1],&endptr,10);
    
    int h = (int) strtoimax(argv[2],&endptr,10);
   
    printf("\n Argv[1] = %d\n",w);
    printf("\n Argv[2] = %d\n",h);
    
    int8_t** map;
    
    map = bool_matrix_init(map,h,w);

    if(map == 0){
    	printf("\nFailed calloc\n");
    	return -1;
    }
    if(map[0]==0){
    	printf("\nFailed calloc maybe\n");
    	return -1;
    }
    
    int response;
    
    printf("\nContinue?([-1] -> No | Everything else -> Yes)\n");
    scanf("%d",&response);
    
    while(response != -1){
        printf("\nInsert row column and value to set (Like : 4 5 0 or 4 5 1)\n");
        int row,col,value;
        scanf("%d %d %d",&row,&col,&value);
        if(value!=0)
            value = 1;
        
        bool_matrix_set_value(map,row,col,value);
        
        printMap(map,h,w);
        
        /**/
        printf("\nContinue?([-1] -> No | Everything else -> Yes)");
        scanf("%d",&response);
        /**/
    }
    
    bool_matrix_free(map,h);
    
    return 0;
}
