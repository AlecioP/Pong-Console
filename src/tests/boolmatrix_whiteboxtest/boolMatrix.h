/*
 * boolMatrix.h
 *
 * Created: 05/06/2019 14:54:28
 *  Author: Alessio Portaro
 */ 


#ifndef BOOLMATRIX_H_
#define BOOLMATRIX_H_

#include <stdint.h> /*To use int8_t */
#include <stdlib.h> /*To use calloc() & free() */

int8_t** bool_matrix_init(int8_t** matrix,int rows,int cols);

void bool_matrix_free(int8_t** matrix,int rows);

void bool_matrix_set_value(int8_t** matrix,int row,int col,int value);

int bool_matrix_get_value(int8_t** matrix,int row,int col);




#endif /* BOOLMATRIX_H_ */
