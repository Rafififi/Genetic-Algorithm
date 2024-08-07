#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define true  1
#define false 0
#define bool  int

void check_arguments(const int POPULATION_SIZE, const int MAX_GENERATIONS, const double crossover_rate, const double mutate_rate, const double stop_criteria, const int NUM_VARIABLES){
  if (POPULATION_SIZE <= 0 || MAX_GENERATIONS <= 0 || crossover_rate <= 0 || crossover_rate > 1 || mutate_rate > 1 || mutate_rate <= 0 || stop_criteria < 0 || NUM_VARIABLES <= 0){
    printf("One or more inputs is invalid\n");
    printf("The order is ./Algo POPULATION_SIZE MAX_GENERATIONS crossover_rate mutate_rate stop_criteria NUM_VARIABLES\n");
    exit(0);
  }
}

inline void generate_population(const int POPULATION_SIZE, const int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double* Lbound, double* Ubound){
  // randomly initialize for all values in "population[i][j]""
  for (int i = 0; i < POPULATION_SIZE; i++){
    for (int j = 0; j < NUM_VARIABLES; j++){
      population[i][j] = generate_random(Lbound[j], Ubound[j]);
    }
  }
}

inline void compute_objective_function(const int POPULATION_SIZE, const int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double* fitness){
  /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
     by calling "Objective_function" */
  for (int i = 0; i < POPULATION_SIZE; i++)
  {
    fitness[i] = 1/(Objective_function(NUM_VARIABLES, population[i])); // If the function should be going to zero 1/OF is used
  }
}

int main(int argc, char** argv){
  if (argc != 7){
    printf("Incorrect number of inputs. Expected 7 inputs .\n");
    puts("The order is ./Algo POPULATION_SIZE MAX_GENERATIONS crossover_rate mutate_rate stop_criteria NUM_VARIABLES");
    return 1; // Exit the program with an error status
  }

  const int POPULATION_SIZE = atoi(argv[1]);
  const int MAX_GENERATIONS = atoi(argv[2]);
  const double crossover_rate = atof(argv[3]);
  const double mutate_rate = atof(argv[4]);
  const double stop_criteria = atof(argv[5]);
  const int NUM_VARIABLES = atoi(argv[6]);

  check_arguments(POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria, NUM_VARIABLES);
  printf("Genetic Algorithm is initiated\n");

  double Lbound[NUM_VARIABLES];
  double Ubound[NUM_VARIABLES];
  for (int i = 0; i < NUM_VARIABLES; i++){
    Lbound[i] = -5;
    Ubound[i] = 5;
  }

  double population[POPULATION_SIZE][NUM_VARIABLES];
  double fitness[POPULATION_SIZE];
  double new_population[POPULATION_SIZE][NUM_VARIABLES];
  double bestFitness[] = {0.0, 0.0};
  double bestSolution = 0.0;
  unsigned int index = 0;
  short int stopConditionMet = 0;
  double bestPosition[NUM_VARIABLES];

  clock_t start_time = clock();
  srand(1);

  generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);

  int generation = 0;
  for (; generation < MAX_GENERATIONS; generation++){
    compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);


    bestFitness[0] = fitness[0];
    // Finds the best fitness value from this generation and its index
    for (int i = 0; i < POPULATION_SIZE; i++){
      if (fitness[i] > bestFitness[0]){ // If this is a function that should be going to zero then use > 
        bestFitness[0] = fitness[i];
        index = i;
      }
    }
    if (bestFitness[0] > bestSolution){ //  If this is a function that should be going to zero then use >
      bestSolution = bestFitness[0];
      for (int i = 0; i < NUM_VARIABLES; i++){
        bestPosition[i] = population[index][i];
      }
    }

    if (generation > 0){
      if (fabs(bestFitness[1] - bestFitness[0]) < stop_criteria){ // if it meets the stop criteria
        if (stopConditionMet >= MAX_GENERATIONS * 0.1){ // If the stop condition is met for 10% of the max generations
          printf("Stopping criteria met\n");
          break;
        }
        stopConditionMet++;
      }
      else if (generation == MAX_GENERATIONS){ // if it reaches the max generations without meeting the stop criteria
        printf("Stopping criteria not met\n");
        break;
      }
      else{// this resets the stop condition met counter if the stop condition is not met
        stopConditionMet = 0;
      }
    }
    // moves bestFitnees[0] to bestFitness[1] so that it can be used to compare later
    bestFitness[1] = bestFitness[0];

    crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);


    mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
    // Now you have the a new population, and it goes to the beginning of loop to re-compute all again
  }

  printf("-------------------------------------------\n");
  printf("number of variables %d\n", NUM_VARIABLES);
  printf("Lower Bounds: %.16lf, %.16lf\n", Lbound[0], Lbound[1]);
  printf("Upper Bounds: %.16lf, %.16lf\n", Ubound[0], Ubound[1]);
  printf("Population size: %d\n", POPULATION_SIZE);
  printf("Max generations: %d\n", MAX_GENERATIONS);
  printf("Crossover rate: %f\n", crossover_rate);
  printf("Mutation rate: %f\n", mutate_rate);
  printf("Stopping criteria: %.16lf\n", stop_criteria);
  printf("Generation: %d\n", generation);
  printf("Results\n");
  printf("-------------------------------------------\n");

  clock_t end_time = clock();
  double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("CPU time: %f seconds\n", cpu_time_used);

  printf("Best solution found:");
  for (int i = 0; i < NUM_VARIABLES; i++)
  {
    printf(", %.16lf", bestPosition[i]);
  }
  printf("\n");

  printf("Best Function Value found: %.16lf\n", (Objective_function(NUM_VARIABLES, bestPosition)));
  printf("Best Fitness: %.16lf\n", 1 / (Objective_function(NUM_VARIABLES, bestPosition) + 1e-6));
}
