/*
 * boolMatrix.c
 *
 * Created: 05/06/2019 15:17:42
 *  Author: Alessio Portaro
 */ 

//#include "headers.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int8_t** bool_matrix_init(int8_t** matrix,int rows,int cols){
    int i,physicCols;
    printf("\nSizeof(int8_t)=%lu\n",sizeof(int8_t));
    printf("\nSizeof(int8_t*)=%lu\n",sizeof(int8_t*));
    fflush(stdout);
    matrix = (int8_t**) calloc(rows,sizeof(int8_t*));
    physicCols = ((cols-1)/8)+1;
    for(i=0;i<rows;i++)
        matrix[i] = (int8_t*) calloc(physicCols,sizeof(int8_t));
    printf("\nEnd bool_matrix_init \n");
    return matrix;
}

void bool_matrix_free(int8_t** matrix,int rows){
    int i;
    for(i=0;i<rows;i++)
        free(matrix[i]);
    free(matrix);
}

void bool_matrix_set_value(int8_t** matrix,int i,int j,int value){
    
    if(value!=0)
    /*
     *  Ho      : XXX
     *
     *  OR      : 010
     *
     *  voglio  : X1X
     */
        matrix[i][j/8] |= (1<<(7-(j%8)));
    else
    /*
     *  Ho      : XXX
     *
     *  AND     : 101
     *
     *  voglio  : X0X
     */
        matrix[i][j/8] &= ~(/**/1<<(7-(j%8))/**/);
    
}

int bool_matrix_get_value(int8_t** matrix,int i,int j){
    
    int8_t byte = matrix[i][j/8];
    
    /*
     *  Ho      : XXX
     *
     *  AND     : 010
     *
     *  voglio  : 0X0
     */
    
    byte &= (1<<(7-(j%8)));
    
    return byte;
    
}
