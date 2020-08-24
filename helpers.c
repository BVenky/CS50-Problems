#include "helpers.h"
#include "math.h"
#include <stdint.h>
#include "stdio.h"

int getSliceAvg(int tmpH, int tmpW, int h, int w, int color, RGBTRIPLE image[h][w]);
int getEdgeValue(int tmpH, int tmpW, int h, int w, int color, RGBTRIPLE image[h][w]);
int square(int number);

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
            sum = sum + 0;
            //divd--;
        }
        else
        {
            // Keep adding to sum variable
            if (color == 0)
            {
                sum = sum + image[tmpH][tmpW + k].rgbtRed;
            }
            else if (color == 1)
            {
                sum = sum + image[tmpH][tmpW + k].rgbtBlue;
            }
            else if (color == 2)
            {
                sum = sum + image[tmpH][tmpW + k].rgbtGreen;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpIm[height][width];
    for (int h = 0; h < height; h++)
    {
        int tmpH = h - 1;
        for (int w = 0; w < width; w++)
        {
            int tmpW = w - 1;

            // get the averages of a slice to smoothen the image
            int edgeRed = getEdgeValue(tmpH, tmpW, height, width, 0, image);
            int edgeBlue = getEdgeValue(tmpH, tmpW, height, width, 1, image);
            int edgeGreen = getEdgeValue(tmpH, tmpW, height, width, 2, image);

            // Restrict values beyond 255 to 255 and values below 0 to 0
            if (edgeRed > 255)
            {
                edgeRed = 255;
            }
            else if (edgeRed < 0)
            {
                edgeRed = 0;
            }
            if (edgeBlue > 255)
            {
                edgeBlue = 255;
            }
            else if (edgeBlue < 0)
            {
                edgeBlue = 0;
            }
            if (edgeGreen > 255)
            {
                edgeGreen = 255;
            }
            else if (edgeGreen < 0)
            {
                edgeGreen = 0;
            }

            tmpIm[h][w].rgbtRed = (uint8_t) edgeRed;
            tmpIm[h][w].rgbtBlue = (uint8_t) edgeBlue;
            tmpIm[h][w].rgbtGreen = (uint8_t) edgeGreen;
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

//Calculate edges using Gx and Gy filters within distance 1 of the input element
int getEdgeValue(int tmpH, int tmpW, int h, int w, int color, RGBTRIPLE image[h][w])
{
    int k = 0;
    int sumx = 0;
    int sumy = 0;

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};

    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};

    int tmpMul[3][3];
    int ctH = 0;
    for (int i = 0; i < 9; i++)
    {

        // Condition to avoid indexing error for index less than 0 and greater than max height or width
        if (tmpH < 0 || tmpW + k < 0 || tmpH >= h || tmpW + k >= w)
        {
            sumx = sumx + 0;
            sumy = sumy + 0;
            //divd--;
        }
        else
        {
            // Keep adding to sum variable
            if (color == 0)
            {
                sumx = sumx + image[tmpH][tmpW + k].rgbtRed * gx[ctH][k] ;
                sumy = sumy + image[tmpH][tmpW + k].rgbtRed * gy[ctH][k] ;
            }
            else if (color == 1)
            {
                sumx = sumx + image[tmpH][tmpW + k].rgbtBlue * gx[ctH][k] ;
                sumy = sumy + image[tmpH][tmpW + k].rgbtBlue * gy[ctH][k] ;
            }
            else if (color == 2)
            {
                sumx = sumx + image[tmpH][tmpW + k].rgbtGreen * gx[ctH][k] ;
                sumy = sumy + image[tmpH][tmpW + k].rgbtGreen * gy[ctH][k] ;
            }
        }
        if (k == 2)
        {
            k = 0;
            tmpH += 1;
            ctH += 1;
        }
        else
        {
            k++;
        }

    }

    int sum = square(sumx) + square(sumy);//Calculate final value using sobel formula
    return (int) round(sum); // Round the average and return
}

int square(int number)
{
    int sq = number * number;
    return sq;
}