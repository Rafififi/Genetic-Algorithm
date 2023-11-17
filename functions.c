// Include everything necessary here
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"

double generate_random(double min, double max)
{
    // implement a function to return a value between min and max
    double randomFloat = (double)rand() / (double)RAND_MAX;
    // RAND_MAX is the maximum value returned by rand() making randomFloat between 0 and 1
    double randomFloatBetween = min + randomFloat * (max - min); // this forces the value to be between the min and max
    return randomFloatBetween;
}

unsigned int generate_int()
{
    // implement the function to return a random integer value
    int randomInt = rand();
    return randomInt;
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES])
{
    // randomly initialize for all values in "population[i][j]""
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = generate_random(Lbound[j], Ubound[j]);
        }
    }
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness[i] = 1 / (Objective_function(NUM_VARIABLES, population[i]) + 1e-10); // calculate fitness
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/
    double randomFloat;
    double fitnessSum = 0.0;
    int crossPoint;
    double parent1[NUM_VARIABLES];
    double parent2[NUM_VARIABLES];
    double fitness_probs[POPULATION_SIZE];
    int parent1Index = 0;
    int parent2Index = 0;
    double cumulativeSum = 0.0;

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitnessSum += fitness[i];
    }
    // get the fitness probability for each individual
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness_probs[i] = fitness[i] / fitnessSum;
    }

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < POPULATION_SIZE; j++)
        {
            cumulativeSum += fitness_probs[j];
            randomFloat = generate_random(0.0, 1.0);
            if (randomFloat < cumulativeSum) // if the float is generated is less than the sum the coordinates asscosiated with it are set as the parent
            {
                parent1Index = j; // index of parent 1
                break;
            }
        }

        randomFloat = generate_random(0.0, 1.0);
        cumulativeSum = 0.0; // reset cumulative sum
        for (int j = 0; j < POPULATION_SIZE; j++)
        {
            cumulativeSum += fitness_probs[j];
            if (randomFloat < cumulativeSum) // if the float is generated is less than the sum the coordinates asscosiated with it are set as the parent
            {
                parent2Index = j; // index of parent 2
                break;
            }
        }

        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            parent1[j] = population[parent1Index][j];
            parent2[j] = population[parent2Index][j];
            // Set the parents equal to the genes at the index of the parent
        }

        randomFloat = generate_random(0.0, 1.0);
        if (randomFloat < crossover_rate)
        {
            crossPoint = rand() % NUM_VARIABLES;
            for (int j = 0; j < crossPoint; j++)
            {
                new_population[i][j] = parent1[j];
                new_population[i + 1][j] = parent2[j];
                // Set the part of the new population before the cross point equal to the parents
            }
            for (int j = crossPoint; j < NUM_VARIABLES; j++)
            {
                new_population[i][j] = parent2[j];
                new_population[i + 1][j] = parent1[j];
                // Set the part of the new population after the cross point equal to the parents
            }
        }
        else
        {
            for (int j = 0; j < NUM_VARIABLES; j++)
            {
                new_population[i][j] = parent1[j];
                new_population[i + 1][j] = parent2[j]; // if the crossover condition was not met set the parents equal to the new_population
            }
        }
    }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/
    double randomFloat;
    int toBeMutated = (int)(POPULATION_SIZE * NUM_VARIABLES * mutate_rate); // number of variables to be mutated
    int amountMutated = 0;

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            randomFloat = generate_random(0.0, 1.0);
            // randomFloat is used to determine if a specific gene in the population will be mutated
            if (randomFloat < mutate_rate && amountMutated < toBeMutated) // mutate a specific gene in the population randomly
            {
                new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
                amountMutated++;
            }
        }
        if (amountMutated >= toBeMutated) // Check if the number of variables to be mutated has been reached
        {
            break;
        }
    }
    // make New_population the population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = new_population[i][j];
        }
    }
}
