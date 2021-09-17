package shape2;

public class Triangle{
    private int a,b,c;
    public Triangle(int a,int b,int c){
        this.a=a;
        this.b=b;
        this.c=c;
    }
    public void show(){
        System.out.println("Sides of the triangle are = "+a+" "+b+" "+c);
        if((a+b)>c && (a+c)>b && (b+c)>a){
            int s=(a+b+c)/2;
            double  area=Math.sqrt(s*(s-a)*(s-b)*(s-c));
            System.out.println("Area of Triangle is: " + area);    
        }
        else  System.out.println("Area of Triangle not exit");
    }
};