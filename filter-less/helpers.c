#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) // 2d array of rgbtriples
{
    int gray;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            gray = round((image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) / 3.0);
            gray = (BYTE)gray;
            image[row][column].rgbtBlue = image[row][column].rgbtGreen = image[row][column].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int limit = 255;
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            sepiaRed = round(.393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 * image[row][column].rgbtBlue);
            sepiaGreen = round(.349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue);
            sepiaBlue = round(.272 * image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue);
            if (sepiaRed > limit)
            {
                image[row][column].rgbtRed = limit;
            }
            else
            {
                image[row][column].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > limit)
            {
                image[row][column].rgbtGreen = limit;
            }
            else
            {
                image[row][column].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > limit)
            {
                image[row][column].rgbtBlue = limit;
            }
            else
            {
                image[row][column].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // if even numbers, every pixel switch positions
    // if odd, middle pixel remains same
    RGBTRIPLE tmp;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++) // width / 2 so it doesnt pass through same pixel making the image same as original
        {
            tmp = image[row][column];                            // tmp = 0
            image[row][column] = image[row][width - column - 1]; // 0 = 10 - 0 - 1 (array width - current column - 1 (because it started with 0))
            image[row][width - column - 1] = tmp;                // 10 - 0 - 1 = tmp
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of image[][] by declaring a new 2d array like RGBTRIPLE copy[height][width];
    // and copying image into copy pixel by pixel with nested for loops.
    // and then read pixels colors from copy but write pixels colors in image
    // Box blur: takes each pixel for each color value, giving it a new value by averaging the color values of neighboring pixels
    // new value of each pixel is average of values of all pixels within 1 row and column of original pixel and also the pixel (3x3 box)
    //let us a temporary one that will help us store pixels inorder to avoid overwriting any

    RGBTRIPLE copy[height][width];
    //initialize temporary image structure;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column].rgbtBlue = image[row][column].rgbtBlue;
            copy[row][column].rgbtGreen = image[row][column].rgbtGreen;
            copy[row][column].rgbtRed = image[row][column].rgbtRed;
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int counterRed = 0;
            int counterBlue = 0;
            int counterGreen = 0;
            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;
            for (int i = - 1; i < 2; i++)
            {
                for (int j = - 1; j < 2; j++)
                {
                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }
                    if (j + column < 0 || j + column > width - 1)
                    {
                        continue;
                    }
                    if (copy[i + row][j + column].rgbtRed >= 0)
                    {
                        counterRed++; // 6
                        averageRed = averageRed + copy[i + row][j + column].rgbtRed; // 0 + 200 + 200 + 150 + 200 + 200 = 950
                    }
                    if (copy[i + row][j + column].rgbtBlue >= 0)
                    {
                        counterBlue++;
                        averageBlue += copy[i + row][j + column].rgbtBlue;
                    }
                    if (copy[i + row][j + column].rgbtGreen >= 0)
                    {
                        counterGreen++;
                        averageGreen += copy[i + row][j + column].rgbtGreen;
                    }
                }
            }
            image[row][column].rgbtRed = round(averageRed / (counterRed * 1.0));
            image[row][column].rgbtGreen = round(averageGreen / (counterGreen * 1.0));
            image[row][column].rgbtBlue = round(averageBlue / (counterBlue * 1.0));
        }
    }
    return;
}

