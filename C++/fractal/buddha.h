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
#include <thread>

using namespace std;

class BuddhaFractal
{
    private:
        const int MIN_ITERS;
        const int MAX_ITERS;
        const unsigned int NO_POINTS;
        const complex<double> center;
        const double diam_x;
        const double diam_y;
        const int WIDTH;
        const int HEIGHT;
        const int THREAD_COUNT;
        struct coords
        {
            int x;
            int y;
        };

    public:
        ImageArray::complexPixel** imageArray;
        BuddhaFractal( int min_iters, int max_iters, unsigned int points, complex<double> center, double diam_x, double diam_y, int width, int height, ImageArray::complexPixel** img, int thread_count);
        coords findCoords(complex<double> c);
        void iteration();
        vector<complex<double>> frac_fun(const complex<double> &c);
        void orbit(complex<double> c);
        void threadIter(int thread_i);
};
#endif
