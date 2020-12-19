#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Get a string of text and shove it into an array. Getting a string is automatically an array.
// Parse through entire array until the /0 (NULL Character) which is the end of the array
// Convert every character in array into ascii and determine if it is an alphabet letter then increment number of letters

int main(void)
{
    string sentence = get_string("Text:");
    //printf("%s\n", sentence);
    int Letters = 0;
    int Sentences = 0;
    float L = 0;
    float S = 0;
    float index = 0;
    int gradescore = 0;

    //You may assume that a sentence will not start or end with a space, and you may assume that a sentence will not have multiple spaces in a row.
    //We initialize Words to 1 because of the above assumption, if we didn't we'd have to make some clever way of capturing these kinds of inputs.
    //If we wanted to capture the last word we could compare the last values in the array (/0 NULL) to the second last value ( !, ., ?)
    //If we wanted to capture the double space, we'd have to compare the current sentence[i] with sentence[i+1] whenever a space occurs
    //We'd also do something like the above if there was a space at the end.

    int Words = 1;

    for (int i = 0; (int) sentence[i] != 0; i++)
    {
        //printf ("%i\n", (int) sentence[i]); //(Prints Decimal Ascii Equivalent)
        if ((( 65 <= (int) sentence[i]  && (int) sentence[i] <= 90) || ( 97 <= (int) sentence[i]   && (int) sentence[i] <= 122)))
        {
            Letters++;
        }
        else if ((int) sentence[i] == 33 ||(int) sentence[i] == 46 ||(int) sentence[i] == 63)
        {
            Sentences++;
        }
        else if ((int) sentence[i] == 32)
        {
            Words++;
        }

    }

    //DEBUG
    //printf("%i Letters\n", Letters);
    //printf("%i Sentences\n", Sentences);
    //printf("%i Words\n", Words);

    L = Letters * ((float) 100/Words);
    S = Sentences * ((float) 100/Words);
    //printf("%f L index\n", L);
    //printf("%f S index\n", S);

    index = (0.0588 * L) - (0.296 * S) - 15.8;
    //printf("%f index\n", index);

    gradescore = round(index);
    if (gradescore < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (16 <= gradescore)
    {
        printf("Grade 16+\n");
    }
    else
    printf("Grade %i\n", gradescore);

}