class Overload{
        int a,b; 
        public Overload(){
            a=5;
            b=5;
            System.out.println("a = "+a+" b = "+b);
        }
        public Overload(int _a){
            a=_a;
            b=5;
            System.out.println("a = "+a+" b = "+b);
        }
        public Overload(int _a,int _b){
            a=_a;
            b=_b;
            System.out.println("a = "+a+" b = "+b);
        }
    }

public class Main {
   
    public static void main(String args[]) {
        Overload ob1=new Overload();
        Overload ob2=new Overload(100);
        Overload ob3=new Overload(77,77);
    }
}