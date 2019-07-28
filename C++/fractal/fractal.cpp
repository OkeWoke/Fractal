#include "fractal.h"

Fractal::Fractal(int iters, complex<double> center, double diam_x, double diam_y, int width, int height,ImageArray::complexPixel** img)
:NO_ITERS(iters)
,center(center)
,diam_x(diam_x)
,diam_y(diam_y)
,WIDTH(width)
,HEIGHT(height)
{
    imageArray = img;
    cout<<"Creating Fractal..." <<endl;
    iteration();
}

void Fractal::iteration()
{
    double yInc = diam_y/HEIGHT;
    double xInc = diam_x/WIDTH;

    complex<double> c = complex<double>(-diam_x/2,diam_y/2);
    c+=center;//view shift

    for(int y= 0;y<HEIGHT;y++)
    {
        c.real(-diam_x/2);
        c.real(center.real() + c.real());
        for(int x=0; x<WIDTH;x++)
        {
            ImageArray::complexPixel f = fun(c);
            //f.x = x;
            //f.y =y;
            //f.cPoint = c;
            imageArray[x][y] = f;

            //pixelList.push_back(f);
            c.real(c.real()+xInc);
        }
        c.imag(c.imag()-yInc);
    }
}

ImageArray::complexPixel Fractal::fun(const complex<double>& c)
{
    complex<double> z(0,0);
    ImageArray::complexPixel cP;
    //cP.cPoint = z;//is this a copy or a reference?
    for(int i=0;i<NO_ITERS; ++i)
    {
        double zRsq = real(z)*real(z);
        double zIsq = imag(z)*imag(z);

        z.imag((real(z)*imag(z)));
        z.imag(z.imag()+z.imag());
        z.real(zRsq-zIsq);
        z+=c;

        if (zRsq+zIsq > 4)
        {
            cP.iters = i;
            return cP;
        }
    }
    cP.iters = NO_ITERS;
    return cP;
}
