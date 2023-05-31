// Alphabetical Exercise

// Check if a lowercase string's characters are in
// alphabetical order.
// If yes, print "Yes"
// If no, print "No"

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string word = get_string("Word: ");
    int word_length = strlen(word);
    bool order = true;

    for (int i = 0; i < word_length; i++)
    {
        if (islower(word[i]))
        {
            if (word[i] < word[i - 1])
            {
                order = false;
            }
            
        }
    }

    if (order == true)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
}