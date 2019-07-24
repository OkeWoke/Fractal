#include <iostream>
#include <chrono>
#include <complex.h>
#include <png.hpp>

using namespace std;

class fractal{
    private:
        int NO_ITERS;
        int WIDTH;
        int HEIGHT;
        double diam_x;
        double diam_y;
        complex<double> center;

        struct complexPixel{
            //int x;
            //int y;
            short iters;
            //complex<double> cPoint;
        };

    public:
        fractal(int iters, complex<double> center, double diam_x, double diam_y, int width, int height){
            this->diam_x = diam_x;
            this->diam_y = diam_y;
            this->center = center;
            this->WIDTH = width;
            this->HEIGHT = height;
            this->NO_ITERS = iters;
            draw(iteration());
        }

    complexPixel** iteration()
    {
        complexPixel **pixelMatrix;
        pixelMatrix = new complexPixel*[WIDTH];
        for(int i=0;i<WIDTH;i++){
            pixelMatrix[i] = new complexPixel[HEIGHT];
        }

        double yInc = diam_y/HEIGHT;
        double xInc = diam_x/WIDTH;

        complex<double> c = complex<double>(-diam_x/2,diam_y/2);
        c+=center;//view shift
        for(int y= 0;y<HEIGHT;y++){

            c.real(-diam_x/2);
            c.real(center.real() + c.real());
            for(int x=0; x<WIDTH;x++){
                complexPixel f = fun(c);
                //f.x = x;
                //f.y =y;
                //f.cPoint = c;
                pixelMatrix[x][y] = f;

                //pixelList.push_back(f);
                c.real(c.real()+xInc);
            }
            c.imag(c.imag()-yInc);
        }

        return pixelMatrix;
    }

    private:
        complexPixel fun(complex<double>& c){
            complex<double> z(0,0);
            complexPixel cP;
            //cP.cPoint = z;//is this a copy or a reference?
            for(int i=0;i<NO_ITERS; ++i){
                double zRsq = real(z)*real(z);
                double zIsq = imag(z)*imag(z);

                z.imag((real(z)*imag(z)));
                z.imag(z.imag()+z.imag());
                z.real(zRsq-zIsq);
                z+=c;

                if (zRsq+zIsq > 4){
                    cP.iters = i;
                    return cP;
                }
            }
            cP.iters = NO_ITERS;
            return cP;
        }

        void draw(complexPixel** pixelList){

            png::image< png::rgb_pixel > image(WIDTH, HEIGHT);
            for (int y = 0; y < HEIGHT; y++)
            {
                for (int x = 0; x < WIDTH; x++)
                {
                    int iters = pixelList[x][y].iters;
                    if(iters==NO_ITERS){
                        image[y][x] = png::rgb_pixel(0,0,(int)(iters*(float) 255/ NO_ITERS));
                    }else{
                        image[y][x] = png::rgb_pixel((int)( 0- ((float)iters/NO_ITERS)*-1*255),(int)(255/(pow(1.001,iters))),0);
                    }
                }
            }
            image.write("Fractal.png");

            for(int i=0;i<WIDTH;i++){
                delete [] pixelList[i];
            }
            delete [] pixelList;
        }
};

int main()
{
    auto start = chrono::steady_clock::now();

    int iters = 500;
    complex<double> center(-1.7798310726,0.0000768808);
    double diam_x = 0.0002;
    double diam_y = 0.0002;
    int image_height = 1000;
    int image_width = 1000;
    fractal f(iters,center,diam_x,diam_y,image_width,image_height);

    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::seconds>(end - start).count()<< " (s)";

    return 0;
}
