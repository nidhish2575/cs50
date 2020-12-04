#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // to loop over every pixel
    for(int i=0; i< height; i++){

        for(int j=0; j< width; j++){


            int av= round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3.0 );

            image[i][j].rgbtRed=image[i][j].rgbtBlue=image[i][j].rgbtGreen=av;

        }

    }
              return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++){

        for(int j=0; j< width; j++){

            int sepiaRed = round(.393 *image[i][j].rgbtRed  + .769 *image[i][j].rgbtGreen  + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 *image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 *image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if(sepiaBlue>255){
              image[i][j].rgbtBlue=255;
            }
            else{
                 image[i][j].rgbtBlue=sepiaBlue;
            }

            if(sepiaRed>255){
              image[i][j].rgbtRed=255;
            }
            else{
                 image[i][j].rgbtRed=sepiaRed;
            }

            if(sepiaGreen>255){
              image[i][j].rgbtGreen=255;
            }
            else{
                 image[i][j].rgbtGreen=sepiaGreen;
            }


        }
    }

    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a copy of original image and then making changes to the copy
    RGBTRIPLE temp[height][width];

    for(int i=0; i<height; i++){
        // p is position of pixel in temporary image
        int p=0;

        for(int j=width-1; j>=0; j--, p++){

            // starting j from the last pixel in the row, we are giving new value to pixel of temp starting from first pixel of row

            temp[i][p]=image[i][j];

        }
    }

    for(int i=0; i<height; i++){

        for(int j=0; j<width; j++){

            // applying reflection to original image

            image[i][j]=temp[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;

    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            // averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}

