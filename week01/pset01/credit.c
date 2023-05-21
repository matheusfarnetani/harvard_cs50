#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long get_number(void);
int sum_card(long long num);
int sum_digit(int a);

int main(void) {
    long long number = 0;
    int mainsum = 0;

    number = get_number();

    mainsum = sum_card(number);
    printf("%d\n", mainsum);
}

long long get_number(void) {
    long long num = 0;
    int result = 0;
    while (true)
    {
        printf("Number: ");
        result = scanf("%lld", &num);
        if (result == 1) {
            return num;
        }
        else {
            printf("This program handles only numerical inputs.\n");
            while (getchar() != '\n') {
                continue;
            }
        }
    }
}

int sum_card(long long num) {
    int numDigits = 0; // Number of digits in the number
    long long temp = num;

    // Count the number of digits
    while (temp != 0) {
        temp /= 10;
        numDigits++;
    }

    // Allocate memory for the array
    int* digitArray = (int*)malloc(numDigits * sizeof(int));

    // Store each digit in the array
    temp = num; // Use temp to keep the original value of num
    for (int i = numDigits - 1; i >= 0; i--) {
        digitArray[i] = temp % 10;
        temp /= 10;
    }

    int cardsum = 0;

    // Iterate over the array and perform conditional operations
    for (int i = 0; i < numDigits; i++) {
        int a = 0;
        if (i % 2 == 0) {
            int b = digitArray[i] * 2;
            if (b >= 10) {
                a = sum_digit(b);
            } else {
                a = b;
            }
        } else {
            a = digitArray[i];
        }
        cardsum += a;
    }

    // Free the dynamically allocated memory
    free(digitArray);

    return cardsum;
}

int sum_digit(int a) {
   int sum = 0;
   int r;

   for (; a != 0; a = a / 10) {
      r = a % 10;
      sum += r;
   }

   return sum;
}