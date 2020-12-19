#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    //Don't memory allocate until you pass initial error checking.
    //allocate 8 char size memory for file name since file names are 7 characters + null character
    char *jpeg = malloc(8);

    //the line below WORKS, but is not an accurate type. unsigned char for most systems will be 8 bit, but there will be systems where it isn't 8 bit.
    //this problem works with bytes, you should by good practice, 100% ensure the type is 8 bits/a byte
    //unsigned char bytes[SIZE];
    BYTE bytes[SIZE];
    int count = 0;
    FILE *temp;
    //Temporary


    //fread automatically reads the appropriate place, it moves the pointer. GOOGLE THIS QUESTION.
    //Also I am not 100% sure but I am pretty sure this while condition DOES NOT capture the rest of the file if the file wasn't perfectly all blocks of 512 bytes.
    //fread will return 1 if it sucesfully reads a block of 512 bytes once, if it doesnt it will return 0.
    //However, for this HW problem, yes everything is a perfect block fo 512 bytes
    while (fread(bytes, 512, 1, file) == 1)
    {
        //int readbytes = fread(bytes, 512, 1, file);
        if (bytes[0] == 0xff && bytes[1] == 0xd8  && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            //first create JPEG, OPEN for writing, write, and then close?
            if (count == 0)
            {
                sprintf(jpeg, "%03i.jpg", count);
                count++;
                //OPEN for writing the first 512 bytes
                temp = fopen(jpeg, "w");

                //write into temp 1 byte, 512 times, from bytes
                fwrite(bytes, 512, 1, temp);
            }

            else //NEW JPEG: CLOSE OLD ONE, MAKE NEW JPEG INCREMENT COUNT
            {
                fclose(temp);

                sprintf(jpeg, "%03i.jpg", count);
                count++;

                temp = fopen(jpeg, "w");

                fwrite(bytes, 512, 1, temp);
            }
        }
        else if (count > 0)
        {
            fwrite(bytes, 512, 1, temp);
        }

    }

    //close
    fclose(temp);

    //free memory allocation from earliar
    free(jpeg);
}
