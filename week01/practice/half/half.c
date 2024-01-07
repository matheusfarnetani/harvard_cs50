#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float bill = get_float("Bill before tax and tip: ");
    float tax = get_float("Sale Tax percent: ");
    int tip = get_int("Tip percent: ");

    float tax_value = bill * (tax / 100);
    float bill_value = tax_value + bill;
    float tip_value = bill_value * ((float) tip / 100);

    float half = (bill_value + tip_value) / 2;

    printf("You will owe $%.2f each!\n", half);
}