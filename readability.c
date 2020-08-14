#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string input = get_string("Text: "); //get input from user
    int len = strlen(input);    //get len of characters in input
    int lettersCount = 0;
    int wordsCount = 0;
    int sentencesCount = 0;

    for (int i = 0; i < len; i++)
    {
        if ((input[i] >= 97 && input[i] <= 122) || (input[i] >= 65 && input[i] <= 90))  //Condition to check for letters
        {
            lettersCount += 1;
        }
        else  if (input[i] == 33 || input[i] == 46 || input[i] == 63)   //Condition to get sentences
        {
            sentencesCount += 1;
            wordsCount += 1;
        }
        else if (i > 0 && input[i - 1] != 33 && input[i - 1] != 46 && input[i - 1] != 63 && input[i] == 32)
        {
            wordsCount += 1;
        }
    }

    float avgletters = (lettersCount * 100) / (float) wordsCount;   //Get average letters per 100 words
    float avgSentences = (sentencesCount * 100) / (float) wordsCount;   //Get average sentences pper 100 words
    int index = round(0.0588 * avgletters - 0.296 * avgSentences - 15.8);
    //printf("Letters Count: %i\nWord Count: %i\nSentences Count: %i\nAvg Letters: %.2f\nAvg Sentences: %.2f\n", lettersCount, wordsCount,
    //       sentencesCount, avgletters, avgSentences);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }


}
