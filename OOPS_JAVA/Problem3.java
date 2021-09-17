import java.lang.Math.*;

class Circle{
	private double radius;
	Circle(double _radius){
		radius=_radius;
	}

	double area(){
		return Math.PI*radius*radius;
	}
	
	double perimeter(){
		return 2*Math.PI*radius;
	}
	
	double getRadius(){
		return radius; 
	}	
}

public class Problem3 {
   
    public static void main(String args[]) {
        Circle obj=new Circle(10);
	System.out.println("Area of the Circle with radius "+obj.getRadius()+" is = "+obj.area());
	System.out.println("Perimeter of the Circle with radius "+obj.getRadius()+" is = "+obj.perimeter());
    }
}