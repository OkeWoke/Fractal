#include <string>
#include <ctime>
#include<cmath>
#ifndef IMAGE_ARRAY
#define IMAGE_ARRAY

class ImageArray //A class that handles a 2D array of ints.
{
    private:
        const int MAX_VAL = 65536;
        unsigned int *histogram;
        void updateHistogram();
        unsigned short findMax();

    public:
        const int WIDTH;
        const int HEIGHT;

        struct complexPixel //incase we want to add extra info for each point
        {
            unsigned short iters;
        };

        complexPixel **pixelMatrix;
        ImageArray(int width, int height);
        void clearArray();
        void deleteArray();
        void equaliseHistogram();
        void normalise();
        void logPixel();
        void clipTop();
};
#endif
