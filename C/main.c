#include <stdio.h>
#include <stdlib.h>
#include <complex.h>


int WIDTH = 1000;
int HEIGHT = 1000;
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



void pixelIter(){
    struct point boundPoints[WIDTH*HEIGHT];
    struct point unBoundPoints[WIDTH*HEIGHT];

    struct point* points;

    double complex c =  -diam/2+creal(center) + (diam/2+cimag(center)) * I;
    for(int y=0;y<HEIGHT;y++){
        c = -diam/2+creal(center) + cimag(c)*I;
        for(int x=0;x<WIDTH;x++){
            double complex a = 0+0*I;
           // point f = iter(a,c);
            //if(f.iters>=ITERS){

            //}
        }

    }
}
