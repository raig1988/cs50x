#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen;
            int average = round(sum / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflect_left;
    RGBTRIPLE reflect_right;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            reflect_left = image[i][width - j - 1];
            reflect_right = image[i][j];
            image[i][j] = reflect_left;
            image[i][width - j - 1] = reflect_right;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{


    // create a copy first
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    // all within 1 row & 1 column
    // 9 pixel grid (3x3)
    for (int i = 1; i <= height - 2; i++)
    {
        for (int j = 1; j <= width - 2; j++)
        {
            float center_grid_red = copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
            float center_grid_green = copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
            float center_grid_blue = copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
            int center_grid_average_red = round((center_grid_red) / 9.0);
            int center_grid_average_green = round((center_grid_green) / 9.0);
            int center_grid_average_blue = round((center_grid_blue) / 9.0);
            image[i][j].rgbtRed = center_grid_average_red;
            image[i][j].rgbtGreen = center_grid_average_green;
            image[i][j].rgbtBlue = center_grid_average_blue;
        }
    }


    // edge cases 6 pixels grid
    for (int i = 1; i <= height - 2; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) // left edge
            {
                float edge_left_red = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i+1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                float edge_left_green = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                float edge_left_blue = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                int edge_left_average_red = round((edge_left_red) / 6);
                int edge_left_average_green = round((edge_left_green) / 6);
                int edge_left_average_blue = round((edge_left_blue) / 6);
                image[i][j].rgbtRed = edge_left_average_red;
                image[i][j].rgbtGreen = edge_left_average_green;
                image[i][j].rgbtBlue = edge_left_average_blue;
            }
            if (j == width - 1) // right edge
            {
                float edge_right_red = copy[i][width - 1].rgbtRed + copy[i][width - 2].rgbtRed + copy[i+1][width - 1].rgbtRed + copy[i + 1][width - 2].rgbtRed + copy[i - 1][width - 1].rgbtRed + copy[i - 1][width - 2].rgbtRed;
                float edge_right_green = copy[i][width - 1].rgbtGreen + copy[i][width - 2].rgbtGreen + copy[i+1][width - 1].rgbtGreen + copy[i + 1][width - 2].rgbtGreen + copy[i - 1][width - 1].rgbtGreen + copy[i - 1][width - 2].rgbtGreen;
                float edge_right_blue = copy[i][width - 1].rgbtBlue + copy[i][width - 2].rgbtBlue + copy[i+1][width - 1].rgbtBlue + copy[i + 1][width - 2].rgbtBlue + copy[i - 1][width - 1].rgbtBlue + copy[i - 1][width - 2].rgbtBlue;
                int edge_right_average_red = round((edge_right_red) / 6);
                int edge_right_average_green = round((edge_right_green) / 6);
                int edge_right_average_blue = round((edge_right_blue) / 6);
                image[i][j].rgbtRed = edge_right_average_red;
                image[i][j].rgbtGreen = edge_right_average_green;
                image[i][j].rgbtBlue = edge_right_average_blue;
            }

        }
    }


    for (int i = 0; i < height; i++) // corner cases
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) // top left corner
            {
                float top_left_corner_red = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                float top_left_corner_green = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                float top_left_corner_blue = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                int top_left_corner_average_red = round((top_left_corner_red) / 4);
                int top_left_corner_average_green = round((top_left_corner_green) / 4);
                int top_left_corner_average_blue = round((top_left_corner_blue) / 4);
                image[i][j].rgbtRed = top_left_corner_average_red;
                image[i][j].rgbtGreen = top_left_corner_average_green;
                image[i][j].rgbtBlue = top_left_corner_average_blue;
            }
            if (i == 0 && j == width - 1) // top right corner
            {
                float top_right_corner_red = copy[i][width - 1].rgbtRed + copy[i][width - 2].rgbtRed + copy[i + 1][width - 1].rgbtRed + copy[i + 1][width - 2].rgbtRed;
                float top_right_corner_green = copy[i][width - 1].rgbtGreen + copy[i][width - 2].rgbtGreen + copy[i + 1][width - 1].rgbtGreen + copy[i + 1][width - 2].rgbtGreen;
                float top_right_corner_blue = copy[i][width - 1].rgbtBlue + copy[i][width - 2].rgbtBlue + copy[i + 1][width - 1].rgbtBlue + copy[i + 1][width - 2].rgbtBlue;
                int top_right_corner_average_red = round((top_right_corner_red) / 4);
                int top_right_corner_average_green = round((top_right_corner_green) / 4);
                int top_right_corner_average_blue = round((top_right_corner_blue) / 4);
                image[i][width -1].rgbtRed = top_right_corner_average_red;
                image[i][width -1].rgbtGreen = top_right_corner_average_green;
                image[i][width -1].rgbtBlue = top_right_corner_average_blue;
            }
            if (i == height - 1 && j == 0) // bottom left corner
            {
                float bottom_left_corner_red = copy[height - 1][j].rgbtRed + copy[height - 1][j + 1].rgbtRed + copy[height - 2][j].rgbtRed + copy[height - 2][j + 1].rgbtRed;
                float bottom_left_corner_green = copy[height - 1][j].rgbtGreen + copy[height - 1][j + 1].rgbtGreen + copy[height - 2][j].rgbtGreen + copy[height - 2][j + 1].rgbtGreen;
                float bottom_left_corner_blue = copy[height - 1][j].rgbtBlue + copy[height - 1][j + 1].rgbtBlue + copy[height - 2][j].rgbtBlue + copy[height - 2][j + 1].rgbtBlue;
                int bottom_left_corner_average_red = round((bottom_left_corner_red) / 4);
                int bottom_left_corner_average_green = round((bottom_left_corner_green) / 4);
                int bottom_left_corner_average_blue = round((bottom_left_corner_blue) / 4);
                image[height - 1][j].rgbtRed = bottom_left_corner_average_red;
                image[height - 1][j].rgbtGreen = bottom_left_corner_average_green;
                image[height - 1][j].rgbtBlue = bottom_left_corner_average_blue;
            }
            if (i == height - 1 && j == width - 1) // bottom right corner
            {
                float bottom_right_corner_red = copy[height - 1][width -1].rgbtRed + copy[height - 1][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed + copy[height - 2][width - 2].rgbtRed;
                float bottom_right_corner_green = copy[height - 1][width -1].rgbtGreen + copy[height - 1][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen + copy[height - 2][width - 2].rgbtGreen;
                float bottom_right_corner_blue = copy[height - 1][width -1].rgbtBlue + copy[height - 1][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue + copy[height - 2][width - 2].rgbtBlue;
                int bottom_right_corner_average_red = round((bottom_right_corner_red) / 4);
                int bottom_right_corner_average_green = round((bottom_right_corner_green) / 4);
                int bottom_right_corner_average_blue = round((bottom_right_corner_blue) / 4);
                image[height - 1][width - 1].rgbtRed = bottom_right_corner_average_red;
                image[height - 1][width - 1].rgbtGreen = bottom_right_corner_average_green;
                image[height - 1][width - 1].rgbtBlue = bottom_right_corner_average_blue;
            }
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
