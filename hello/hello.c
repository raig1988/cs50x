#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // asks name
    string name = get_string("What's your name? ");

    // shows name
    printf("hello, %s\n", name);
}