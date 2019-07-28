#include "imageArray.h"

ImageArray::ImageArray(int width, int height):WIDTH(width),HEIGHT(height)
{
    pixelMatrix = new complexPixel*[WIDTH];

    for(int i=0;i<WIDTH;i++)
    {
        pixelMatrix[i] = new complexPixel[HEIGHT];
    }
    for(int y= 0;y<HEIGHT;y++)//instantiating iters in each pixel
    {
        for(int x=0; x<WIDTH;x++)
        {
            complexPixel a;
            a.iters=0;
            pixelMatrix[x][y] =a;
        }
    }
}

void ImageArray::clearArray()//resets array to 0
{
    for(int y= 0;y<HEIGHT;y++)
    {
        for(int x=0; x<WIDTH;x++)
        {
            pixelMatrix[x][y].iters = 0;
        }
    }
}

void ImageArray::deleteArray()
{
    for(int i=0;i<WIDTH;i++)
    {
        delete [] pixelMatrix[i];
    }
    delete [] pixelMatrix;
}

void ImageArray::draw( std::string filename)
{
    png::image< png::rgb_pixel > image(WIDTH, HEIGHT);
    int max_pixel_val = 0;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int iters = pixelMatrix[x][y].iters;
            if (iters > max_pixel_val)
            {
                max_pixel_val = iters;
            }
        }
    }

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            int iters = pixelMatrix[x][y].iters;
            int gray = (int)((255*(double)iters)/max_pixel_val);
            image[y][x] = png::rgb_pixel(gray,gray,gray);
        }
    }

    image.write("renders/"+filename+"_"+std::to_string(HEIGHT)+"x"+std::to_string(WIDTH)+".png");
}
