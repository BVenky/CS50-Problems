#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height=0;
    do
    {
        height=get_int("Height: "); //Get Height from User Until Condition is true
    }
    while(height<1 || height>8);
    for(int i=1;i<=height;i++)  //Loop for Rows
    {
        for(int k=0;k<height;k++) //Loop for Columns
        {
            if(k<height-i)
            {
                printf(" ");    //Print spaces
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}