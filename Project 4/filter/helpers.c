#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        
        int grayscaleavg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3.0);
        
        image[i][j].rgbtRed = grayscaleavg;
        image[i][j].rgbtGreen = grayscaleavg;
        image[i][j].rgbtBlue = grayscaleavg;
        
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    //This problem you need another array to hold the new image or else you'll miss half the picture because you changed the first half.
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][width - 1 - j];
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE temp[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float REDAVG = 0;
            float GREENAVG = 0;
            float BLUEAVG = 0;
            
            int xcord[] = {i-1, i, i+1};
            int ycord[] = {j-1, j, j+1};
            
            for (int n = 0; n < 3; n++)
            {
                for (int m = 0; m < 3; m++)
                {
                    int x = xcord[n];
                    int y = ycord[m];
                    
                    //CHECK IF PIXEL EXISTS
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        REDAVG = REDAVG + image[x][y].rgbtRed;
                        GREENAVG = GREENAVG + image[x][y].rgbtGreen;
                        BLUEAVG = BLUEAVG + image[x][y].rgbtBlue;
                        count++;    
                    }
                }
            }
            
            //CHECK FOR OVER 255
            REDAVG = round(REDAVG/count);
            GREENAVG = round(GREENAVG/count);
            BLUEAVG = round(BLUEAVG/count);
            
            if (REDAVG > 255.0)
                REDAVG = 255;
            
            if (GREENAVG > 255.0)
                GREENAVG = 255;
                
            if (BLUEAVG > 255.0)
                BLUEAVG = 255;
                
            
            temp[i][j].rgbtRed = REDAVG;
            temp[i][j].rgbtGreen = GREENAVG;
            temp[i][j].rgbtBlue = BLUEAVG;
        }
    }
    
    
    // Take New Image and Put Into Original Image
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE temp[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int countx = 0;
            int county = 0;
            
            float XTRED = 0;
            float XTGREEN = 0;
            float XTBLUE = 0;
            float YTRED = 0;
            float YTGREEN = 0;
            float YTBLUE = 0;
            float RED = 0;
            float GREEN = 0;
            float BLUE = 0;
            
            //Generate 3x3 Grid, Gx Matrix Multipliers, Gy Matrix Multipliers
            int xcord[] = {i-1, i, i+1};
            int ycord[] = {j-1, j, j+1};
            int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int Gy[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
            
            //Calculate Gx Red Green Blue
            for (int n = 0; n < 3; n++)
            {
                for (int m = 0; m < 3; m++)
                {
                    int x = xcord[n];
                    int y = ycord[m];
                    
                    //CHECK IF PIXEL EXISTS
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                       XTRED += Gx[countx]*image[x][y].rgbtRed;
                       XTGREEN += Gx[countx]*image[x][y].rgbtGreen;
                       XTBLUE += Gx[countx]*image[x][y].rgbtBlue;
                       countx++;
                    }
                    else
                    {
                        XTRED += 0;
                        XTGREEN += 0;
                        XTBLUE += 0;
                        countx++;
                    }
                }
            }
            
            //Calculate Gy Red Green Blue
            for (int k = 0; k < 3; k++)
            {
                for (int p = 0; p < 3; p++)
                {
                    int x = xcord[k];
                    int y = ycord[p];
                    
                    //CHECK IF PIXEL EXISTS
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                       YTRED += Gy[county]*image[x][y].rgbtRed;
                       YTGREEN += Gy[county]*image[x][y].rgbtGreen;
                       YTBLUE += Gy[county]*image[x][y].rgbtBlue;
                       county++;
                    }
                    else
                    {
                        YTRED += 0;
                        YTGREEN += 0;
                        YTBLUE += 0;
                        county++;
                    }
                }
            }
            
            //Get final Red Green Blue
            RED = round(sqrt(XTRED * XTRED + YTRED * YTRED));
            GREEN = round(sqrt(XTGREEN * XTGREEN + YTGREEN * YTGREEN));
            BLUE = round(sqrt(XTBLUE * XTBLUE + YTBLUE * YTBLUE));
            
            //CHECK IF OVER 255
            if (RED > 255.0)
                RED = 255;
            
            if (GREEN > 255.0)
                GREEN = 255;
                
            if (BLUE > 255.0)
                BLUE = 255;
                
            //Store Temporarily    
            temp[i][j].rgbtRed = RED;
            temp[i][j].rgbtGreen = GREEN;
            temp[i][j].rgbtBlue = BLUE;
        }    
    }
    
    // Take New Image and Put Into Original Image
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}
