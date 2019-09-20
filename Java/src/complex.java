import java.util.ArrayList;

public class complex{
/**Custom class to represent complex numbers also contains 2 properties, iteration count and bound boolean to minimize arithmetic done**/
	
	public double real;//real part
	public double imag;//imaginary part
	
	public int iters = 0;  //When this complex number's absolute  value exceeds 2 after a number of computational iterations it assigns the number of iterations taken here.
	public boolean isBound = true;// Whether or not abs value was < 2 at termination.
	
	public int x;
	public int y;
	
	public complex(double a, double b){
		this.real = a;
		this.imag = b;
	}
	
	public void add(complex c){
		/** add's complex c to this **/
		this.real +=c.real;
		this.imag +=c.imag;
	}
	
	public double abs(){
		/** Returns the absolute value of this complex number**/
		return this.real*this.real+this.imag*this.imag;
	}
	
	public String toString(){
		/** Returns formatted string of complex number in: (x,yi) form.**/
		return String.format("(%.2f,%.2fi)",this.real,this.imag);
	}
}