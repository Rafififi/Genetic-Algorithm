#include <stdlib.h>
#include <string.h>
#include "functions.h"

double generate_random(double min, double max) {
  double randomFloat = (double)rand() / (double)RAND_MAX;
  return (min + randomFloat * (max - min));
}

// Function to initialize a random population

static inline void crossPoint_helper(const int POPULATION_SIZE, const int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double parent1[NUM_VARIABLES], double parent2[NUM_VARIABLES], const double crossover_rate, int i){
    if (generate_random(0.0, 1.0) < crossover_rate){
      int crossPoint = rand() % NUM_VARIABLES;
      for (int j = 0; j < crossPoint; j++){
        new_population[i][j] = parent1[j];
        new_population[i + 1][j] = parent2[j];
        // Set the part of the new population before the cross point equal to the parents
      }
      for (int j = crossPoint; j < NUM_VARIABLES; j++){
        new_population[i][j] = parent2[j];
        new_population[i + 1][j] = parent1[j];
        // Set the part of the new population after the cross point equal to the parents
      }
      return;
    }
    for (int j = 0; j < NUM_VARIABLES; j++){
      new_population[i][j] = parent1[j];
      new_population[i + 1][j] = parent2[j]; // if the crossover condition was not met set the parents equal to the new_population
    }
}

inline void crossover(const int POPULATION_SIZE, const int NUM_VARIABLES, double* fitness, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES],  double crossover_rate){

  double randomFloat;
  double parent1[NUM_VARIABLES];
  double parent2[NUM_VARIABLES];
  int parent1Index = 0;
  int parent2Index = 0;
  double cumulativeSum = 0.0;

  double fitnessSum = 0.0;
  for (int i = 0; i < POPULATION_SIZE; i++){
    fitnessSum += fitness[i];
  }

  for (int i = 0; i < POPULATION_SIZE; i++){
    for (int j = 0; j < POPULATION_SIZE; j++){
      cumulativeSum += (fitness[j]/fitnessSum);
      if (generate_random(0.0, 1.0) < cumulativeSum){
        parent1Index = j; // index of parent 1
        break;
      }
    }

    randomFloat = generate_random(0.0, 1.0);
    cumulativeSum = 0.0; // reset cumulative sum
    for (int j = 0; j < POPULATION_SIZE; j++){
      cumulativeSum += (fitness[j]/fitnessSum);
      if (randomFloat < cumulativeSum){ 
        parent2Index = j; // index of parent 2
        break;
      }
    }

    for (int j = 0; j < NUM_VARIABLES; j++){
      parent1[j] = population[parent1Index][j];
      parent2[j] = population[parent2Index][j];
      // Set the parents equal to the genes at the index of the parent
    }
    crossPoint_helper(POPULATION_SIZE, NUM_VARIABLES, new_population, parent1, parent2, crossover_rate, i);
  }
}

inline void mutate(const int POPULATION_SIZE, const int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES]
    , double* Lbound,  double* Ubound,  double mutate_rate){

  int toBeMutated = (int)(POPULATION_SIZE * NUM_VARIABLES * mutate_rate); // number of variables to be mutated

  for (int i = 0; i < POPULATION_SIZE; i++){
    for (int j = 0; j < NUM_VARIABLES; j++){
      if (generate_random(0.0, 1.0) < mutate_rate && 0 < toBeMutated){ // mutate a specific gene in the population randomly
        new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
        toBeMutated--;
      }
    }
    if (toBeMutated <= 0){
      break;
    }
  }
  memcpy(population, new_population, POPULATION_SIZE * NUM_VARIABLES * sizeof(population[0][0]));
}
