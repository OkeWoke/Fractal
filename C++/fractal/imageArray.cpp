#include "imageArray.h"

ImageArray::ImageArray(int width, int height):WIDTH(width),HEIGHT(height)
{
    histogram = new int[MAX_VAL];
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
    delete [] histogram;
}

void ImageArray::updateHistogram()
{//deletes prior histogram, creates new one, no fixed size.
    int max_pixel_val = findMax();
    delete [] histogram;
    histogram = new int[max_pixel_val+1];

    for(int i=0;i<max_pixel_val;i++){//clearing and init vals
        histogram[i] = 0;
    }
     for (int y = 0; y < HEIGHT; y++)// construct histogram
    {
        for (int x = 0; x < WIDTH; x++)
        {
            histogram[pixelMatrix[x][y].iters]++;
        }
    }
}

void ImageArray::equaliseHistogram()
{
    //Creating cumulative histogram
    updateHistogram();
    int MAX_VAL = sizeof(histogram)-1;//override global, lazy
    int cumulative[MAX_VAL];
    cumulative[0] = histogram[0];
    for(int i=1;i<MAX_VAL;i++){
        cumulative[i] = cumulative[i-1]+histogram[i];
    }

    //constructing LUT
    int q_min = 0;
    for(int i=0;i<MAX_VAL;i++)
    {
        if (cumulative[i]>0)
        {
            q_min = i;
            break;
        }
    }

    int LUT[MAX_VAL];
    for(int i=0;i<MAX_VAL;i++)
    {
        if (i<q_min)
        {
            LUT[i] = 0;
        }else
        {
            LUT[i] = MAX_VAL * (cumulative[i]-cumulative[q_min])/(cumulative[MAX_VAL] - cumulative[q_min]);
        }
    }

    //applying LUT to image
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            pixelMatrix[x][y].iters = LUT[pixelMatrix[x][y].iters];
        }
    }
}

void ImageArray::clipTop()
{
    for (int y = 0; y < HEIGHT; y++)//find max value in the image array
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int iters = pixelMatrix[x][y].iters;
            if (iters > MAX_VAL)
            {
                pixelMatrix[x][y].iters = MAX_VAL;
            }
        }
    }
}
int ImageArray::findMax()
{
    int max_pixel_val = 0;
    for (int y = 0; y < HEIGHT; y++)//find max value in the image array
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
    return max_pixel_val;
}

void ImageArray::normalise()
{   //this function will scale all pixel values between 0 and max_val, loss of information/quality occurs.
    int max_pixel_val = findMax();

    for (int y = 0; y < HEIGHT; ++y)//normalising the value
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            int iters = pixelMatrix[x][y].iters;
            pixelMatrix[x][y].iters = (int)((MAX_VAL*(double)iters)/max_pixel_val);
        }
    }
}

void ImageArray::logPixel()
{
    for (int y = 0; y < HEIGHT; ++y)//normalising the value
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            short iters = pixelMatrix[x][y].iters;
            if(iters > 0)
            {
                pixelMatrix[x][y].iters= log(iters);
            }else
            {
                pixelMatrix[x][y].iters= 0;
            }


        }
    }
}
void ImageArray::draw( std::string filename)
{
    //equaliseHistogram();
    //logPixel();
    //normalise();
    clipTop();
    //png::gray_pixel_16 for future implementation
    png::image< png::gray_pixel_16 > image(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            int gray = pixelMatrix[x][y].iters;
            image[y][x] = png::gray_pixel_16(gray);
        }
    }

    image.write("renders/"+filename+"_"+std::to_string(HEIGHT)+"x"+std::to_string(WIDTH)+"_"+std::to_string(time(0))+".png");
}
