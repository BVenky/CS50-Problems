#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    long input = get_long("Enter Your Card Number: "); //Get Card Number from User
    long tmp = input;
    int *digits = malloc(1 * sizeof(int));

    //Divide input by 10 until we get 0
    int count = 0;
    int sum_alt = 0;
    while (tmp != 0)
    {
        if (count > 0)
        {
            digits = realloc(digits, (count + 1) * sizeof(int));
        }
        digits[count] = tmp % 10;   //get individual digits and store them in array

        if (count % 2)
        {
            sum_alt = sum_alt + ((digits[count] * 2) % 10) + ((digits[count] * 2) / 10);    //Multiply every other digit by 2 and add all digits
        }
        else
        {
            sum_alt = sum_alt + digits[count];  //Add digits which are not multiplied
        }

        tmp = tmp / 10;
        //printf("%d", digits[count]);
        count += 1;
    }

    //printf("\n");

    //printf("%d\n", sum_alt);

    if (sum_alt % 10)
    {
        printf("INVALID\n");
    }
    else
    {
        if (digits[count - 1] == 4)
        {
            printf("VISA\n");
        }
        else if (digits[count - 1] == 5)
        {
            for (int i = 1; i <= 5; i++)
            {
                if (digits[count - 2] == i)
                {
                    printf("MASTERCARD\n");
                }
            }
        }
        else if ((digits[count - 1] == 3) && ((digits[count - 2] == 4) || (digits[count - 2] == 7)))
        {
            printf("AMEX\n");
        }
    }

}