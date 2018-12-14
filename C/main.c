#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <png.h>

#define WIDTH 1000
#define HEIGHT 1000
//const int WIDTH = 1000;
//const int HEIGHT = 1000;
int ITERS = 100;
double diam = 3;
double complex center = 0 + 0*I;


struct point {
    int x;
    int y;
    double abs;
    int iters;
};

int main()
{


    return 0;
}

struct point iter(double complex z, double complex c){
    int count = 0;
    struct point f;
    double zRsq = creal(z)*creal(z);
    double zIsq = cimag(z)*cimag(z);
    while(count<ITERS){
        double zRsq = creal(z)*creal(z);
        double zIsq = cimag(z)*cimag(z);

        z = creal(z)+ (creal(z)*cimag(z))*I;
        z= (zRsq-zIsq)+(cimag(z)+cimag(z))*I;//multiple by 2 and chang creal
        z+=c;

        if(zRsq+zIsq > 4){
            f.abs = zIsq+zRsq;
            f.iters = count;
            return f;
        }
        count+=1;
    }
    f.abs = zIsq+zRsq;
    f.iters = count;
    return f;
}


struct point * pixelIter(){
    static struct point points[WIDTH*HEIGHT];//Aray containng all points sampled on complex plane

    double yInc = diam/HEIGHT;
    double xInc = diam/WIDTH;

    double complex c =  -diam/2+creal(center) + (diam/2+cimag(center)) * I;
    int index = 0;
    for(int y=0;y<HEIGHT;y++){
        c = -diam/2+creal(center) + cimag(c)*I;
        for(int x=0;x<WIDTH;x++){
            double complex a = 0+0*I;
            struct point f = iter(a,c);
            f.x =x;
            f.y=y;
            points[index] = f;
            index++;
            c +=xInc;
        }
        c-=yInc*I;

    }

    return points;
}


void draw(struct point points[]){


}
