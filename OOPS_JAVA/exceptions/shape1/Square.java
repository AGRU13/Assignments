package shape1;

public class Square{
    private int side;
    public Square(int side) {
        this.side=side;
    }
    public void show(){
        System.out.println("Side of the square = "+side);
        System.out.println("Area of the square = "+side*side);
    }
};