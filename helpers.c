#include "helpers.h"
#include <math.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For every row of image image[row_number < height]:
    //For every pixel in row image[row_number < height][column_number < width]:
    //Take value of red
    //Take value of green
    //Take value of blue
    //Average = round(value(red+green+blue) / 3)
    //New value of red = average
    //New value of green = average
    //New value of blue = average

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    * Sepia algorithm:
    * sepia_red = 0.393 * original_red + 0.769 * original_green + 0.189 * original_blue
    * sepia_green = 0.349 * original_red + 0.686 * original_green + 0.168 * original_blue
    * sepia_blue = 0.272 * original_red + 0.534 * original_green + 0.131 * original_blue
    * If new value > 255, than new value = 255
    */

    // For every row of image image[row_number < height]:
    // For every pixel in row image[row_number < height][column_number < width]:

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia_blue = round(0.272 * (float)image[i][j].rgbtRed + 0.534 * (float)image[i][j].rgbtGreen + 0.131 *
                                   (float)image[i][j].rgbtBlue);
            int sepia_green = round(0.349 * (float)image[i][j].rgbtRed + 0.686 * (float)image[i][j].rgbtGreen + 0.168 *
                                    (float)image[i][j].rgbtBlue);
            int sepia_red = round(0.393 * (float)image[i][j].rgbtRed + 0.769 * (float)image[i][j].rgbtGreen + 0.189 *
                                  (float)image[i][j].rgbtBlue);

            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }

            image[i][j].rgbtBlue = sepia_blue;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtRed = sepia_red;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Create new temporary array
    RGBTRIPLE temporary[height][width];
    // Copy input image to new array
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            temporary[k][l] = image[k][l];
        }
    }

    //Reflect image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temporary[i][width - 1 - j];
        }
    }
    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create new temporary array
    RGBTRIPLE temporary[height][width];

    // Copy input image to new array
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            temporary[k][l] = image[k][l];
        }
    }

    int counter;
    float sum_of_blue;
    float sum_of_green;
    float sum_of_red;
    int new_blue;
    int new_green;
    int new_red;

    // Check every row
    for (int i = 0; i < height; i++)
    {
        // Check every pixel
        for (int j = 0; j < width; j++)
        {
            // Set counter and particular sums to 0 for every new calculation
            counter = 0;
            sum_of_blue = 0;
            sum_of_green = 0;
            sum_of_red = 0;

            if ((i - 1 >= 0) && (j - 1 >= 0))
            {
                sum_of_blue += temporary[i - 1][j - 1].rgbtBlue;
                sum_of_green += temporary[i - 1][j - 1].rgbtGreen;
                sum_of_red += temporary[i - 1][j - 1].rgbtRed;
                counter++;
            }

            if ((i - 1 >= 0) && (j >= 0))
            {
                sum_of_blue += temporary[i - 1][j].rgbtBlue;
                sum_of_green += temporary[i - 1][j].rgbtGreen;
                sum_of_red += temporary[i - 1][j].rgbtRed;
                counter++;
            }

            if ((i - 1 >= 0) && (j + 1 >= 0) && (j + 1 < width))
            {
                sum_of_blue += temporary[i - 1][j + 1].rgbtBlue;
                sum_of_green += temporary[i - 1][j + 1].rgbtGreen;
                sum_of_red += temporary[i - 1][j + 1].rgbtRed;
                counter++;
            }

            if ((i >= 0) && (j - 1 >= 0))
            {
                sum_of_blue += temporary[i][j - 1].rgbtBlue;
                sum_of_green += temporary[i][j - 1].rgbtGreen;
                sum_of_red += temporary[i][j - 1].rgbtRed;
                counter++;
            }

            if ((i >= 0) && (j >= 0))
            {
                sum_of_blue += temporary[i][j].rgbtBlue;
                sum_of_green += temporary[i][j].rgbtGreen;
                sum_of_red += temporary[i][j].rgbtRed;
                counter++;
            }

            if ((i >= 0) && (j + 1 >= 0) && (j + 1 < width))
            {
                sum_of_blue += temporary[i][j + 1].rgbtBlue;
                sum_of_green += temporary[i][j + 1].rgbtGreen;
                sum_of_red += temporary[i][j + 1].rgbtRed;
                counter++;
            }

            if ((i + 1 >= 0) && (j - 1 >= 0) && (i + 1 < height))
            {
                sum_of_blue += temporary[i + 1][j - 1].rgbtBlue;
                sum_of_green += temporary[i + 1][j - 1].rgbtGreen;
                sum_of_red += temporary[i + 1][j - 1].rgbtRed;
                counter++;
            }

            if ((i + 1 >= 0) && (j >= 0) && (i + 1 < height))
            {
                sum_of_blue += temporary[i + 1][j].rgbtBlue;
                sum_of_green += temporary[i + 1][j].rgbtGreen;
                sum_of_red += temporary[i + 1][j].rgbtRed;
                counter++;
            }

            if ((i + 1 >= 0) && (j + 1 >= 0) && (i + 1 < height) && (j + 1 < width))
            {
                sum_of_blue += temporary[i + 1][j + 1].rgbtBlue;
                sum_of_green += temporary[i + 1][j + 1].rgbtGreen;
                sum_of_red += temporary[i + 1][j + 1].rgbtRed;
                counter++;
            }

            new_blue = round((float)sum_of_blue / counter);
            new_green = round((float)sum_of_green / counter);
            new_red = round((float)sum_of_red / counter);

            image[i][j].rgbtBlue = new_blue;
            image[i][j].rgbtGreen = new_green;
            image[i][j].rgbtRed = new_red;

        }
    }

    return;
}