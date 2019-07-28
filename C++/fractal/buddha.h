#include <iostream>
#include <chrono>
#include <complex.h>
#include <png.hpp>
#include <random>
#include <conio.h>
#include <string>
#include "imageArray.h"
#ifndef BUDDHA_FRACTAL
#define BUDDHA_FRACTAL

using namespace std;

class BuddhaFractal
{
    private:
        const int NO_ITERS;
        const unsigned int NO_POINTS;
        const complex<double> center;
        const double diam_x;
        const double diam_y;
        const int WIDTH;
        const int HEIGHT;

        struct coords
        {
            int x;
            int y;
        };

    public:
        ImageArray::complexPixel** imageArray;
        BuddhaFractal( int iters, unsigned int points, complex<double> center, double diam_x, double diam_y, int width, int height, ImageArray::complexPixel** img);
        coords findCoords(complex<double> c);
        void iteration();
        vector<complex<double>> frac_fun(const complex<double> &c);
        void orbit(complex<double> c);
};
#endif
