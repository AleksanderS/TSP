

#include <stdio.h>
#include <stdlib.h>
#include "BruteForce.h"
#include <string.h>
#include "matrix.h"
#include "fileIO.h"

int m, k, p, q;
int fac(int n){
    if(n <= 1)
        return 1;
    return n * fac(n-1);
}
/*
 * Passes in a tour, the graph, and the number of cities in a tour.
 * 
 */
double getTourCost(int *tour, MatrixP matrix, int tour_size){
    double cost = 0;
    int i;
    for(i = 0; i < tour_size; i++){
        int j,k;
        j = tour[i];
        k = tour[i + 1];
        double current = matrix->array[j][k];
        cost += current;
    }
    return cost;
}

void PermuteIter(PresetsP presets, int *s){
    int i;
    int n = presets->amount_of_cities;
    double nfact = (double) fac( n );
    perm1(n, nfact,s);
}
/*
 * Guarantees we will iterate through every permutation AND that the last permutation will be the original permutation in reverse, giving us a stopping condition.
 *
 */
void perm1(int n, double nfact, int *s){
  //  int m, k, p, q, i;
    
    
        m = n - 2;
        while(s[m] > s[m+1])
            m = m - 1;
        k = n -1;
        while(s[m] > s[k])
            k = k -1;
        int tmp = s[m]; //Swap
            s[m] = s[k]; 
                s[k] = tmp; //end swap
        p = m + 1;
        q = n-1;
        while(p < q)
        {
            tmp = s[p]; //Swap
                s[p] = s[q]; 
                    s[q] = tmp; //End Swap
            p++;
            q--;
        }
    
}


