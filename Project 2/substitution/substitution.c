#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int checkrepeat[128] = {0};
    int repeated = 0;
    int k = 0;
    
    //This variable is used to decrease the ascii value to between 0 and 25 from the plaintext to align it with the key array values
    int convert = 0;

    //Check if valid command line input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    //Check if valid key length
    int KEYLENGTH = strlen(argv[1]);

    if (KEYLENGTH != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //Check if valid character in key AND check for repeated characters
    for (int i = 0; i < KEYLENGTH; i++)
    {
        k = argv[1][i];
        //debug
        //printf("%i \n",k);
        //printf("%c \n", argv[1][i]);
        
        if ((0 <= k && k <= 64) || ( 91 <= k && k <= 96) || ( 123 <= k && k <= 127))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (checkrepeat[k] == 0)
            checkrepeat[k]++;
        else
        {
            repeated++;
            break;
        }
    }
    
    //if repeated characters, print error
    if (1 <= repeated)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
     
    //get text
    //convert plaintext array to its cipher value
    //after convert ensure its the same case as before
    //if it isnt an actual letter, just keep the same.
    string plaintext = get_string("plainttext: ");
    int ptlength = strlen(plaintext);
    string ciphertext = plaintext;
    
    for (int p = 0; p < ptlength; p++)
    {
        if (65 <= plaintext[p] && plaintext[p] <= 90)
        {
            convert = plaintext[p] - 65;
            ciphertext[p] = toupper(argv[1][convert]);
        }
        else if (97 <= plaintext[p] && plaintext[p] <= 122)
        {
            convert = plaintext[p] - 97;
            ciphertext[p] = tolower(argv[1][convert]);
        }
        else
            ciphertext[p] = plaintext[p];
    }
    
    printf("ciphertext: %s\n",ciphertext);
    return 0;
}