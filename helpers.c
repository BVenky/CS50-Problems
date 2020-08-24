#include "helpers.h"
#include "math.h"
#include <stdint.h>
#include "stdio.h"

int getSliceAvg(int tmpH, int tmpW, int h, int w, int color, RGBTRIPLE image[h][w]);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float avg = 0;

            // Calculate average and round the value
            avg = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / (float) 3);

            // Update values into the main
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
            //formula to sepiaRed
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            //formula to sepiaGreen
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            //formula to sepiaBlue
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            // Restrict values beyond 255 to 255 and values below 0 to 0
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }

            // Update the values in the main struct
            image[h][w].rgbtBlue = (uint8_t) sepiaBlue;
            image[h][w].rgbtGreen = (uint8_t) sepiaGreen;
            image[h][w].rgbtRed = (uint8_t) sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpwidth = width / 2;
    // Check if width is even or odd
    if (width % 2 == 0)
    {
        tmpwidth = tmpwidth - 1;
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w <= tmpwidth; w++)
        {
            if (width % 2 != 0 && w == tmpwidth)
            {
                continue;
            }
            RGBTRIPLE tmp = image[h][w]; // Hold temp value to copy

            // Switch Values
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpIm[height][width];
    for (int h = 0; h < height; h++)
    {
        int tmpH = h - 1;
        for (int w = 0; w < width; w++)
        {
            int tmpW = w - 1;

            // get the averages of a slice to smoothen the image
            tmpIm[h][w].rgbtRed = (uint8_t) getSliceAvg(tmpH, tmpW, height, width, 0, image);;
            tmpIm[h][w].rgbtBlue = (uint8_t) getSliceAvg(tmpH, tmpW, height, width, 1, image);
            tmpIm[h][w].rgbtGreen = (uint8_t) getSliceAvg(tmpH, tmpW, height, width, 2, image);
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Copy the updated temporary image into the main image struct
            image[j][i].rgbtBlue = tmpIm[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tmpIm[j][i].rgbtGreen;
            image[j][i].rgbtRed = tmpIm[j][i].rgbtRed;
        }
    }
    return;
}

//Get average of the elements within distance 1 of the input element
int getSliceAvg(int tmpH, int tmpW, int h, int w, int color, RGBTRIPLE image[h][w])
{
    int k = 0;
    float sum = 0;
    int divd = 0;
    for (int i = 0; i < 9; i++)
    {

        // Condition to avoid indexing error for index less than 0 and greater than max height or width
        if (tmpH < 0 || tmpW + k < 0 || tmpH >= h || tmpW + k >= w)
        {
            avg = avg + 0;
            //divd--;
        }
        else
        {
            // Keep adding to sum variable
            if (color == 0)
            {
                avg = avg + image[tmpH][tmpW + k].rgbtRed;
            }
            else if (color == 1)
            {
                avg = avg + image[tmpH][tmpW + k].rgbtBlue;
            }
            else if (color == 2)
            {
                avg = avg + image[tmpH][tmpW + k].rgbtGreen;
            }
            divd++; //increment the number of elements counter
        }
        if (k == 2)
        {
            k = 0;
            tmpH += 1;
        }
        else
        {
            k++;
        }

    }

    float avg = sum / divd; // Calculate Average
    return (int) round(avg); // Round the average and return
}