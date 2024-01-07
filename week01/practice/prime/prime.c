#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int get_min(void);
int get_max(int min);
bool prime(int n);

int main(void)
{
    int min = get_min();
    int max = get_max(min);

    for (int i = min; i < max; i++)
    {
        if (i == 1 || i == 0)
        {
            continue;
        }

        if (prime(i) == true)
        {
            printf("%i\n", i);
        }
    }
}

int get_min(void)
{
    int n = 0;
    do
    {
        n = get_int("Minimum: ");
    } while (n <= 0);
    
    return n;
}

int get_max(int min)
{
    int n = 0;
    do
    {
        n = get_int("Maximum: ");
    } while (n < min);
    
    return n;
}

bool prime(int n)
{
    bool is_prime = true;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}