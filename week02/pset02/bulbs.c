#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");

    int ascii;

    for (int i = 0, len = strlen(message); i < len; i++)
    {
        ascii = message[i];
        int bits[BITS_IN_BYTE];
        int counter = 0;

        do
        {
            int n = ascii % 2;
            if (n == 0)
            {
                bits[counter] = 0;
            }
            else
            {
                bits[counter] = 1;
            }
            counter++;
            ascii /= 2;
        }
        while (counter < BITS_IN_BYTE);

        for (int i = BITS_IN_BYTE - 1; i > -1; i--)
        {
            print_bulb(bits[i]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        // printf("\U000026AB");
        printf("0"); // Windows doesn't know the emoji :c
    }
    else if (bit == 1)
    {
        // Light emoji
        // printf("\U0001F7E1");
        printf("1"); // Windows doesn't know the emoji :c
    }
}
