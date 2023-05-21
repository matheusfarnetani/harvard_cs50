#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_symbol(int size);
void print_space(int size);

int main(void)
{
    int n = get_size();

    for (int i = 1; i <= n; i++)
    {
        print_space(n - i);
        print_symbol(i);
        printf(" ");
        print_symbol(i);
        print_space(n - i);
        printf("\n");
    }
}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);
    return n;
}

void print_symbol(int size)
{
        for (int i = 0; i < size; i++)
        {
            printf("#");
        }  
}

void print_space(int size)
{
        for (int i = 0; i < size; i++)
        {
            printf(" ");
        }  
}