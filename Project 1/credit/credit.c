#include <math.h>
#include <stdio.h>
#include <cs50.h>

//PROBLEM
// AE Cards 15 digits, start with 34 or 37
// MasterCard 16 digits, start with 51, 52, 53, 54, 55
// Visa 13 or 16 digits, start with 4
// See bottom of code to see how each iteration of the luhnCRC function works

int luhnCRC(long ccnumber);

int main(void)
{
    long ccnumber = get_long("Number:");

    if (luhnCRC(ccnumber) == 0)
    {
        printf("INVALID\n");
    }

    else if (((ccnumber <= 4999999999999) && (4000000000000 <= ccnumber)) ||  ((4000000000000000 <= ccnumber) && (ccnumber <= 4999999999999999)))
    {
        printf("VISA\n");
    }

    else if (((340000000000000 <= ccnumber) && (ccnumber <= 349000000000000)) || ((370000000000000 <= ccnumber) && (ccnumber <= 379000000000000)))
    {
        printf("AMEX\n");
    }

    else if ((5100000000000000 <= ccnumber) && (ccnumber <= 5599999999999999))
    {
        printf("MASTERCARD\n");
    }

    else
        printf("INVALID\n");
}

int luhnCRC(long ccnumber)
{
    long sum1 = 0;
    long sum2 = 0;

    for (long counter = 100; counter <= 10000000000000000; counter = counter*100)
    {
        long Remainder = ccnumber%counter;
        long Digit = Remainder/(counter/10);
        int Product = Digit * 2;
        if (Product > 9)
        {
            int ProductRemainder =  Product%10; //If the digit * 2 = a number greater than 9 we need to find both the digits again. This is the 1st digit
            int SndProductDigit = Product/10; //This is the second digit.
            
            sum1 = sum1 + ProductRemainder + SndProductDigit;
            //debug
            printf("%i Product\n", Product);
            printf("%li even\n", sum1);
        }
        else
            sum1 = sum1 + Product;
            //debug
            printf("%li even Digit\n", Digit); // %li is long integer
            printf("%li even\n", sum1);




    }

    for (long counter = 10; counter <= 1000000000000000; counter = counter*100)
    {
        long Remainder = ccnumber%counter;
        long Digit = Remainder/(counter/10);
        sum2 = sum2 + Digit;

        //DEBUG
        printf("%li odd Digit\n", Digit);
        printf("%li odd\n", sum2);

    }

    long TotalSum = sum1 + sum2;
    long LuhnCRC = TotalSum%10;
    printf("%li\n",TotalSum);

    if(LuhnCRC == 0)
    {
        return 1;
    }
    else
        return 0;

}

    /* I am keeping this here so that it is easier to visualize how the for loop iterates
    int SDR = ccnumber%100;
    int SndDigit = SDR/10;

    int FDR = ccnumber%10000;
    int FthDigit = FDR/1000;

    int SixDR = ccnumber%1000000;
    int SixDigit = SixDR/100000;

    int EthDR = ccnumber%100000000;
    int EthDigit = EthDR/10000000;

    int TenDR = ccnumber%10 000 000 000;
    int TenDigit = TenDR/1000000000; */

