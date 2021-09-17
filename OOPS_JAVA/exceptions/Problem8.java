import shape1.Square;
import shape2.Triangle;
import shape3.Circle;

public class Problem8{
	public static void main(String args[]){
        Square sq=new Square(14);
        Triangle tr=new Triangle(3,4,5);
        Circle cr=new Circle(10);
        sq.show();
        tr.show();
        cr.show();
    }
};