#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Height: "); //Get Height from User Until Condition is true
    }
    while (height < 1 || height > 8);

    //Loop for Rows
    for (int i = 1; i <= height; i++)
    {
        //Loop for Columns
        for (int k = 0; k < height; k++)
        {
            if (k < height - i)
            {
                printf(" ");    //Print spaces
            }
            else
            {
                printf("#");
            }
        }

        printf("  ");

        //Loop for 2nd Half
        for (int k = 0; k < height; k++)
        {
            if (k <= i - 1)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}