#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int key);
bool only_digits(string text);

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (only_digits(argv[1]) == false)
    {
        return 1;
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }

    printf("\n");

    return 0;
}

char rotate(char c, int key)
{
    char new_c;
    if (!isalpha(c))
    {
        return c;
    }
    else if (islower(c))
    {
        new_c = (c - 'a' + key) % 26 + 'a';
        return new_c;
    }
    else if (isupper(c))
    {
        new_c = (c - 'A' + key) % 26 + 'A';
        return new_c;
    }
}

bool only_digits(string text)
{
    // Check if the key contains only numbers
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (!isdigit(text[i]))
        {
            printf("Usage: ./caesar key\n");
            return false;  
        }
    }

    return true;
}