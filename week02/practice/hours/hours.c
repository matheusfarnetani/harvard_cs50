#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hour(float array[], int array_size, char output);

int main(void)
{
    int weeks;
    do
    {
        weeks = get_int("Number of weeks taking CS50: ");
    }
    while (weeks < 1);

    float hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_float("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = get_char("Enter T for total hours, A for average hours per week: ");
        output = toupper(output);
    }
    while (output != 'T' && output != 'A');

    calc_hour(hours, weeks, output);
}

float calc_hour(float array[], int array_size, char output)
{
    float sum;
    for (int i = 0; i < array_size; i++)
    {
        sum += array[i];
    }

    if (output == 'T')
    {
        printf("%f\n", sum);
    }
    else
    {
        float average = sum / array_size;
        printf("%f\n", average);
    }
}