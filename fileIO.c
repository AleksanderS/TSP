#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>

void getCityWeights(double city_weight_list[380]){
    FILE *in = fopen("theCities.txt", "r");
    int i;
    for(i = 0; i < 380; i++){
        fscanf(in, "%lf", &(city_weight_list[i]));
    }
    
}

PresetsP getPresets(){
    FILE *in = fopen("thePresets.txt", "r");
    PresetsP presets = malloc(sizeof(Presets));
    
    fscanf(in, "%i", &(presets->tours));
    fscanf(in, "%i", &(presets->generations));
    fscanf(in, "%lf", &(presets->mutation_percent));
    fscanf(in, "%lf", &(presets->elites_percent));
    fscanf(in, "%i", &(presets->amount_of_cities));
    fclose(in);
    return presets;
}
