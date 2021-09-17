interface Shape2D{
	double getArea();
}

interface Shape3D{
	double getVolume();
}

class Point3D{
	double x,y,z;
	Point3D(double _x,double _y,double _z){
		x=_x;
		y=_y;
		z=_z;	
	}
}

abstract class Shape{
	abstract void display();
}

class Circle extends Shape implements Shape2D{
	Point3D center,surface;
	Circle(Point3D _center,Point3D _surface){
		center=_center;
		surface=_surface;
	}
	public double getArea(){
		double dx=center.x-surface.x;
		double dy=center.y-surface.y;
		double radius=Math.sqrt(dx*dx+dy*dy);
		return Math.PI*radius*radius;
	}
	public void display(){
		System.out.printf("\nCenter point of Circle is = (%f, %f, %f) \nand surface point is = (%f, %f, %f)\n",center.x,center.y,center.z,surface.x,surface.y,surface.z);
	}
}

class Sphere extends Shape implements Shape3D{
	Point3D center,surface;
	Sphere(Point3D _center,Point3D _surface){
		center=_center;
		surface=_surface;
	}
	public double getVolume(){
		double dx=center.x-surface.x;
		double dy=center.y-surface.y;
		double radius=Math.sqrt(dx*dx+dy*dy);
		return 4/3*Math.PI*radius*radius*radius;
	}
	public void display(){
		System.out.printf("\nCenter point of Sphere is = (%f, %f, %f) \nand surface point is = (%f, %f, %f)\n",center.x,center.y,center.z,surface.x,surface.y,surface.z);
	}
}

class Problem7{
	public static void main(String args[]){
		Point3D center=new Point3D(10,5,15);
		Point3D surface=new Point3D(1,2,1);	
		Shape objc=new Circle(center,surface);
		objc.display();
		Shape2D obj2d=new Circle(center,surface);
		System.out.println("Area of the circle with the above points is: "+obj2d.getArea());
		Shape objs=new Sphere(center,surface);
		objs.display();
		Shape3D obj3d=new Sphere(center,surface);
		System.out.println("Volume of the sphere with the above points is: "+obj3d.getVolume());
	}
}