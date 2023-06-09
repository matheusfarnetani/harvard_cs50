// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    } 
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    // Base case
    if (n == 1)
    {
        return array[0];
    }
    
    // Recursive case: find the maximum value between the first element and the maximum of the rest of the array
    int max_value = max(array + 1, n - 1);
    
    // Compare the maximum of the rest with the first element and return the larger one
    if (array[0] > max_value)
    {
        return array[0];
    }
    else
    {
        return max_value;
    }
    
    // Normal version
    // int max_value = array[0];

    // for (int i = 1; i < n; i++)
    // {
    //     if (array[i] > max_value)
    //     {
    //         max_value = array[i];
    //     }
    // }

    // return max_value;
}
