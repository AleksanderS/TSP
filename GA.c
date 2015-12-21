#include <stdlib.h>
#include <stdio.h>

#include "GA.h"
#include "fileIO.h"
#include "BruteForce.h"
#include "matrix.h"
#include <time.h>
void copyArray(int *, int *, int);
void getOriginalPermutation(int *, int );
void reverseArray(int *, int *, int);
int arrayEquals(int *, int *, int );




int z = 1;
int zz = 3;



/*
 * The genetic Algorithm. Uses global variables z and zz. z = 1, zz = 3. The number of cities - 1 is passed in as the ending index. GA will swap 
 * ending index and z, increment z, then swap n and zz, incrementing zz.
 * If z or zz ever reach ending index, they will be reset to their initial values.
 */
void geneticAlgorithmPerm1(int *array, int n){
    if(z == n){
        z = 1;
    }
    int tmp;
    tmp = array[z];
    array[z] = array[n];
    array[n] = tmp;
    z++;
    n--;
    
    if(zz == n) zz = 3;
    tmp = array[zz];
    array[zz] = array[n];
    array[n] = tmp;
    zz++;
    
}
/*
 * Creates Genetic Algorithm statistics struct.
 */
GAStatsP newGAStats(){
    GAStatsP tmp = malloc(sizeof(GAStats));
    tmp->cost = 0;
    tmp->elapsed = -1;
    tmp->end = -1;
    tmp->percent_optimal = 0;
    tmp->start = -1;
    return tmp;
}

void startGeneticAlgorithm(GAStatsP stats, PresetsP presets,MatrixP matrix,  int *original_permutation){
    struct Permutation generation[presets->tours];
    struct Permutation elites[(int)(presets->tours*presets->elites_percent)];
    stats->start = clock();
    fillFirstGeneration(generation, original_permutation, presets->amount_of_cities + 1, presets);
    calculateGenerationToursCost(generation, presets, matrix);
    findElites(generation, presets); // sort the array based upon tour_cost
 
    
    int i;
    for(i = 0; i < presets->generations - 1; i++){
        int v;
        for(v = (int)(presets->tours*presets->elites_percent) + 1; v < (int)(presets->tours*presets->mutation_percent); v++){
            geneticAlgorithmPerm1(generation[v].perm, presets->amount_of_cities - 1 );
            
        }
        for(v; v < presets->tours; v++){
            PermuteIter(presets, generation[v].perm);
        }
        calculateGenerationToursCost(generation, presets, matrix);
        findElites(generation, presets);
    }
    stats->end = clock();
    stats->elapsed = stats->end - stats->start;
    stats->cost = generation[0].tour_cost;
  
}

/*
 * Creates the initial generation. Fills it with Iterative permutations, then performs the GA on those permutations.
 *
 */
void fillFirstGeneration(struct Permutation *generation, int *original_permutation, int size, PresetsP presets){
    
    int tmp_permutation[size];
    copyArray(tmp_permutation, original_permutation, size - 1);
    int i;
    
    for(i = 0; i < presets->tours; i++){
        generation[i].perm = malloc(sizeof(int)*(presets->amount_of_cities + 1));
        copyArray((generation[i].perm), tmp_permutation, size - 1);
        PermuteIter(presets, tmp_permutation);
        PermuteIter(presets, (generation[i].perm));   
    }
    for(i = 0; i < presets->tours; i++)
        geneticAlgorithmPerm1(generation[i].perm, presets->amount_of_cities - 1 );
         
}
/*
 *
 * Loops through the generation array, determining cost for each generation.
 *
 */
void calculateGenerationToursCost(struct Permutation *generation, PresetsP presets, MatrixP matrix){
    int i;
    for(i = 0; i < presets->tours; i++){
       generation[i].tour_cost = getTourCost(generation[i].perm, matrix, presets->amount_of_cities);
    }
    
}

/*
 * Simply sorts the generation and places the elites at the top of the generation array.
 */
void findElites(struct Permutation *generation, PresetsP presets){
    MergeSort(generation, presets->tours); 
}


/*
 * Used for finding Elites in a generation
 * 
 */
void MergeSort(struct Permutation *A, int n){
    int mid,i;
    struct Permutation *L, *R;
    if(n < 2) return; //ends recursion. base condition

    mid = n/2;  


    L = malloc(mid*sizeof(struct Permutation)); 
    R = malloc((n- mid)*sizeof(struct Permutation)); 

    for(i = 0;i<mid;i++) L[i] = A[i]; 
    for(i = mid;i<n;i++) R[i-mid] = A[i]; 

    MergeSort(L,mid);  
    MergeSort(R,n-mid); 
    Merge(A,L,mid,R,n-mid);  
    free(L);
    free(R);
}

void Merge(struct Permutation *A,struct Permutation *L,int leftCount,struct Permutation *R,int rightCount) {
	int o, p, q;
	o = 0; p = 0; q =0;

	while(o<leftCount && p< rightCount) {
		if(L[o].tour_cost  < R[p].tour_cost) A[q++] = L[o++];
		else A[q++] = R[p++];
	}
	while(o < leftCount) A[q++] = L[o++];
	while(p < rightCount) A[q++] = R[p++];
}


