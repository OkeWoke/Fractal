#include <iostream>
#include <chrono>
#include <complex.h>
#include <png.hpp>
#include <random>
#include <conio.h>
#include <string>
#include <windows.h>

using namespace std;

#include "imageArray.h"
#include "fractal.h"
#include "buddha.h"


int main()
{
    SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
    auto start = chrono::steady_clock::now();

    int iters = 500;

    complex<double> center(-0.4,0);
    double diam_x = 2;
    double diam_y = 2;
    int image_height = 1000;
    int image_width = 1000;
    unsigned int points =image_width*image_height*10;

    //
    ImageArray img(image_width,image_height);
    BuddhaFractal a(iters,points,center,diam_x,diam_y,image_width,image_height, img.pixelMatrix);
    img.draw("Test");
    img.clearArray();
    Fractal f(iters,center,diam_x,diam_y,image_width,image_height,img.pixelMatrix);
    img.draw("Test2");

    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::seconds>(end - start).count()<< " (s)"<<endl;
    getch();
    return 0;
}
