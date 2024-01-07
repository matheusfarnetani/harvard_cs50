#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define SYMBOL_COUNT 32

int issymbol(char c);
bool valid(string word);

int main(void)
{
    string password = get_string("Enter your password: ");
    bool checked = valid(password);
    if (checked == true)
    {
        printf("Your password is valid!");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol!");
    }
}

int issymbol(char c)
{
    char symbols[SYMBOL_COUNT] = {
        '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'
    };

    for (int i = 0; i < SYMBOL_COUNT; i++) 
    {
        if (c == symbols[i])
        {
            return true;
        }
    }
    return false;
}

bool valid(string word)
{
    bool uppercase = false;
    bool lowercase = false;
    bool number = false;
    bool symbol = false;

    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        if (islower(word[i]))
        {
            lowercase = true;
        }
        if (isupper(word[i]))
        {
            uppercase = true;
        }
        if (isdigit(word[i]))
        {
            number = true;
        }
        if (issymbol(word[i]))
        {
            symbol = true;
        }
    }

    if (lowercase == true && uppercase == true && number == true && symbol == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}