#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height of half pyramid?\n");
    int height = GetInt();
    while (height > 23 || height < 0) 
    {
        printf("Please pick a height between 0 and 23...\n");
        height = GetInt();
    }
    for (int i = 0; i < height; i++)
    {
        printf("%*s", height-1-i,"");
        printf("%.*s", i+2,"#########################");
        printf("\n");
    }
}