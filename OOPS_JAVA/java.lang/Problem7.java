import java.util.Scanner;

public class Problem7{
	public static void main(String args[]){
        System.out.println("Enter a number for primality check");
		Scanner sc=new Scanner(System.in);
        int n=sc.nextInt(),isPrime=1;
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                isPrime=0;
                break;
            }
        }
        if(isPrime==1) System.out.println(n+" is a prime number");
        else System.out.println(n+" is not a prime number");
	}
};