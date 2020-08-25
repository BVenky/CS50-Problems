#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"

int main(int argc, char *argv[])
{
    //Check if correct number of arguments are entered
    if (argc != 2)
    {
        printf("Usage ./render (raw file path)\n"); //Prompt Usage
        return 1;
    }
    //Read Raw File
    FILE *rawfile = fopen(argv[1], "r");

    //Check if the file is valid and opened
    if (rawfile == NULL)
    {
        printf("Cannot open Raw file\n");
        return 1;
    }

    //Define a Char array block of size 512
    unsigned char *bytes = malloc(512);
    int byteCount = 0, count = 0;

    FILE *img;
    // Read file in blocks of size 512
    char *filename = malloc(7);
    while (fread(bytes, 512, 1, rawfile))
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xe0) == 0xe0)
        {
            if (count > 0)
            {
                fclose(img);
            }
            printf("True %i\n", count);
            sprintf(filename, "%03d.jpg", count);

            img = fopen(filename, "w");

            if (img == NULL)
            {
                fclose(img);
                free(bytes);
                free(filename);
                free(rawfile);
                return 1;
            }
            count++;
        }
        byteCount++;

        if (byteCount == 512)
        {
            byteCount = 0;
        }

    }

    if (count > 0)
    {
        fwrite(bytes, 512, 1, img);
    }
    fclose(img);
    free(bytes);
    free(filename);
    free(rawfile);
    return 0;

}
