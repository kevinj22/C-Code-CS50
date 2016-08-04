#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: /home/cs50/pset2/caesar <key>\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    if (k < 0)
    {
        printf("Key must be a non-negative interger\n");
        return 1;
    }
    string code = GetString();
    for (int i = 0, n = strlen(code); i < n; i++)
    {
        if (isalpha(code[i]) && isupper(code[i]))
        {
            printf("%c", ((code[i]-65+k) % 26) + 65);
        }
        else if (isalpha(code[i]) && islower(code[i]))
        {
            printf("%c", ((code[i]-97+k) % 26) + 97);
        }
        else 
        {
            printf("%c", code[i]);
        }
    }
    printf("\n");
    return 0;
}