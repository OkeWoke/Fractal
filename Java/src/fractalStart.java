

public class fractalStart{

	public static void main(String[] args){
		
		double startTime = System.nanoTime();
		
		int iters = 10;
		complex center = new complex(-1.7798310726,0.0000768808);
		double diam = 0.0001;
		int height = 10000;
		int width = 10000;
		
		fractal f =  new fractal(iters, center,diam,width,height);
		
		/** Code for making zooming in parameters for animation
		 * while(diam>0.0001) {
			
			//iters = (int) (iters*=1.05);
			if(iters <2000) {
				iters+=50;
			}
			diam/=1.1;
		}**/
		
		
		double endTime = System.nanoTime();

		double  duration = (endTime - startTime);
		System.out.println(duration/1000000000);
	}
}