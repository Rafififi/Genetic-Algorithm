// Include everything necessary here
#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int generation;
    // <YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code>
    if (argc != 7)
    {
        printf("Incorrect number of inputs. Expected 7 inputs .\n");
        puts("The order is ./Algo POPULATION_SIZE MAX_GENERATIONS crossover_rate mutate_rate stop_criteria NUM_VARIABLES");
        return 1; // Exit the program with an error status
    }
    // <YOUR CODE: Assign all inputs given by the user argv[i]>
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);
    int NUM_VARIABLES = atoi(argv[6]);
    // Check the inputs to make sure they are valid
    if (POPULATION_SIZE <= 0 || MAX_GENERATIONS <= 0 || crossover_rate <= 0 || crossover_rate > 1 || mutate_rate > 1 || mutate_rate <= 0 || stop_criteria < 0 || NUM_VARIABLES <= 0)
    {
        printf("One or more inputs is invalid\n");
        printf("The order is ./Algo POPULATION_SIZE MAX_GENERATIONS crossover_rate mutate_rate stop_criteria NUM_VARIABLES\n");
        exit(0);
    }
    printf("Genetic Algorithm is initiated\n");
    // ###################################################################################
    // you dont need to change anything here
    // the number of variables
    // To change the amount of variables only change this line
    // the lower bounds of variables
    double Lbound[NUM_VARIABLES];
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        Lbound[i] = -5;
    }
    // the upper bounds of variable
    double Ubound[NUM_VARIABLES];
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        Ubound[i] = 5;
    }
    // ###################################################################################

    // <YOUR CODE: Here make all the initial print outs>

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();
    srand(time(NULL));

    // <YOUR CODE: Declare all the arrays you need here>

    double population[POPULATION_SIZE][NUM_VARIABLES];
    double fitness[POPULATION_SIZE];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];
    double bestFitness[] = {0.0, 0.0};
    double bestSolution = 0.0;
    unsigned int index = 0;
    short int stopConditionMet = 0;
    double bestPosition[NUM_VARIABLES];
    // <YOUR CODE: Call generate_population function to initialize the "population"> like:
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);
    // iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met

    for (generation = 0; generation < MAX_GENERATIONS; generation++)
    {
        // <YOUR CODE: Compute the fitness values using objective function for
        // each row in "population" (each set of variables)> like:
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);
        // <YOUR CODE: Here implement the logic of finding best solution with minimum fitness value
        // and the stopping criteria>

        bestFitness[0] = fitness[0];
        // Finds the best fitness value from this generation and its index
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            if (fitness[i] > bestFitness[0]) // If this is a function that should be going to zero then use >
            {
                bestFitness[0] = fitness[i];
                index = i;
            }
        }
        if (bestFitness[0] > bestSolution) //  If this is a function that should be going to zero then use >
        {
            bestSolution = bestFitness[0];
            for (int i = 0; i < NUM_VARIABLES; i++)
            {
                bestPosition[i] = population[index][i];
            }
        }

        if (generation > 0)
        {
            // fabs is built into math takes absolute value
            if (fabs(bestFitness[1] - bestFitness[0]) < stop_criteria) // if it meets the stop criteria
            {
                if (stopConditionMet >= MAX_GENERATIONS * 0.1) // If the stop condition is met for 10% of the max generations
                {
                    printf("Stopping criteria met\n");
                    break;
                }
                stopConditionMet++;
            }
            else if (generation == MAX_GENERATIONS) // if it reaches the max generations without meeting the stop criteria
            {
                printf("Stopping criteria not met\n");
                break;
            }
            else // this resets the stop condition met counter if the stop condition is not met
            {
                stopConditionMet = 0;
            }
        }
        // moves bestFitnees[0] to bestFitness[1] so that it can be used to compare later
        bestFitness[1] = bestFitness[0];
        // <YOUR CODE: Here call the crossover function>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);
        // <YOUR CODE: Here call the mutation function>

        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
        // Now you have the a new population, and it goes to the beginning of loop to re-compute all again
    }

    // <YOUR CODE: Jump to this part of code if the stopping criteria is met before MAX_GENERATIONS is met>

    printf("-------------------------------------------\n");
    printf("number of variables %d\n", NUM_VARIABLES);
    printf("Lower Bounds: %.16lf, %.16lf\n", Lbound[0], Lbound[1]);
    printf("Upper Bounds: %.16lf, %.16lf\n", Ubound[0], Ubound[1]);
    printf("\nPopulation size: %d\n", POPULATION_SIZE);
    printf("Max generations: %d\n", MAX_GENERATIONS);
    printf("Crossover rate: %f\n", crossover_rate);
    printf("Mutation rate: %f\n", mutate_rate);
    printf("Stopping criteria: %.16lf\n", stop_criteria);
    printf("Generation: %d\n", generation);
    printf("Results\n");
    printf("-------------------------------------------\n");

    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // <Here print out the best solution and objective function value for the best solution like the format>
    printf("Best solution found:");
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        printf(", %.16lf", bestPosition[i]);
    }
    printf("\n");
    
    printf("Best Function Value found: %.16lf\n", (Objective_function(NUM_VARIABLES, bestPosition)));
    printf("Best Fitness: %.16lf\n", 1 / (Objective_function(NUM_VARIABLES, bestPosition) + 1e-6));
}
