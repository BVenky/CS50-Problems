#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input;
    do
    {
        input = get_float("Enter the Change owed by us: ");   //Get change owed from the user
    }
    while (input < 0);

    int coins[4] = {25, 10, 5, 1};
    int numOfcoins[4] = {0, 0, 0, 0};

    int tmpInput = round(input * 100);  //convert dollars to cents
    int totalCoins = 0;

    for (int i = 0; i < 4; i++)
    {
        numOfcoins[i] = tmpInput / coins[i];    //get absolute value by dividing input value by coin value
        tmpInput = tmpInput - (numOfcoins[i] * coins[i]);   //now minus the value from input value
        totalCoins = totalCoins + numOfcoins[i];
    }
    printf("%d\n", totalCoins);

}