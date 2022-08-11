#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // GET KEY
    int count = 0;

    // VALIDATE KEY

    // check for only 2 arguments
    if (argc != 2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }
    // check key length
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        count++;
    }
    if (count != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // check if its alphabetical characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }
    // check for repeated characters (pending)
    for (int i = 0, j = strlen(argv[1]); i < j; i++)
    {
        for (int k = i + 1; k < j; k++)
        {
            if (toupper(argv[1][i]) == toupper(argv[1][k]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    // GET PLAINTEXT FROM USER
    string plaintext = get_string("plaintext: ");
    // ENCIPHER
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            for (int k = 65; k < 91; k++)
            {
                if (plaintext[i] == k)
                {
                    plaintext[i] = toupper(argv[1][k - 65]);
                    break;
                }
            }
        }
        else if (islower(plaintext[i]))
        {
            for (int j = 97; j < 123; j++)
            {
                if (plaintext[i] == j)
                {
                    plaintext[i] = tolower(argv[1][j - 97]);
                    break;
                }
            }
        }
    }
    // PRINT CIPHERTEXT
    string ciphertext = plaintext;
    printf("ciphertext: %s\n", ciphertext);
}