#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand((unsigned)time(NULL));

    int thing1 = 0;
    int thing2 = 0;
    int thing3 = 0;
    int thing4 = 0;
    int thing5 = 0;
    int thing6 = 0;
    int thing7 = 0;
    int thing8 = 0;
    int thing9 = 0;
    int thing10 = 0;
    
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
    for (int i = 0; i < 100000000; i++)
    {
        double randomFloat = (double)rand() / (double)RAND_MAX;
        double randomFloatBetween = Lbound[0] + randomFloat * (Ubound[0] - Lbound[0]);
        //count how many floats are between each integer (-5 to -4 etc)    
    }
    
    
    return 0;
}
