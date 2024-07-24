#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// This is the Objective function which the implementation is in OF.c
double Objective_function(const int NUM_VARIABLES, double* x);

// This function generate a random number with precision double between "min" and "max"
double generate_random(double min, double max);

// Initializing the population randomly between the the lower and upper bound
void generate_population(const int POPULATION_SIZE, const int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double* Lbound, double* Ubound);

// Calling Objective_function function to compute fitness[i] values of each individual in "population"
void compute_objective_function(const int POPULATION_SIZE, const int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double* fitness);

// crossover function
void crossover(const int POPULATION_SIZE, const int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate);

// mutation function
void mutate(const int POPULATION_SIZE, const int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate);

#endif
