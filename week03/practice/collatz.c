#include <cs50.h>
#include <stdio.h>

int collatz(int n, int steps);

int main(void)
{
    int number = get_int("Number: ");
    printf("%i steps.\n", collatz(number, 0));
    return 0;
}

int collatz(int n, int steps)
{
    if (n == 1)
        return steps;
    else if (n % 2 == 0)
        collatz(n / 2, steps + 1);
    else if (n % 2 != 0)
        collatz(3 * n + 1, steps + 1);
}