#include <stdio.h>
#include <cs50.h>

int main(void)
{

    string name = get_string("What is your name?\n"); //This line asks the user for their name and assigns it to the string variable "name"
    printf("Hello, %s\n", name); //This line will say hello to the given user input.

}