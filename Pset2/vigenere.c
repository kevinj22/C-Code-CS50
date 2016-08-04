#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char keyvals(char keyword);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error please give an input\n");
        return 1;
    }
    
   
    string key = argv[1];
    
    // Error Check for non numeric characters, skip spaces
    
    for (int i = 0, n=strlen(key); i < n; i++)
    {
        if (isalpha(key[i])==0 && key[i]!=' ')
        {
            printf("Need only letters stopped at %c, %i\n", key[i],i);
            return 1;
        }
    }
    
    // Carry on with code if no errors
    
    string code = GetString();
    int keylen = strlen(key);
    char keynums[keylen];
    for (int i = 0; i < keylen; i++)
    {
        keynums[i]=keyvals(key[i]);
    }
    
    // Make a variable k to keep track of keynums index
    // Need a standalone variable to skip iterating it over spaces
    
    int k = 0;
    for (int j = 0, n=strlen(code); j < n; j++)
    {
        if (isalpha(code[j]) && isupper(code[j]))
        {
            printf("%c", ((code[j] -65+keynums[k % keylen])%26 + 65));
            k++;
        }
        else if (isalpha(code[j]) && islower(code[j]))
        {
            printf("%c", ((code[j] -97+keynums[k % keylen])%26 + 97));
            k++;
        }
        else
        {
            printf("%c",code[j]);
        }
    }
    printf("\n");
    return 0;
}

char keyvals(char keyword)
{
    // Set keys to a null character
    char keys='\0';
    if (isalpha(keyword) && isupper(keyword))
    {
        keys= keyword-65;
    }
    else if (isalpha(keyword) && islower(keyword))
    {
        keys= keyword-97;
    }
    return keys;
}
