#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number = 0;
    int whitespace = 1; //formula to calculate whitespace on the first row (top of the pyramid) is user input - 1, 2nd row user input - 2
    int pyramidblockright = 0; //this variable is used for determining how many # to draw on the right side of the pyramid (per row)
    int pyramidblockleft = 0; //this variable is used for determining how many # to draw on the left side of the pyramid (per row)

    do
    {
        number = get_int("What is your number?\n");

    } while (number < 1 || number > 8);

    for (int counter = 0; counter < number; counter++)
    {
        if (whitespace < number)
        {
            do //This do while draws the white space needed on the left side of the pyramid.
            {
                printf(" ");
                whitespace = whitespace + 1;
            }
            while (whitespace < number);
        }

        do
        {
            printf("#");
            pyramidblockright = pyramidblockright + 1;
        }
        while (pyramidblockright <= counter);

        printf("  "); //draw empty space between left and right side of pyramid

        do
        {
            printf("#");
            pyramidblockleft = pyramidblockleft + 1;
        }
        while (pyramidblockleft <= counter);

        printf("\n"); //Set to the next row to begin drawing the next row of the pyramid

        //REINITIALIZE YOUR COUNTS APPROPRIATELY
        whitespace = counter + 2; //the white space changes with every row
        pyramidblockright = 0; //pyramid block for every row increase, you want this to match counter.
        pyramidblockleft = 0;

    }

}
