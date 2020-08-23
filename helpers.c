#include "helpers.h"
#include "math.h"
#include <stdint.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float avg = 0;
            avg = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / (float) 3);
            image[h][w].rgbtBlue = (uint8_t) avg;
            image[h][w].rgbtGreen = (uint8_t) avg;
            image[h][w].rgbtRed = (uint8_t) avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            uint8_t sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            uint8_t sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            uint8_t sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            image[h][w].rgbtBlue = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtRed = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
