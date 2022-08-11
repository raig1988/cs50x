#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h, row, column, space;
    // asks user for input and returns value within parameters (more equal 1 but less equal 8)
    do
    {
        h = get_int("How tall?: ");
    }
    while (h < 1 || h > 8);

    // we need to draw a pyramid right sided with variables as row, column, dashes and spaces
    for (row = 0; row < h; row++)
    {
        // nested loop for spaces depend on height and row as main variables (-1 is the pattern found for the equation)
        for (space = 0; space < h - row - 1  ; space++)
        {
            printf(" ");
        }
        // nested loop for column depending on rows
        for (column = 0; column <= row ; column++)
        {
            printf("#");
        }

        printf("\n");
    }
}
