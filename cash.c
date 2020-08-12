#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input = get_float("Enter the Change owed by us: ");   //Get change owed from the user
    int coins[4] = {25, 10, 5, 1};
    int numOfcoins[4] = {0, 0, 0, 0};

    int tmpInput = round(input * 100);
    int totalCoins = 0;

    for (int i = 0; i < 4; i++)
    {
        numOfcoins[i] = tmpInput / coins[i];
        tmpInput = tmpInput - (numOfcoins[i] * coins[i]);
        totalCoins = totalCoins + numOfcoins[i];
    }

}