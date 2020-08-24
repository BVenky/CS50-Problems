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
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
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
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //printf("Avg: %i\n", (uint8_t) getSliceAvg(398, 598, height, width, 2, image));
    //printf("Height: %i Width: %i\n", height, width);
    for (int h = 0; h < height; h++)
    {
        int tmpH = h - 1;
        for (int w = 0; w < width; w++)
        {
            int tmpW = w - 1;

            //getSliceAvg(tmpH, tmpW, image);
            int blurRed = getSliceAvg(tmpH, tmpW, height, width, 0, image);
            int blurBlue = getSliceAvg(tmpH, tmpW, height, width, 1, image);
            int blurGreen = getSliceAvg(tmpH, tmpW, height, width, 2, image);

            if (blurRed > 255)
            {
                blurRed = 255;
            }
            else if (blurRed < 0)
            {
                blurRed = 0;
            }
            if (blurGreen > 255)
            {
                blurGreen = 255;
            }
            else if (blurGreen < 0)
            {
                blurGreen = 0;
            }
            if (blurBlue > 255)
            {
                blurBlue = 255;
            }
            else if (blurBlue < 0)
            {
                blurBlue = 0;
            }

            image[h][w].rgbtRed = (uint8_t) blurRed;
            image[h][w].rgbtBlue = (uint8_t) blurBlue;
            image[h][w].rgbtGreen = (uint8_t) blurGreen;
        }
    }
    return;
}

int getSliceAvg(int tmpH, int tmpW, int h, int w, int color, RGBTRIPLE image[h][w])
{
    int k = 0;
    float avg = 0;
    int divd = 9;
    for (int i = 0; i < 9; i++)
    {

        if (tmpH < 0 || tmpW + k < 0 || tmpH >= h || tmpW + k >= w)
        {
            avg = avg + 0;
            divd--;
        }
        else
        {
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
            //printf("tmpH: %i tmpW: %i h: %i w: %i\n", tmpH, tmpW + k, h, w);
            //printf("Rval: %i\n", image[tmpH][tmpW + k].rgbtRed);
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
    //printf("divd: %i\n", divd);
    avg = avg / 9;
    return (int) round(avg);
}