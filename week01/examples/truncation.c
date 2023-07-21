#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long x = get_long("x: ");
    long long y = get_long("y: ");

    float z = (float) x / (float) y;
    printf("%f\n", z);
}