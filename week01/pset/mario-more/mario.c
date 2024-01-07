#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_symbol(int size);
void print_space(int size);

int main(void)
{
    // Get size of pyramid
    int n = get_size();

    // Call functions to create pyramid
    for (int i = 1; i <= n; i++)
    {
        print_space(n - i);
        print_symbol(i);

        // Create middle space
        printf("  ");

        print_symbol(i);

        // Hit enter
        printf("\n");
    }
}

int get_size(void)
{
    // Get value > 1
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_symbol(int size)
{
    // Print sequence of '#' in the same line
    for (int i = 0; i < size; i++)
    {
        printf("#");
    }
}

void print_space(int size)
{
    // Print sequence of ' ' in the same line
    for (int i = 0; i < size; i++)
    {
        printf(" ");
    }
}