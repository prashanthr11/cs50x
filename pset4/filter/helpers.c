#include "helpers.h"
# include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int avg = round((image[i][j].rgbtBlue +  image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
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
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int sr = round(0.393 * r + 0.769 * g + 0.189 * b);
            int sg = round(0.349 * r + 0.686 * g + 0.168 * b);
            int sb = round(0.272 * r + 0.534 * g + 0.131 * b);
            // If the values in the Image Exceeds 255 then set to its maximum value (0xFF)
            if (sb > 255)
            {
                sb = 255;
            }
            if (sg > 255)
            {
                sg = 255;
            }
            if (sr > 255)
            {
                sr = 255;
            }
            image[i][j].rgbtBlue = sb;
            image[i][j].rgbtGreen = sg;
            image[i][j].rgbtRed = sr;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < round(width / 2); ++j)
        {
            RGBTRIPLE temp = image[i][j];   // Temparary Value
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

void Colour_Fill(int sumBlue, int sumGreen, int sumRed, RGBTRIPLE imgcpy)
{
    // printf("as");
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcpy[height][width];    // Temporary image
    for (int i = 1; i <= height - 2; ++i) // Loop all th middle images from (1,1) to (height - 2, width - 2) --> 9 Adjacent Squares
    {
        for (int j = 1; j <= width - 2; ++j)
        {
            int sum1 = 0, sum2 = 0, sum3 = 0;
            for (int k = -1; k <= 1 ; ++k)
            {
                for (int m = -1; m <= 1; ++m)
                {
                    // Assigning the values of the Image to Temporary Image
                    sum1 += image[i + k][j + m].rgbtRed;
                    sum2 += image[i + k][j + m].rgbtBlue;
                    sum3 += image[i + k][j + m].rgbtGreen;
                }
            }
            // Counting & Assigning the Average values of RGB to Temporary Image
            int avg1 = round(sum1 / 9.0);
            int avg2 = round(sum2 / 9.0);
            int avg3 = round(sum3 / 9.0);
            imgcpy[i][j].rgbtBlue = avg2;
            imgcpy[i][j].rgbtGreen = avg3;
            imgcpy[i][j].rgbtRed = avg1;
        }
    }
    for (int i = 0; i < height; ++i)    // Loop through the 4 corners
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0 && j == 0)
            {
                int sumb = image[i][j].rgbtBlue +  image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                int sumg = image[i][j].rgbtGreen +  image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                int sumr = image[i][j].rgbtRed +  image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed;
                Colour_Fill(sumb, sumg, sumr, image[i][j]);
                // int avgb = round(sumb / 4.0);
                // int avgg = round(sumg / 4.0);
                // int avgr = round(sumr / 4.0);
                // imgcpy[i][j].rgbtBlue = avgb;
                // imgcpy[i][j].rgbtGreen = avgg;
                // imgcpy[i][j].rgbtRed = avgr;
            }
            else if (i == 0 && j == width - 1)
            {
                int sumb = image[i][j].rgbtBlue +  image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                int sumg = image[i][j].rgbtGreen +  image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                int sumr = image[i][j].rgbtRed +  image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed;
                // Colour_Fill(sumb, sumg, sumr, &image[i][j]);
                int avgb = round(sumb / 4.0);
                int avgg = round(sumg / 4.0);
                int avgr = round(sumr / 4.0);
                imgcpy[i][j].rgbtBlue = avgb;
                imgcpy[i][j].rgbtGreen = avgg;
                imgcpy[i][j].rgbtRed = avgr;
            }
            else if (i == height - 1 && j == 0)
            {
                int sumb = image[i][j].rgbtBlue +  image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue;
                int sumg = image[i][j].rgbtGreen +  image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen;
                int sumr = image[i][j].rgbtRed +  image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed;
                // Colour_Fill(sumb, sumg, sumr, &image[i][j]);
                int avgb = round(sumb / 4.0);
                int avgg = round(sumg / 4.0);
                int avgr = round(sumr / 4.0);
                imgcpy[i][j].rgbtBlue = avgb;
                imgcpy[i][j].rgbtGreen = avgg;
                imgcpy[i][j].rgbtRed = avgr;
            }
            else if (i == height - 1 && j == width - 1)
            {
                int sumb = image[i][j].rgbtBlue +  image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue;
                int sumg = image[i][j].rgbtGreen +  image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen;
                int sumr = image[i][j].rgbtRed +  image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed;
                // Colour_Fill(sumb, sumg, sumr, &image[i][j]);
                int avgb = round(sumb / 4.0);
                int avgg = round(sumg / 4.0);
                int avgr = round(sumr / 4.0);
                imgcpy[i][j].rgbtBlue = avgb;
                imgcpy[i][j].rgbtGreen = avgg;
                imgcpy[i][j].rgbtRed = avgr;
            }
        }
    }
    for (int i = 0; i < 1; ++i) // Loop for the 0th row, heigth - 1 row, 0th column and width - 1 column
    {
        for (int j = 1; j < width - 1; ++j)
        {
            int sum1 = 0, sum2 = 0, sum3 = 0, avg1 = 0, avg2 = 0, avg3 = 0;
            for (int k = 0; k < 2; k++)
            {
                for (int m = -1; m < 2; m++)
                {
                    int r = image[i + k][j + m].rgbtRed;
                    int b = image[i + k][j + m].rgbtBlue;
                    int g = image[i + k][j + m].rgbtGreen;
                    sum1 += r;
                    sum2 += b;
                    sum3 += g;
                }
            }
            avg1 = round(sum1 / 6.0);
            avg2 = round(sum2 / 6.0);
            avg3 = round(sum3 / 6.0);
            imgcpy[i][j].rgbtBlue = avg2;
            imgcpy[i][j].rgbtGreen = avg3;
            imgcpy[i][j].rgbtRed = avg1;
        }
    }
    for (int i = height - 1; i < height; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            int sum1 = 0, sum2 = 0, sum3 = 0, avg1 = 0, avg2 = 0, avg3 = 0;
            for (int k = -1; k < 1; k++)
            {
                for (int m = -1; m < 2; m++)
                {
                    int r = image[i + k][j + m].rgbtRed;
                    int b = image[i + k][j + m].rgbtBlue;
                    int g = image[i + k][j + m].rgbtGreen;
                    sum1 += r;
                    sum2 += b;
                    sum3 += g;
                }
            }
            avg1 = round(sum1 / 6.0);
            avg2 = round(sum2 / 6.0);
            avg3 = round(sum3 / 6.0);
            imgcpy[i][j].rgbtBlue = avg2;
            imgcpy[i][j].rgbtGreen = avg3;
            imgcpy[i][j].rgbtRed = avg1;
        }
    }
    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            int sum1 = 0, sum2 = 0, sum3 = 0, avg1 = 0, avg2 = 0, avg3 = 0;
            for (int k = -1; k < 2; ++k)
            {
                for (int m = 0; m < 2; ++m)
                {
                    int r = image[i + k][j + m].rgbtRed;
                    int b = image[i + k][j + m].rgbtBlue;
                    int g = image[i + k][j + m].rgbtGreen;
                    sum1 += r;
                    sum2 += b;
                    sum3 += g;
                }
            }
            avg1 = round(sum1 / 6.0);
            avg2 = round(sum2 / 6.0);
            avg3 = round(sum3 / 6.0);
            imgcpy[i][j].rgbtBlue = avg2;
            imgcpy[i][j].rgbtGreen = avg3;
            imgcpy[i][j].rgbtRed = avg1;
        }
    }
    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = width - 1; j < width; ++j)
        {
            int sum1 = 0, sum2 = 0, sum3 = 0, avg1 = 0, avg2 = 0, avg3 = 0;
            for (int k = -1; k < 2; ++k)
            {
                for (int m = -1; m < 1; ++m)
                {
                    int r = image[i + k][j + m].rgbtRed;
                    int b = image[i + k][j + m].rgbtBlue;
                    int g = image[i + k][j + m].rgbtGreen;
                    sum1 += r;
                    sum2 += b;
                    sum3 += g;
                }
            }
            avg1 = round(sum1 / 6.0);
            avg2 = round(sum2 / 6.0);
            avg3 = round(sum3 / 6.0);
            imgcpy[i][j].rgbtBlue = avg2;
            imgcpy[i][j].rgbtGreen = avg3;
            imgcpy[i][j].rgbtRed = avg1;
        }
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Assigning the values of Temporary Image to the Image
            image[i][j].rgbtBlue = imgcpy[i][j].rgbtBlue;
            image[i][j].rgbtRed = imgcpy[i][j].rgbtRed;
            image[i][j].rgbtGreen = imgcpy[i][j].rgbtGreen;
        }
    }
    return;
}
