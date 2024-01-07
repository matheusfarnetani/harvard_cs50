#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool VISITED[26] = {false};

char rotate(char c, string key);
bool valid_key(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (valid_key(argv[1]) == false)
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", rotate(plaintext[i], argv[1]));
    }

    printf("\n");
    return 0;
}

char rotate(char c, string key)
{
    char new_c;
    if (islower(c))
    {
        new_c = tolower(key[c - 'a']);
    }
    else if (isupper(c))
    {
        new_c = toupper(key[c - 'A']);
    }
    else
    {
        return c;
    }

    return new_c;
}

bool valid_key(string text)
{
    // Check if the key it's 26 long alphabetical string
    int len = strlen(text);
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char c = tolower(text[i]);

        if (!isalpha(text[i]) || VISITED[c - 'a'])
        {
            printf("Usage: ./substitution key\n");
            return false;
        }

        VISITED[c - 'a'] = true;
    }

    if (len < 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    return true;
}