/* 
 * File:   main.c
 * Author: Alex Lindemann
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "fileIO.h"
#include "BruteForce.h"
#include "GA.h"

//PROTOTYPES FOR HELPER FUNCTIONS
void copyArray(int *, int *, int);
void getOriginalPermutation(int *, int );
void reverseArray(int *, int *, int);
int arrayEquals(int *, int *, int );




int main(void) {

    //BUILD GRAPH
    double city_weight_list[380];
    getCityWeights(city_weight_list);
    MatrixP my_matrix = newMatrix();
    buildMatrix(my_matrix, city_weight_list);
    //END BUILD GRAPH
    
    //GET PRESETS FROM FILE
    PresetsP presets = getPresets();
    //END GET PRESETS FROM FILE
    
    //CREATE NEEDED PERMUTATIONS
    int original_permutation[presets->amount_of_cities + 1];
    int current_permutation[presets->amount_of_cities + 1];
    int ending_permutation[presets->amount_of_cities + 1];
    int best_permutation[presets->amount_of_cities + 1];
    //END CREATE NEEDED PERMUTATIONS
    
    //INITIALIZE PERMUTATIONS
    getOriginalPermutation(original_permutation, presets->amount_of_cities);
    copyArray(current_permutation, original_permutation, presets->amount_of_cities);
    reverseArray(ending_permutation, original_permutation, presets->amount_of_cities );
    //END INITIALIZE PERMUTATIONS
    
    /*
     * Sets best cost to first tour cost of the generation to start off with. 
     */
    double best_cost;
    double current_permutation_tour_cost;
    best_cost = getTourCost(current_permutation, my_matrix, presets->amount_of_cities);
    
    
    
    //BRUTE FORCE
    clock_t BF_start = clock();
    while(arrayEquals(current_permutation, ending_permutation, presets->amount_of_cities) == -1){
        PermuteIter(presets, current_permutation);
        current_permutation_tour_cost = getTourCost(current_permutation, my_matrix, presets->amount_of_cities);
        if(current_permutation_tour_cost < best_cost){
            best_cost = current_permutation_tour_cost;
            copyArray(best_permutation, current_permutation, presets->amount_of_cities);
        }
    }
    current_permutation_tour_cost = getTourCost(ending_permutation, my_matrix, presets->amount_of_cities);
    if(current_permutation_tour_cost < best_cost){
            best_cost = current_permutation_tour_cost;
            copyArray(best_permutation, current_permutation, presets->amount_of_cities);
    }
    clock_t BF_end = clock();
    clock_t BF_ELAPSED = BF_end - BF_start;
    // END BRUTE FORCE
    
    
    //START GENETIC ALGORITHM
    GAStatsP stats = newGAStats();
    startGeneticAlgorithm(stats, presets, my_matrix,  original_permutation);
    //END GENETIC ALGORITHM
    
    //PRINT STATISTICS
    fprintf(stderr, "Optimal Cost from BF = %.2lf\n", best_cost);
    fprintf(stderr, "BF Time              = %.3lf\n", (double)BF_ELAPSED * 1000/ CLOCKS_PER_SEC);
    fprintf(stderr, "GA Cost              = %i\n", stats->cost);
    fprintf(stderr, "GA Time              = %.3lf\n", (double)stats->elapsed * 1000/ CLOCKS_PER_SEC);
    fprintf(stderr, "Percent Optimal      = %.2lf\n", (double)stats->cost / best_cost * 100);
    //END PRINT STATISTICS
    
    return (0);
}

void copyArray(int *dest, int *src, int size){
    int i;
    for(i = 0; i <= size; i++)
        dest[i] = src[i];
}

int arrayEquals(int *first, int *second, int size){
    
    int i;
    for(i = 0; i <= size; i++){
        if(first[i] != second[i]) return -1;
    }
    return 1;
}

void reverseArray(int *dest, int *src, int size){
    int i;
    for(i = 0; size > 0; size--, i++){
        dest[i] = src[size - 1];
    }

}


void getOriginalPermutation(int *array, int amount){
    int i;
    for(i = 0; i < amount; i++){
        array[i] = i;
    }
    array[i] = 0;
}





