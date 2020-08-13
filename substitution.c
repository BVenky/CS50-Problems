#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];   //Collect key from command line argument
        int len = strlen(key);  //get the length of the key
        int lowerStart = 65;
        int higherStart = 97;

        if (len == 26)  //Condition 1 to check length of key equals 26
        {
            int tmp[len];
            for (int i = 0; i < len; i++)
            {
                if (!(key[i] >= 97 && key[i] <= 122) && !(key[i] >= 65 && key[i] <= 90))    //Check if key consists of only alphabets
                {
                    return 1;
                }
                else
                {
                    for (int j = 0; j < len; j++)
                    {
                        if (tmp[j] == (int) key[i]) //check if any character in key is repeated
                        {
                            return 1;
                        }
                    }
                    tmp[i] = key[i];
                }
            }
            string input = get_string("plaintext:");    //get input text from user to encode
            int ipLen = strlen(input);
            printf("ciphertext:");

            //Loop over the input text and encode each individual character
            for (int i = 0; i < ipLen; i++)
            {
                int keyIndex;
                if (input[i] <= 122 && input[i] >= 97)
                {
                    keyIndex = input[i] - 97;
                    printf("%c", tolower(key[keyIndex]));   //print encoded key as lower if input is lower as well
                }
                else if (input[i] <= 90 && input[i] >= 65)
                {
                    keyIndex = input[i] - 65;
                    printf("%c", toupper(key[keyIndex]));   //print encoded key as upper if input is upper as well
                }
                else
                {
                    printf("%c", input[i]);
                }
                //printf("%i", input[i]);
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Key is Invalid\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substituion key\n");
        return 1;
    }
}