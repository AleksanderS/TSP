/* 
 * File:   GA.h
 * Author: Alex
 *
 * Created on October 22, 2015, 6:06 PM
 */

#ifndef GA_H
#define	GA_H
#include <time.h>
#include "fileIO.h"
#include "matrix.h"
typedef struct {
    clock_t start;
    clock_t end;
    clock_t elapsed;
    int cost;
    double percent_optimal;
}*GAStatsP, GAStats;
struct Permutation {
    int *perm;
    double tour_cost;
    
};

void geneticAlgorithmPerm1(int *, int );
void startGeneticAlgorithm(GAStatsP , PresetsP ,MatrixP ,  int *);
GAStatsP newGAStats();

void fillFirstGeneration(struct Permutation *, int *, int, PresetsP);

void calculateGenerationToursCost(struct Permutation *, PresetsP , MatrixP );

void findElites( struct Permutation *, PresetsP );

void Merge(struct Permutation *,struct Permutation *,int ,struct Permutation *,int );

void MergeSort(struct Permutation *, int );
#endif	/* GA_H */

