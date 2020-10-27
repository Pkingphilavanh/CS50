#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change = 0.00;

    do
    {
        change = get_float("Change owed: ");

    }
    while (change < 0.00);

    //Convert the change to a total amount of cents and round it to the nearest penny.
    int cent = round(change * 100);

    // Get remainder from quarters and get # of quarters
    int Remainder25C = cent%25;
    int TotalQuarter = cent/25;

    // Get remainder from dimes and get # of dimes
    int Remainder10C = Remainder25C%10;
    int TotalDime = Remainder25C/10;

    // Get remainder from nickelss and get # of nickels
    int Remainder5C = Remainder10C%5; //Remainder here is actually the number of pennies too ONLY if the input is > 0.04
    int TotalNickel = Remainder10C/5;

    // Get remainder from pennies and get # of pennies
    int Remainder1C = Remainder5C%1;
    int TotalPenny = Remainder5C/1;

    int Coins = TotalQuarter + TotalDime + TotalNickel + TotalPenny;

    printf("%i\n",Coins);

    //debug
    /*
    printf("%i cents\n",cent);

    printf("%i remaining cents \n",Remainder25C);
    printf("%i Quarters \n",TotalQuarter);

    printf("%i remaining cents \n",Remainder10C);
    printf("%i Dimes \n",TotalDime);

    printf("%i Nickel \n",TotalNickel);

    printf("%i Pennies \n",Remainder5C);

    printf("%i Coins \n",Coins);

    */
}
