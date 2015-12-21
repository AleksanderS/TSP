/* 
 * File:   fileIO.h
 * Author: Alex
 *
 * Created on October 19, 2015, 12:05 PM
 */

#ifndef FILEIO_H
#define	FILEIO_H

typedef struct {
    int tours;
    int generations;
    double mutation_percent;
    double elites_percent;
    int amount_of_cities;
} *PresetsP, Presets;

void getCityWeights(double *);

PresetsP getPresets();

#endif	/* FILEIO_H */

