#include <stdio.h>

int main(void)
{
    int size = 101;
    int array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%i\n", array[i]);
    }
}