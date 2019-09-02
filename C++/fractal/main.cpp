#include <iostream>
#include <chrono>
#include <complex.h>
#include <png.hpp>
#include <random>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

#include "imageArray.h"
#include "fractal.h"
#include "buddha.h"


int main()
{
    auto start = chrono::steady_clock::now();

    //parameters
    int iters = 200;
    int min_iters = 0;
    complex<double> center(-0.4,0);
    double diam_x = 2.1;
    double diam_y = 2.1;
    int image_width = 500;
    int image_height = 500;
    int threads_to_use = 4;
    unsigned int points =image_width*image_height*100; //changes noise profile

    //image creation, fractal creation, and array deletion.
    ImageArray img(image_width,image_height);
   /** for(int i=0;i<100;i++)  //Animation via making many subframes
    {
        BuddhaFractal a(min_iters+(i*50),iters+(i*50),points,center,diam_x,diam_y,image_width,image_height, img.pixelMatrix);
        img.draw("animation_"+to_string(time(0))+"/Buddha_"+to_string(min_iters)+"_"+to_string(iters)+"_"+to_string(points)+"_"+to_string(diam_y)+"_"+to_string(diam_x));
        img.clearArray();
    }**/

    BuddhaFractal a(min_iters,iters,points,center,diam_x,diam_y,image_width,image_height, img.pixelMatrix,threads_to_use);

    img.draw("Buddha_"+to_string(min_iters)+"_"+to_string(iters)+"_"+to_string(points)+"_"+to_string(diam_y)+"_"+to_string(diam_x));
    img.clearArray();
    img.deleteArray();

    auto end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::seconds>(end - start).count()<< " (s)"<<endl;
    getch();

    return 0;
}
