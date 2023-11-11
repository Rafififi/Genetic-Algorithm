// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



double generate_random(double min, double max)
{
    // implement a function to return a value between min and max
    double randomFloat = (double)rand() / (double)RAND_MAX;
    // RAND_MAX is the maximum value returned by rand() making randomFloat between 0 and 1
    double randomFloatBetween = min + randomFloat * (max - min);
    return randomFloatBetween;
}

unsigned int generate_int()
{
    // implement the function to return a random integer value
    int randomInt = rand();
    return randomInt;
}
double Objective_function(int NUM_VARIABLES, double x[NUM_VARIABLES])
{
    // While the objective function could be anything here it is to minimize Ackley function
    double sum1 = 0.0, sum2 = 0.0;
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        sum1 += x[i] * x[i];
        sum2 += cos(2.0 * M_PI * x[i]);
    }
    return -20.0 * exp(-0.2 * sqrt(sum1 / NUM_VARIABLES)) - exp(sum2 / NUM_VARIABLES) + 20.0 + M_E;
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
    double fitnessSum;
    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness[i] = 1/(Objective_function(NUM_VARIABLES, population[i])+1e-6);
        fitnessSum += fitness[i];
    }
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness[i] = fitness[i]/fitnessSum;
    }

}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/
    double randomFloat;
    int crossPoint;
    for(int i = 0; i < POPULATION_SIZE; i++)
    {

        randomFloat = (double)rand() / (double)RAND_MAX;
        if (randomFloat > crossover_rate)
        {
            double parent1[] = {population[i][1], population[i][2]};
            double parent2[] = {population[i + 1][1], population[i+1][2]};

            crossPoint = generate_int(1, NUM_VARIABLES);
            for (int j = 0; j < NUM_VARIABLES; ++j)
            {
                if (j < crossPoint)
                {
                    new_population[i][j] = parent1[j];
                    new_population[i + 1][j] = parent2[j];
                }
                else
                {
                    new_population[i][j] = parent2[j];
                    new_population[i + 1][j] = parent1[j];
                }
            }
        }   

    }
    compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, new_population, fitness);
//Make population equal to new_population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for(int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = new_population[i][j];
        }
    }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/
    double randomFloat;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for(int j = 0; j < NUM_VARIABLES; j++)
        {
            randomFloat = (double)rand() / (double)RAND_MAX;
            if (randomFloat > mutate_rate)
            {
                new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
            }
            population[i][j] = new_population[i][j];

        }
    }
}

