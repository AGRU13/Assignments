package shape3;

public class Circle{
    private int radius;
    public Circle(int radius){
        this.radius=radius;
    }
    public void show(){
        System.out.println("Radius of the circle = "+radius);
        double area=Math.PI*radius*radius;
        System.out.println("Area of the circle = "+area);   
    }
};