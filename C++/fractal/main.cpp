#include <iostream>
#include <chrono>
#include <complex.h>
#include <png.hpp>
#include <random>
#include <conio.h>
#include <string>
//#include <ctime>
using namespace std;

class fractal{
    private:
        int NO_ITERS;
        int WIDTH;
        int HEIGHT;
        double diam_x;
        double diam_y;
        complex<double> center;

    protected:
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

    protected:
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

class buddhaFractal{
    private:
        int NO_ITERS;
        int WIDTH;
        int HEIGHT;
        int NO_POINTS;
        double diam_x;
        double diam_y;
        complex<double> center;
        struct complexPixel{
            //int x;
            //int y;
            short iters;
            //complex<double> cPoint;
        };

        struct coords {
            int x;
            int y;
        };

    public:
        buddhaFractal(int iters, int points, complex<double> center, double diam_x, double diam_y, int width, int height){

            this->diam_x = diam_x;
            this->diam_y = diam_y;
            this->center = center;
            this->WIDTH = width;
            this->HEIGHT = height;
            this->NO_ITERS = iters;
            this->NO_POINTS = points;
            cout<<"doing this thing";
            draw(iteration());
        }

    private:
        coords findCoords(complex<double> c)
        {
            //-1, -1 if out of image bounds
            complex<double> topLeft(-diam_x/2,diam_y/2);
            complex<double> bottomRight(diam_x/2,-diam_y/2);
            topLeft+=center;
            bottomRight+=center;
            coords bounds;

            if(c.real() < topLeft.real() || c.imag()> topLeft.imag() || c.real() > bottomRight.real() || c.imag() < bottomRight.imag()){

                bounds.x= -1;
                bounds.y = -1;
                return bounds;
            }

            double yInc = diam_y/HEIGHT;
            double xInc = diam_x/WIDTH;
            bounds.x = (center.real()+(diam_x/2)-c.real())/xInc;
            bounds.y = (center.imag()+(diam_y/2)-c.imag())/yInc;

            return bounds;
        }

        complexPixel** iteration()
        {
            //init pixel matrix
            complexPixel **pixelMatrix;
            pixelMatrix = new complexPixel*[WIDTH];

            for(int i=0;i<WIDTH;i++){
                pixelMatrix[i] = new complexPixel[HEIGHT];
            }

            for(int y= 0;y<HEIGHT;y++){//instantiating iters in each pixel
                for(int x=0; x<WIDTH;x++){
                    complexPixel a;
                    a.iters=0;
                    pixelMatrix[x][y] =a;
                }
            }

            //generate random complex num, trace orbit and mark the pixel matrix
            mt19937 rng;
            uniform_real_distribution<double> unif(center.real()-diam_x/2,center.real()+diam_x/2);
            uniform_real_distribution<double> unif_imag(center.imag()-diam_y/2,center.imag()+diam_y/2);

            rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());

            for(int i=0;i<NO_POINTS;i++){
                complex<double> sample(unif(rng),unif_imag(rng));
                orbit(pixelMatrix,sample);
            }

            return pixelMatrix;
        }

        vector<complex<double>> frac_fun(complex<double> c){
            complex<double> z(0,0);
            vector<complex<double>> orbit_trace;
            orbit_trace.reserve(NO_ITERS);//reserve memory in advance

            for(int i=0;i<NO_ITERS; ++i){
                double zRsq = real(z)*real(z);
                double zIsq = imag(z)*imag(z);

                z.imag((real(z)*imag(z)));
                z.imag(z.imag()+z.imag());
                z.real(zRsq-zIsq);
                z+=c;
                //z = z*z + c;
                orbit_trace.push_back(z);
                if (zRsq+zIsq > 4){
                    return orbit_trace;
                }
            }
            //return orbit_trace;
            return vector<complex<double>>();
        }

        void orbit(complexPixel** imgArray, complex<double> c){
            vector<complex<double>> orbit_trace = frac_fun(c);
            vector<complex<double>>::iterator end = orbit_trace.end();

            for(vector<complex<double>>::iterator itr = orbit_trace.begin();itr!=end;itr++ ){
                coords point = findCoords(*itr);

                if(point.x >=0 && point.y >=0){//inbounds and inside img
                    //cout<< "called";
                    imgArray[point.x][point.y].iters+=1;
                }else{
                    //cout<< "out of bounds" << endl;
                }
            }
        }

        void draw(complexPixel** pixelList){

            png::image< png::rgb_pixel > image(WIDTH, HEIGHT);
            int max_pixel_val = 255;

            for (int y = 0; y < HEIGHT; y++)
            {
                for (int x = 0; x < WIDTH; x++)
                {
                    int iters = pixelList[x][y].iters;
                    if (iters > max_pixel_val){
                        max_pixel_val = iters;
                    }
                    //int gray = int((double)iters);
                    //image[y][x] = png::rgb_pixel(gray,gray,gray);
                    //}
                }
            }

            for (int y = 0; y < HEIGHT; ++y)
            {
                for (int x = 0; x < (WIDTH-2); ++x)
                {
                    int iters = pixelList[x][y].iters;
                    int gray = (int)((255*(double)iters)/max_pixel_val);
                    image[y][x] = png::rgb_pixel(gray,gray,gray);
                }
            }

            image.write("Fractal_"+to_string(HEIGHT)+"x"+to_string(WIDTH)+"_"+to_string(NO_ITERS)+"_"+to_string(NO_POINTS)+".png");

            for(int i=0;i<WIDTH;i++){
                delete [] pixelList[i];
            }
            delete [] pixelList;
        }
};

int main()
{
    auto start = chrono::steady_clock::now();

    int iters = 200;

    complex<double> center(-0.4,0.5);
    double diam_x = 1;
    double diam_y = 1;
    int image_height = 2000;
    int image_width = 2000;
    int points =image_width*image_height*100;
    //fractal f(iters,center,diam_x,diam_y,image_width,image_height);
    buddhaFractal a(iters,points,center,diam_x,diam_y,image_width,image_height);
    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::seconds>(end - start).count()<< " (s)";
    getch();
    return 0;
}
