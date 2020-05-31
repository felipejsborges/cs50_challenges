#include <stdio.h>
#include <cs50.h>

// collatz conjecture
int collatz(int n);

int main(void)
{
    int n = get_int("n: ");
    int steps = collatz(n);
    printf("steps: %i\n", steps);
}

int collatz(int n)
{
    // if n is 1, stop
    if (n == 1)
        return 0;

    //otherwise, if n is even, repeat this process on n/2
    else if ((n % 2) == 0)
        return 1 + collatz(n / 2);

    //otherwise, if n is odd, repeat this process on 3n+1
    else
        return 1 + collatz(3 * n + 1);
}