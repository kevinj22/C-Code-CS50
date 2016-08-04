#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How long was your shower?\n");
    int len = GetInt();
    while (len < 0) {
        printf("Negative time in the shower whhaaaa??? Positive number please\n");
        len = GetInt();
    }
    int bots = ((len * 192) / 16);
    printf("Your %i minutes in the shower consumed %i bottles of water\n", len,bots);
}