#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // map each pixel and turn it color the average of RGB
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double average = ((double) image[h][w].rgbtBlue + (double) image[h][w].rgbtGreen + (double) image[h][w].rgbtRed) / 3;
            image[h][w].rgbtBlue = (BYTE) round(average);
            image[h][w].rgbtGreen = (BYTE) round(average);
            image[h][w].rgbtRed = (BYTE) round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // map each pixel and reflect it horizontally
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width / 2); w++)
        {
            // inverting width pixel
            int wNew = width - 1 - w;
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][wNew];
            image[h][wNew] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a temporary image to map pixels
    RGBTRIPLE tmpImg[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            tmpImg[h][w] = image[h][w];
        }
    }

    // map each pixel and get colors average
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blueSum = 0;
            int greenSum = 0;
            int redSum = 0;

            int counter = 0;

            // map neighbour pixels
            for (int hTmp = h - 1; hTmp <= h + 1; hTmp++)
            {
                for (int wTmp = w - 1; wTmp <= w + 1; wTmp++)
                {
                    // handle borders and corners pixels
                    if (hTmp >= 0 && hTmp < height && wTmp >= 0 && wTmp < width)
                    {
                        blueSum += tmpImg[hTmp][wTmp].rgbtBlue;
                        greenSum += tmpImg[hTmp][wTmp].rgbtGreen;
                        redSum += tmpImg[hTmp][wTmp].rgbtRed;
                        counter++;
                    }
                }
            }

            // getting average for each color of the pixel
            image[h][w].rgbtBlue = (BYTE) round((double) blueSum / (double) counter);
            image[h][w].rgbtGreen = (BYTE) round((double) greenSum / (double) counter);
            image[h][w].rgbtRed = (BYTE) round((double) redSum / (double) counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // creating kernels (Gx and Gy) array
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // creating a temporary image to map pixels
    RGBTRIPLE tmpImg[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            tmpImg[h][w] = image[h][w];
        }
    }

    // map each pixel and apply sobel operator
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // creating variables for each color, to calculate Gx and Gy
            int blueGx = 0;
            int blueGy = 0;

            int greenGx = 0;
            int greenGy = 0;

            int redGx = 0;
            int redGy = 0;


            // map 3x3 neighbour pixels
            for (int hTmp = h - 1, i = 0; hTmp <= h + 1; hTmp++, i++)
            {
                for (int wTmp = w - 1, j = 0; wTmp <= w + 1; wTmp++, j++)
                {
                    // handle borders and corners pixels
                    if (hTmp >= 0 && hTmp < height && wTmp >= 0 && wTmp < width)
                    {
                        // Gx
                        blueGx += (int) tmpImg[hTmp][wTmp].rgbtBlue * gx[i][j];
                        greenGx += (int) tmpImg[hTmp][wTmp].rgbtGreen * gx[i][j];
                        redGx += (int) tmpImg[hTmp][wTmp].rgbtRed * gx[i][j];

                        // Gy
                        blueGy += (int) tmpImg[hTmp][wTmp].rgbtBlue * gy[i][j];
                        greenGy += (int) tmpImg[hTmp][wTmp].rgbtGreen * gy[i][j];
                        redGy += (int) tmpImg[hTmp][wTmp].rgbtRed * gy[i][j];
                    }
                    else
                    {
                        blueGx += 0;
                        blueGy += 0;

                        greenGx += 0;
                        greenGy += 0;

                        redGx += 0;
                        redGy += 0;
                    }
                }
            }

            // calculating sobel operator for each color
            double sobelBlue = sqrt(pow((double) blueGx, 2) + pow((double) blueGy, 2));
            double sobelGreen = sqrt(pow((double) greenGx, 2) + pow((double) greenGy, 2));
            double sobelRed = sqrt(pow((double) redGx, 2) + pow((double) redGy, 2));

            // handling numbers greater than 255
            if (sobelBlue > 255)
            {
                sobelBlue = 255;
            }

            if (sobelGreen > 255)
            {
                sobelGreen = 255;
            }

            if (sobelRed > 255)
            {
                sobelRed = 255;
            }

            // applying sobel operator value to the pixel
            image[h][w].rgbtBlue = (BYTE) round(sobelBlue);
            image[h][w].rgbtGreen = (BYTE) round(sobelGreen);
            image[h][w].rgbtRed = (BYTE) round(sobelRed);
        }
    }
    return;
}
