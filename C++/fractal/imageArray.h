#include <png.hpp>
#include <string>
#include <ctime>
#include<cmath>
#ifndef IMAGE_ARRAY
#define IMAGE_ARRAY

class ImageArray //A class that handles a 2D array of ints.
{
    private:
        const int WIDTH;
        const int HEIGHT;
        const int MAX_VAL = 65536;
        int *histogram;

        void updateHistogram();
        void equaliseHistogram();
        void normalise();
        void logPixel();
        void clipTop();
        int findMax();
    public:
        struct complexPixel //incase we want to add extra info for each point
        {
            short iters;
        };
        complexPixel **pixelMatrix;
        ImageArray(int width, int height);
        void clearArray();
        void deleteArray();
        void draw(std::string filename);
};
#endif
