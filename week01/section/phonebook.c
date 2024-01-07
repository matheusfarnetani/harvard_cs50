#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? ");
    int age;
    do
    {
        age = get_int("Age: ");
    }
    while (age <= 9 || age >= 120);
    string number = get_string("What's your phone number? ");

    printf("Age is %i. Name is %s. Phone number is %s", age, name, number);

    // int calls = 4
    // if (calls < 1)
    // {
    //     printf("Call more often!\n")
    // }
    // else
    // {
    //     printf("Thanks for calling!\n")
    // }

    // int i = 0;
    // while (i < 10)
    // {
    //     printf("%i\n", i);
    //     i += 1;
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%i\n", i);
    // }

    // for (int i = 0; i < 10; i++)
    // {
    //     // code with i;
    //     for (int j = i; j < 10; j++)
    //     {
    //         // code with i and j;
    //     }
    //     // code without j;
    // }

    // int n;
    // do
    // {
    //     n = get_int("Number: ");
    // }
    // while (n <= 0)

    // cs50.harvard.edu/college/2022/fall/labs/1/
}