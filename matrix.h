/* 
 * File:   matrix.h
 * Author: Alex
 *
 * Created on October 19, 2015, 11:46 AM
 */

#ifndef MATRIX_H
#define	MATRIX_H

typedef struct matrix {
    
    double array[20][20];
    
    
} *MatrixP, matrix;

MatrixP newMatrix();
void buildMatrix(MatrixP, double *);



#endif	/* MATRIX_H */

