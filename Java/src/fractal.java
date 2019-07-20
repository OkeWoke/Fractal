import java.util.ArrayList;
import java.awt.image.BufferedImage;
import java.awt.Color;
import java.io.File;
import javax.imageio.ImageIO;

public class fractal{
	/** This contains a collection of functions to do the following:
	 *  interation() -> compute mapping of pixel space to point space in  
	 * fun() - > given a complex point it determines if its bound to mandelbrot set
	 * draw() -> Takes output from iteration and draws an image based upon bound set
	 */
	
	private int NO_ITERS ; // Number of iterations 
	private int WIDTH = 1000; // Image width in pixels
	private int HEIGHT = 1000;// Image height in pixels
	private double diam = 3; //Diameter of the complex plane which is computed
	private complex center ;//The image is centered at this complex point on the complex plane
	
	public fractal(int iters, complex center, double diam, int width, int height){
		this.diam = diam;
		this.center = center;
		this.NO_ITERS = iters;
		this.WIDTH = width;
		this.HEIGHT = height;
		
		draw(iteration());
	}
	
	/**
	* This function does the fundamental calculation of the fractal and completes the iteration for a given point in the complex plane.
	* @return complex returns the final complex number computed.
	*/
	private complex fun( complex c){
		/**Code that determines the set, z^2 + c is mandelbrot (where c is the parameter that span the complex plane) **/
		
		complex z = new complex(0,0);
		
		for(int count =0; count< NO_ITERS;++count) {
			
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
		
		z.iters = NO_ITERS;//count;
		return z;
	}
	
	private ArrayList<complex> iteration(){
		
		ArrayList<complex> pixelList = new ArrayList<complex>(); //list of pixels in set
		
		double yInc  = this.diam/HEIGHT;//each pixel has yInc and XInc length on the complex plane.
		double xInc = this.diam/WIDTH;
		
		complex c = new complex(-this.diam/2,this.diam/2);// C value is half the diameter radius, starting at top left corner of complex plane where the center is 0,0, c value changes based on pixel location
		c.add(this.center);//offsets via the center 
		
		for(int y=0;y<HEIGHT;y++){//iterate vertically
			c.real = -this.diam/2;//start at the left side
			c.real+=this.center.real; //shifts via the center offset again
			for (int x=0;x<WIDTH;x++){//iterate horizontally
				complex f = fun(c);
				f.x = x;
				f.y = y;
				pixelList.add(f);
				c.real+=xInc;
			}
			c.imag-=yInc;
		}
		
		return pixelList;
	}
	
	private void draw (ArrayList<complex> pixelList){
		/**sorts pixels that are in the mandelbrot set and those that aren't, draws and saves the image**/
		
		BufferedImage img = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
		
		for (complex c : (ArrayList<complex>) pixelList ) {//in mandel brot set
			if (c.isBound) {
				img.setRGB(c.x ,c.y,new Color(0,0 ,(int)(c.iters*(float) 255/ NO_ITERS)).getRGB()); 
			}else {// not in
				img.setRGB(c.x ,c.y,new Color((int)( 0- ((float)c.iters/NO_ITERS)*-1*255),(int)(255/(Math.pow(1.001,c.iters))) ,0).getRGB()); 
			}
		}
		
		//saving img code
		File outputfile = new File(String.format("image_%d_%d_%d_%f.png",WIDTH,HEIGHT,NO_ITERS,this.diam));
		try{
		ImageIO.write(img, "png", outputfile);
		}catch(Exception IOException){
			System.out.println("Error: Unable to write image file.");
		}
	}
} 