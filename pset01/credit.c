#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool checkSum(long long number);
string defineCard(long long number);

int main(void)
{
    // Ask user for credit card number
    long long number = get_long_long("Number: ");

    string card;
    if (checkSum(number))
    {
        card = defineCard(number);
    }
    else
    {
        card = "INVALID";
    }

    printf("%s\n", card);
}

bool checkSum(long long number)
{
    int numDigits = 0;
    long long temp = number;

    // Count the number of digits
    while (temp != 0)
    {
        temp /= 10;
        numDigits++;
    }

    int digitArray[numDigits];

    // Store each digit in the array
    temp = number;
    for (int i = numDigits - 1; i >= 0; i--)
    {
        digitArray[i] = temp % 10;
        temp /= 10;
    }

    int cardsum = 0;

    // Iterate over the array and perform Luhn’s algorithm
    for (int i = numDigits - 2; i >= 0; i -= 2)
    {
        int a = digitArray[i] * 2;

        // Sum the digits of the result
        while (a != 0)
        {
            cardsum += a % 10;
            a /= 10;
        }
    }

    // Sum the remaining digits
    for (int i = numDigits - 1; i >= 0; i -= 2)
    {
        cardsum += digitArray[i];
    }

    return (cardsum % 10) == 0;
}

string defineCard(long long number)
{
    int numDigits = 0;
    long long temp = number;

    // Count the number of digits
    while (temp != 0)
    {
        temp /= 10;
        numDigits++;
    }

    int firstDigit = number / pow(10, numDigits - 1);
    int firstTwoDigits = number / pow(10, numDigits - 2);

    if (numDigits == 15)
    {
        if (firstTwoDigits == 34 || firstTwoDigits == 37)
        {
            return "AMEX";
        }
    }
    else if (numDigits == 16)
    {
        if (firstTwoDigits >= 51 && firstTwoDigits <= 55)
        {
            return "MASTERCARD";
        }
        else if (firstDigit == 4)
        {
            return "VISA";
        }
    }
    else if (numDigits == 13)
    {
        if (firstDigit == 4)
        {
            return "VISA";
        }
    }

    return "INVALID";
}