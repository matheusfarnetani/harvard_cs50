#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            int average = round((pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3.0);

            pixel->rgbtBlue = average;
            pixel->rgbtGreen = average;
            pixel->rgbtRed = average;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half = width / 2; j < half; j++)
        {
            RGBTRIPLE *leftPixel = &image[i][j];
            RGBTRIPLE *rightPixel = &image[i][width - 1 - j];

            RGBTRIPLE tmp = *leftPixel;
            *leftPixel = *rightPixel;
            *rightPixel = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int counter = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int newRow = i + k;
                    int newCol = j + l;
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        redSum += original[newRow][newCol].rgbtRed;
                        greenSum += original[newRow][newCol].rgbtGreen;
                        blueSum += original[newRow][newCol].rgbtBlue;
                        counter++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float) redSum / counter);
            image[i][j].rgbtGreen = round((float) greenSum / counter);
            image[i][j].rgbtBlue = round((float) blueSum / counter);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image to work with
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    // Create Gx matrix
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // Create Gy matrix
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Start iterating over each pixel of image and perfoming operations
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel[3][3];

            // Store pixel box inside of pixel two dimensional array
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    //Indices for original image
                    int newRow = i + k;
                    int newCol = j + l;

                    // Indice for pixel box
                    int xPixel = k + 1;
                    int yPixel = l + 1;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        pixel[xPixel][yPixel] = original[newRow][newCol];
                    }
                    else
                    {
                        pixel[xPixel][yPixel].rgbtBlue = 0;
                        pixel[xPixel][yPixel].rgbtGreen = 0;
                        pixel[xPixel][yPixel].rgbtRed = 0;
                    }
                }
            }

            int gxRedSum = 0;
            int gxGreenSum = 0;
            int gxBlueSum = 0;

            int gyRedSum = 0;
            int gyGreenSum = 0;
            int gyBlueSum = 0;

            // Start Operations
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    gxRedSum += pixel[k][l].rgbtRed * gx[k][l];
                    gxGreenSum += pixel[k][l].rgbtGreen * gx[k][l];
                    gxBlueSum += pixel[k][l].rgbtBlue * gx[k][l];

                    gyRedSum += pixel[k][l].rgbtRed * gy[k][l];
                    gyGreenSum += pixel[k][l].rgbtGreen * gy[k][l];
                    gyBlueSum += pixel[k][l].rgbtBlue * gy[k][l];
                }
            }

            int redResult = round((float) sqrt(pow(gxRedSum, 2) + pow(gyRedSum, 2)));
            int greenResult = round((float) sqrt(pow(gxGreenSum, 2) + pow(gyGreenSum, 2)));
            int blueResult = round((float) sqrt(pow(gxBlueSum, 2) + pow(gyBlueSum, 2)));

            image[i][j].rgbtRed = (redResult > 255) ? 255 : ((redResult < 0) ? 0 : redResult);
            image[i][j].rgbtGreen = (greenResult > 255) ? 255 : ((greenResult < 0) ? 0 : greenResult);
            image[i][j].rgbtBlue = (blueResult > 255) ? 255 : ((blueResult < 0) ? 0 : blueResult);
        }
    }
}
