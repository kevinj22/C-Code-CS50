#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("Amount of money?\n");
    float amount = GetFloat();
    /* printf("Amount: %f\n", amount); */
    int rounded = round(amount*100);
    while ( amount < 0)
    {
        printf("A postive value please....\n");
        amount = GetFloat();
    }
    float quarters = floor(rounded / 25);
    /* printf("%f\n", quarters); */
    float dimes = floor((rounded - 25 * quarters)/10);
    /* printf("%f\n",dimes); */
    float nickels = floor((rounded - (25 * quarters) - (10 * dimes))/5);
    /* printf("%f\n",nickels); */
    float pennies = (rounded - (25 * quarters) - (10 * dimes) - (5 * nickels));
    /* printf("%f\n",pennies); */
    int coins = (quarters + dimes + nickels + pennies);
    printf("%i\n", coins);
}