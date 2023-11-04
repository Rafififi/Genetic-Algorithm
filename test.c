#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand((unsigned)time(NULL));

    printf("%d", RAND_MAX);
    
    return 0;
}
