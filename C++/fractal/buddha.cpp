#include "buddha.h"

BuddhaFractal::BuddhaFractal( int iters, unsigned int points, complex<double> center, double diam_x, double diam_y, int width, int height, ImageArray::complexPixel** img)
:NO_ITERS(iters)
,NO_POINTS(points)
,center(center)
,diam_x(diam_x)
,diam_y(diam_y)
,WIDTH(width)
,HEIGHT(height)
{
    imageArray = img;
    cout<<"Creating Buddhabrot..."<<endl;
    iteration();
}

BuddhaFractal::coords BuddhaFractal::findCoords(complex<double> c)
{
    complex<double> topLeft(-diam_x/2,diam_y/2);
    complex<double> bottomRight(diam_x/2,-diam_y/2);
    topLeft+=center;
    bottomRight+=center;
    coords bounds;

    if(c.real() < topLeft.real() || c.imag()> topLeft.imag() || c.real() > bottomRight.real() || c.imag() < bottomRight.imag())
    {
        bounds.x= -1; //-1, -1 if out of image bounds
        bounds.y = -1;
        return bounds;
    }

    double yInc = diam_y/HEIGHT;
    double xInc = diam_x/WIDTH;
    bounds.x = (center.real()+(diam_x/2)-c.real())/xInc;
    bounds.y = (center.imag()+(diam_y/2)-c.imag())/yInc;

    return bounds;
}

void BuddhaFractal::iteration()
{
    //generate random complex num, trace orbit and mark the pixel matrix
    mt19937 rng;
    uniform_real_distribution<double> unif(center.real()-diam_x/2,center.real()+diam_x/2);
    uniform_real_distribution<double> unif_imag(center.imag()-diam_y/2,center.imag()+diam_y/2);

    rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());

    for(unsigned int i=0;i<NO_POINTS;i++)
    {
        double x = unif(rng);
        double y = unif_imag(rng);
        //Bulb optimizations
        double q = (x-0.25)*(x-0.25) + y*y;
        while (q*(q+(x-0.25)) <= 0.25*y*y || ((x+1)*(x+1))+y*y <= 0.0625)
        {
            x = unif(rng);
            y = unif_imag(rng);
            q = pow((x-0.25),2) + pow(y,2);
        }
        complex<double> sample(x,y);
        orbit(sample);
    }
}

vector<complex<double>> BuddhaFractal::frac_fun(const complex<double> &c)
{
    complex<double> z(0,0);
    vector<complex<double>> orbit_trace;
    orbit_trace.reserve(NO_ITERS);//reserve memory in advance

    for(int i=0;i<NO_ITERS; ++i)
    {
        double zRsq = real(z)*real(z);
        double zIsq = imag(z)*imag(z);

        z.imag((real(z)*imag(z)));
        z.imag(z.imag()+z.imag());
        z.real(zRsq-zIsq);
        z+=c;

        orbit_trace.push_back(z);
        if (zRsq+zIsq > 4)
        {
            return orbit_trace;
        }
    }
    return vector<complex<double>>();
}

void BuddhaFractal::orbit( complex<double> c)
{
    vector<complex<double>> orbit_trace = frac_fun(c);
    vector<complex<double>>::iterator end = orbit_trace.end();

    for(vector<complex<double>>::iterator itr = orbit_trace.begin();itr!=end;itr++ )
    {
        coords point = findCoords(*itr);

        if(point.x >=0 && point.y >=0)//inbounds and inside img
        {
            imageArray[point.x][point.y].iters+=1;
        }
    }
}
