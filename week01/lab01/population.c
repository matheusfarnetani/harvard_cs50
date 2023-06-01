#include <cs50.h>
#include <stdio.h>

int start_population(void);
int end_population(int start_number);
int years(int start_number, int end_number);

int main(void)
{
    int start_llamas = start_population();
    int end_llamas = end_population(start_llamas);


    if (start_llamas == end_llamas)
    {
        printf("Years: 0\n");
    }
    else
    {
        int year = years(start_llamas, end_llamas);
        printf("Years: %i\n", year);
    }
}

int start_population(void)
{
    // Prompting the user for a starting # of llamas
    int start_number;
    do
    {
        start_number = get_int("Start size: ");
    }
    while (start_number < 9); // Why 9? Because before 9 there is numbers that doesn't work, like 8 for example.

    return start_number;
}

int end_population(int start_number)
{
    // Prompting them for an ending # of llamas
    int end_number;
    do
    {
        end_number = get_int("End size: ");
    }
    while (end_number < start_number);

    return end_number;
}

int years(int start_number, int end_number)
{
    // How many years will it take to get to the goal?
    int year = 0;
    int number = start_number;

    // Every year, 1/3 of our current llamas are born; 1/4 pass away
    do
    {
        int born_llamas = number / 3;
        int pass_llamas = number / 4;
        number = number + born_llamas - pass_llamas;
        year += 1;
    }
    while (number < end_number);

    return year;
}