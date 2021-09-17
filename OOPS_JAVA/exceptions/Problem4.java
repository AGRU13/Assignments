public class Problem4{
	public static void main(String args[]){
        System.out.println("Starting operations.");
        try{
            int a=args.length;
            int b=10/a;
            try{
                a=Integer.parseInt(args[0]);
                int arr[]=new int[5];
                if(a==1) a=10/(a-a);
                else if(a==2) arr[5]=10;
            }catch(ArrayIndexOutOfBoundsException e){
                System.out.println("Trying to access out of size array element");
            }
        }catch(ArithmeticException e){
            System.out.println("Division by 0 is not defined");
        }
        System.out.println("back to main.");
    }
};