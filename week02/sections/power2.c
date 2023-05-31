// Create a program that prompts the user for a size, n.
// Dynamically create an array of that size, where each
// element is 2 time the previous one.

// Start the array at 1.
// Print the array, integer by integer

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int length;
    do
    {
        length = get_int("Array size: ");
    }
    while (length < 1);
    
    int array[length];

    for (int i = 0, j = 1; i < length; i++)
    {
        array[i] = j;
        j *= 2;
    }

    for (int i = 0; i < length; i++)
    {
        printf("%i\n", array[i]);
    }
}