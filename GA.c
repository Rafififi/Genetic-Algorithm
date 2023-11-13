// Include everything necessary here 
#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int generation;
    // <YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code>
    if (argc != 6)
    {
        printf("Incorrect number of inputs. Expected 6 inputs .\n");
        return 1; // Exit the program with an error status
    }
    // <YOUR CODE: Assign all inputs given by the user argv[i]>
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);
    if (POPULATION_SIZE <= 0 || MAX_GENERATIONS <= 0 || crossover_rate <= 0 || mutate_rate <= 0 || stop_criteria < 0)
    {
        printf("One or more inputs is invalid\n");
        exit(0);
    }
    printf("%d, %d, %f, %f, %.16lf\n", POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria);

    // ###################################################################################
    // you dont need to change anything here
    // the number of variables
    int NUM_VARIABLES = 2;
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
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
    unsigned short int index = 0;
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
        for(int i = 0; i < POPULATION_SIZE; i++)
        {
            if(fitness[i] < bestFitness[0])
            {
                bestFitness[0] = fitness[i];
                index = i;
            }
        }
        if (generation > 0)
        {
            if(bestFitness[1] - bestFitness[0] < stop_criteria && bestFitness[1] - bestFitness[0] >= 0)
            {
                printf("Stopping criteria met\n");
                break;
            }
            if (generation == MAX_GENERATIONS)
            {
                printf("Stopping criteria not met\n");
                break;
            }
        }
        bestFitness[1] = bestFitness[0];
        // <YOUR CODE: Here call the crossover function>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);
        // <YOUR CODE: Here call the mutation function>

        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
        // Now you have the a new population, and it goes to the beginning of loop to re-compute all again
   
    }
    
    // <YOUR CODE: Jump to this part of code if the stopping criteria is met before MAX_GENERATIONS is met>

    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n",  cpu_time_used);
    // ###################################################################################

    // <Here print out the best solution and objective function value for the best solution like the format>
    printf("Best solution: %.16lf, %.16lf, %d\n", population[index][0], population[index][1], index);
    printf("Objective function value for the best solution: %.16lf\n", Objective_function(NUM_VARIABLES, population[index]));
    printf("Generation, %d\n", generation);   
}
