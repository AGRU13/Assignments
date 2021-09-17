public class Problem3{
	public static void main(String args[]){
        int a=1231,b=0;
        System.out.println("Going to perform division now.");
        try{
            System.out.println(a/b);
        }catch(ArithmeticException e){
            System.out.println("Division by zero is not defined!!");
        }
        System.out.println("back to main.");
    }
};