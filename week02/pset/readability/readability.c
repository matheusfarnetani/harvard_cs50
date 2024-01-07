#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_sentences(string text);
int count_words(string text);
int count_letters(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float avg_letters = (float) letters / words * 100;
    float avg_sentences = (float) sentences / words * 100;
    int index = round((0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter += 1;
        }
    }

    return counter;
}

int count_words(string text)
{
    int counter = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isblank(text[i]))
        {
            counter += 1;
        }
    }

    return counter;
}

int count_letters(string text)
{
    int counter = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            counter += 1;
        }
    }

    return counter;
}