/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
    
#include <cs50.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Starts from 1 as argv[0] is the ./find command
    int top=n;
    int bot=1;
    while (top >= bot)
    {
        int mid = ceil((top+bot)/2);
        if (value == values[mid])
        {
            return true;
        }
        else if (value > values[mid])
        {
            bot = mid + 1;
        }
        else
        {
            top = mid - 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; j++)
        {
            if (values[j+1]<values[j])
            {
                int t = values[j];
                values[j]= values[j+1];
                values[j+1]=t;
            }
        }
    return;
}