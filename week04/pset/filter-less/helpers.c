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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            // Save original value
            int originalRed = pixel->rgbtRed;
            int originalGreen = pixel->rgbtGreen;
            int originalBlue = pixel->rgbtBlue;

            // Calculate sepia value
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Apply sepiaRed into image
            if (sepiaRed > 255)
            {
                pixel->rgbtRed = 255;
            }
            else if (sepiaRed < 0)
            {
                pixel->rgbtRed = 0;
            }
            else
            {
                pixel->rgbtRed = sepiaRed;
            }

            // Apply sepiaGreen into image
            if (sepiaGreen > 255)
            {
                pixel->rgbtGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                pixel->rgbtGreen = 0;
            }
            else
            {
                pixel->rgbtGreen = sepiaGreen;
            }

            // Apply sepiaBlue into image
            if (sepiaBlue > 255)
            {
                pixel->rgbtBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                pixel->rgbtBlue = 0;
            }
            else
            {
                pixel->rgbtBlue = sepiaBlue;
            }
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
