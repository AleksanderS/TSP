#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

MatrixP newMatrix(){
    MatrixP my_matrix = malloc(sizeof(struct matrix));
    return my_matrix;
}

/*
 * 2D array containing weights for a graph. Graph vertices will not contain connections to themselves.
 */
void buildMatrix(MatrixP graph, double city_weights_list[380]){
    int i,j,k;
    i = 0;
    for(j = 0; j<20; j++){
        
        for(k = 0; k<20; k++){
            if(j == k){
                graph->array[j][k] = 0; //city connection to itself
            }
            else {
                graph->array[j][k] = city_weights_list[i];
                i++;
            }
        }
    }
}