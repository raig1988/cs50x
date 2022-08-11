#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float formulacalc(int countletters, int countwords, int countsentences);

// main program printing grades includes asking input from user and 3 different type of responses
int main(void)
{
    // prompt user for input
    string text = get_string("Text: ");
    // initialize each data type used on the output and compare with the string
    int countletters = count_letters(text);
    int countwords = count_words(text);
    int countsentences = count_sentences(text);
    // initialize the formula
    float index = formulacalc(countletters, countwords, countsentences);
    // conditions for every output shown
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}
// function that counts each letter in the array if its alphabetic
int count_letters(string text)
{
    int countletters = 0;

    for (int i = 0, characters = strlen(text); i < characters; i++)
    {
        if (isalpha(text[i]))
        {
            countletters += 1;
        }
    }
    return countletters;
}
// function that counts each word in the array by counting spaces and adding 1 at the end.
int count_words(string text)
{
    int countwords = 0;

    for (int i = 0, characters = strlen(text); i < characters; i++)
    {
        if (isspace(text[i]))
        {
            countwords += 1;
        }
    }
    return countwords + 1;
}
// function that counts sentences if they end on dot, exclamation or interrogration
int count_sentences(string text)
{
    int countsentences = 0;

    for (int i = 0, characters = strlen(text); i < characters; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            countsentences += 1;
        }
    }
    return countsentences;
}
// formula that calculates index by data type float casting int data types
float formulacalc(int countletters, int countwords, int countsentences)
{
    float index;
    float L = ((float)countletters / countwords) * 100;
    float S = ((float)countsentences / countwords) * 100;
    return index = 0.0588 * L - 0.296 * S - 15.8;
}