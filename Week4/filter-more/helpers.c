#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            RGBTRIPLE pixel = image[i][j];
            float red = pixel.rgbtRed;
            BYTE mean = round((float)(pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue)/3);
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtBlue = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i*2 < width; i++){
        for(int j = 0; j < height; j++){
            RGBTRIPLE one = image[j][i];
            RGBTRIPLE two = image[j][width-i-1];
            image[j][i] = two;
            image[j][width-i-1] = one;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    //copying image
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            copy_image[i][j] = image[i][j];
        }
    }

    //applying blur effect to original image
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int red, green, blue, count;
            red = green = blue = count = 0;

            // working with surrounding pixels
            for(int a = -1; a < 2; a++){
                if(i+a < 0 || i+a > height-1) continue;
                else{
                    for(int b = -1; b < 2; b++){
                        if(j+b < 0 || j+b > width-1) continue;
                        else{
                            red += copy_image[i+a][j+b].rgbtRed;
                            green += copy_image[i+a][j+b].rgbtGreen;
                            blue += copy_image[i+a][j+b].rgbtBlue;
                            count++;
                        }
                    }
                }
           }
            image[i][j].rgbtRed = round((float)(red)/count);
            image[i][j].rgbtGreen = round((float)(green)/count);
            image[i][j].rgbtBlue = round((float)(blue)/count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    int Gy[3][3] = {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

    RGBTRIPLE copy_image[height][width];

    // copy image
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            copy_image[i][j] = image[i][j];
        }
    }
    int max = 0;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            float redx, greenx, bluex, redy, greeny, bluey;
            redx = greenx = bluex = redy = greeny = bluey = 0;
            for(int a = -1; a < 2; a++){
                if(i+a < 0 || i+a > height-1) continue;
                else{
                    for(int b = -1; b < 2; b++){
                        if(j+b < 0 || j+b > width-1) continue;
                        else{
                            redx += Gx[a+1][b+1] * copy_image[i+a][j+b].rgbtRed;
                            greenx += Gx[a+1][b+1] * copy_image[i+a][j+b].rgbtGreen;
                            bluex += Gx[a+1][b+1] * copy_image[i+a][j+b].rgbtBlue;
                            redy += Gy[a+1][b+1] * copy_image[i+a][j+b].rgbtRed;
                            greeny += Gy[a+1][b+1] * copy_image[i+a][j+b].rgbtGreen;
                            bluey += Gy[a+1][b+1] * copy_image[i+a][j+b].rgbtBlue;
                        }
                    }
                }
            }
            image[i][j].rgbtRed = round(sqrt(pow(redx,2) + pow(redy,2))) > 255 ? 255 : round(sqrt(pow(redx,2) + pow(redy,2)));
            image[i][j].rgbtGreen = round(sqrt(pow(greenx,2) + pow(greeny,2))) > 255 ? 255 : round(sqrt(pow(greenx,2) + pow(greeny,2)));
            image[i][j].rgbtBlue = round(sqrt(pow(bluex,2) + pow(bluey,2))) > 255 ? 255 : round(sqrt(pow(bluex,2) + pow(bluey,2)));
            //if (max < sqrt((int)pow(bluex,2) + (int)pow(bluey,2))) max = sqrt((int)pow(bluex,2) + (int)pow(bluey,2));
        }
    }
    //printf("%i\n",max);
    return;
}
