#include <iostream>
#include <chrono>
#include <complex.h>
#include <png.hpp>
#include <random>
#include <conio.h>
#include <string>
#include "imageArray.h"

#ifndef MANDLE_FRACTAL
#define MANDLE_FRACTAL
using namespace std;
class Fractal{
     private:
        const int NO_ITERS;
        const complex<double> center;
        const double diam_x;
        const double diam_y;
        const int WIDTH;
        const int HEIGHT;

    public:
        ImageArray::complexPixel** imageArray;
        Fractal(int iters, complex<double> center, double diam_x, double diam_y, int width, int height, ImageArray::complexPixel** img);
        void iteration();
        ImageArray::complexPixel fun(const complex<double>& c);
};
#endif
