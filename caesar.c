#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int getpower(int value, int raisedto);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string input = argv[1];
        int len = strlen(input);
        int num = 0;

        for (int i = 0; i < len; i++)
        {
            if (isdigit((unsigned) input[i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
            else
            {
                int val = input[i] - 48;
                int mul = 0;

                num = num + (val * getpower(10, len - i - 1));
            }

        }
        //printf("%i\n", num);
        string userIp = get_string("plaintext:");   //get user input
        int iplen = strlen(userIp);

        if (num < 0)    //return error condition if key is < 0
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else if (num >= 0)  //if the condition is perfect this is where it is happening
        {
            int Index;
            printf("ciphertext:");
            for (int i = 0; i < iplen; i++)
            {
                if (userIp[i] <= 122 && userIp[i] >= 97)
                {
                    Index = ((userIp[i] - 96) + (num)) % 26;
                    printf("%c", Index + 96);  //print encoded key as lower if input is lower as well
                }
                else if (userIp[i] <= 90 && userIp[i] >= 65)
                {
                    Index = ((userIp[i] - 64) + (num)) % 26;
                    printf("%c", Index + 64);   //print encoded key as upper if input is upper as well
                }
                else
                {
                    printf("%c", userIp[i]);
                }

            }
            printf("\n");
        }
    }
    else
    {
        return 1;
    }
}

int getpower(int value, int raisedto)   //Function to get the power of a value
{
    if (raisedto >= 0 && value >= 0)
    {
        int retValue = 1;
        if (raisedto != 0)
        {
            if (retValue > 0)
            {
                for (int i = 1; i <= raisedto; i++)
                {
                    retValue = retValue * value;    //multiply value for the power number of times
                }
                return retValue;    //return Final Value
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}