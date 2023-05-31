#include <cs50.h>
#include <stdio.h>

bool valid_triangle(int a, int b, int c);

int main(void)
{
    int a, b, c;

    a = get_int("Give me the first side of the triangle: ");
    b = get_int("Give me the second side of the triangle: ");
    c = get_int("Give me the third side of the triangle: ");

    bool is_triangle = valid_triangle(a, b, c);
    if (is_triangle == true)
    {
        printf("Your triangle is valid!");
    }
    else
    {
        printf("That's not a triangle!");
    }

}

bool valid_triangle(int a, int b, int c)
{
    // Check if all sides are positives int
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }

    // Check if the sum of two sides is greater than the third side
    if ((a + b <= c) || (a + c <= b) || (c + b <= a))
    {
        return false;
    }

    return true;
}