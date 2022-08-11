#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, row, column, space;

    do
    {
        height = get_int("What height: ?");
    }
    while (height < 1 || height > 8);
    // primary function that sets base for drawing
    for (row = 0; row < height; row++)
    {
        // space pushes column for pyramid 1 at depends on a constant(height) and an independent variable (row)
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }
        // pyramid 1
        for (column = 0; column <= row; column++)
        {
            printf("#");
        }
        // space between pyramids set between executing programs
        printf("  ");
        // pyramid 2
        for (column = 0; column <= row; column++)
        {
            printf("#");
        }
        printf("\n");
    }
}