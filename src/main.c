#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random integer
    int random_number = rand();

    // Print "Hello, World!" and the random number
    printf("Hello, World! Random number: %d\n", random_number);

    return 0;
}