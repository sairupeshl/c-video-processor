#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store the original values in temporary variables
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int originalRed = image[i][j].rgbtRed;

            // Create variables to store sepia values
            float sepiaRed = 0.0;
            float sepiaBlue = 0.0;
            float sepiaGreen = 0.0;

            // Compute sepia values, Update pixel with sepia values
            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            // Round off
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            // If result is above 255, make it 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Change the image's pixel values to the sepia ones
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over the left half of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Calculate the new value for each pixel in the image using the copy

    // Loop over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Count the number of surounding grids within image
            int cnt = 0;

            // Create temporary variables to store the new pixel values
            float redtemp = 0.0;
            float bluetemp = 0.0;
            float greentemp = 0.0;

            // Loop over the surrounding 3*3 grid and add all the values
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((-1 < (i + k)) && ((i + k) < height) && (-1 < (j + l)) && ((j + l) < width))
                    {
                        redtemp += copy[i + k][j + l].rgbtRed;
                        bluetemp += copy[i + k][j + l].rgbtBlue;
                        greentemp += copy[i + k][j + l].rgbtGreen;
                        cnt += 1;
                    }
                }
            }

            // Calculate the average
            redtemp /= (float) cnt;
            bluetemp /= (float) cnt;
            greentemp /= (float) cnt;

            // Round off the values
            redtemp = round(redtemp);
            bluetemp = round(bluetemp);
            greentemp = round(greentemp);

            // Change the image pixel values to the new ones
            image[i][j].rgbtRed = redtemp;
            image[i][j].rgbtBlue = bluetemp;
            image[i][j].rgbtGreen = greentemp;
        }
    }
    return;
}

// Edge Detection
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Define the Sobel Kernels
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Calculate the new value for each pixel in the image using the copy

    // Loop over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize accumulators for Red, Green, Blue
            float Gx_red = 0, Gx_green = 0, Gx_blue = 0;
            float Gy_red = 0, Gy_green = 0, Gy_blue = 0;

            // Loop over the surrounding 3*3 grid
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((-1 < (i + k)) && ((i + k) < height) && (-1 < (j + l)) && ((j + l) < width))
                    {
                        Gx_red   += copy[i + k][j + l].rgbtRed   * Gx[k + 1][l + 1];
                        Gx_green += copy[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        Gx_blue  += copy[i + k][j + l].rgbtBlue  * Gx[k + 1][l + 1];

                        Gy_red   += copy[i + k][j + l].rgbtRed   * Gy[k + 1][l + 1];
                        Gy_green += copy[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                        Gy_blue  += copy[i + k][j + l].rgbtBlue  * Gy[k + 1][l + 1];
                    }
                }
            }

            // Calculate the new values and round off
            int redtemp   = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int greentemp = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int bluetemp  = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap values at 255

            // Change the image pixel values to the new ones
            image[i][j].rgbtRed   = (redtemp > 255) ? 255 : redtemp;
            image[i][j].rgbtGreen = (greentemp > 255) ? 255 : greentemp;
            image[i][j].rgbtBlue  = (bluetemp > 255) ? 255 : bluetemp;
        }
    }
    return;
}