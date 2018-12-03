import java.util.ArrayList;
import java.awt.image.BufferedImage;
import java.awt.Color;
import java.io.File;

import java.text.SimpleDateFormat;

import javax.imageio.ImageIO;


public class fractal{
	private int NO_ITERS ; // Number of iterations 
	private int WIDTH = 1000; // Image width in pixels
	private int HEIGHT = 1000;// Image height in pixels
	private double diam = 3; //Diameter of the complex plane which is computed
	private complex center ;//The image is centered at this complex point on the complex plane
	public fractal(int iters, complex center, double diam){
		this.diam = diam;
		this.center = center;
		this.NO_ITERS = iters;
		draw(iteration());
	}
	/**
	* This function does the fundamental calculation of the fractal and completes the iteration for a given point in the complex plane.
	* @return complex returns the final complex number computed.
	*/
	private complex fun(complex z, complex c){
		/**Code that determines the set, z^2 + c is mandelbrot (where c is the parameter that span the complex plane) **/
		int count = 0;
		while (count<NO_ITERS){
			count+=1;
			double zRsq = z.real*z.real;
			double zIsq = z.imag*z.imag;
			z.imag = z.real*z.imag;//Math.pow((z.real+z.imag),2) - zRsq - zIsq;
			z.imag+=z.imag;
			z.real = zRsq-zIsq;
			
			z.add(c);
			if (zRsq+zIsq >4){
				z.iters = count;
				z.isBound = false;
				return z;
			}
		}
		z.iters = count;
		return z;
	}
	
	private Pair<ArrayList<Tuple>,ArrayList<Tuple>> iteration(){
		
		ArrayList<Tuple> pixelList = new ArrayList<Tuple>(); //list of pixels in set
		ArrayList<Tuple> nonPixelList = new ArrayList<Tuple>();
		
		double yInc  = diam/HEIGHT;//each pixel has yInc and XInc length on the complex plane.
		double xInc = diam/WIDTH;
		
		complex c = new complex(-diam/2,diam/2);// C value is half the diameter radius, starting at top left corner of complex plane where the center is 0,0, c value changes based on pixel location
		c.add(center);//offsets via the center 
		
		for(int y=0;y<HEIGHT;y++){//iterate vertically
			c.real = -diam/2;//start at the left side
			c.real+=center.real; //shifts via the center offset again
			for (int x=0;x<WIDTH;x++){//iterate horizontally
				complex f = fun(new complex(0,0),c);
				if(f.isBound){
					pixelList.add(new Tuple(x,y,f.abs(),f.iters));
				}else{
					nonPixelList.add(new Tuple(x,y,f.abs(),f.iters));
				}
				c.real+=xInc;
			}
			c.imag-=yInc;
		}
		
		return new Pair(pixelList,nonPixelList);
	}
	
	private void draw (Pair pixelList){
		/**This function takes two lists, pixels that are in the mandelbrot set and those that aren't, draws and saves the image**/
		
		BufferedImage img = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
		
		for(Tuple tup : (ArrayList<Tuple>) pixelList.a){
			
			img.setRGB(tup.x ,tup.y,new Color(0,0 ,(int)(tup.iter*(float) 255/ NO_ITERS)).getRGB());
		}
		
		for(Tuple tup : (ArrayList<Tuple>) pixelList.b){
			
			img.setRGB(tup.x ,tup.y,new Color((int)( 0- ((float)tup.iter/NO_ITERS)*-1*255),(int)(255/(Math.pow(1.001,tup.iter))) ,0).getRGB());
		}
		
		
		
	
		File outputfile = new File(String.format("image_%d_%d_%d_%f.png",WIDTH,HEIGHT,NO_ITERS,diam));
		try{
		ImageIO.write(img, "png", outputfile);
		}catch(Exception IOException){
	
		}
	}
} 