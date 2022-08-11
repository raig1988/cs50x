#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char p, int k);

int main(int argc, string argv[])
{
    // tests if argc is less than 3 or more than 1
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // checks if input is only digits on string
    for (int i = 0, length = strlen(argv[i]); i < length ; i++)
    {
        if (only_digits(argv[1]) < 1)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //converts array box into an integer
    int k = atoi(argv[1]);
    char ciphertext;
    // ask user for the plaintext
    string plaintext = get_string("plaintext:  ");
    // print ciphertext where you will show the result
    printf("ciphertext: ");
    for (int p = 0, l = strlen(plaintext); p < l ; p++)
    {
        ciphertext = rotate(plaintext[p], k);
        printf("%c", ciphertext);
    }
    printf("\n");
    return 0;
}
// function to find if user input is a digit or not
bool only_digits(string s)
{
    int detect = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        // if char is a digit, it adds up
        if (isdigit(s[i]))
        {
            detect += 1;
        }
        else
        {
            return 0;
        }
    }
    return detect;
}
// criptographic function to change characters according to a key
char rotate(char p, int k)
{
    if (isalpha(p))
    {
        if (isupper(p))
        {
            return (((int)p - 65 + k) % 26) + 65;
        }
        else if (islower(p))
        {
            return (((int)p - 97 + k) % 26) + 97;
        }
    }
    else
    {
        return p;
    }
    return 0;
}