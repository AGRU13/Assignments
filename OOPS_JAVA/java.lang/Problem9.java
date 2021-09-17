import java.util.*;

public class Problem9{
	public static void main(String args[]){
        int n;
		System.out.println("Enter a number to find its factors");
        Scanner sc=new Scanner(System.in);
        n=sc.nextInt();
        ArrayList<Integer> divisors=new ArrayList<Integer>();
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                divisors.add(i);
                if(i!=n/i) divisors.add(n/i);
            }
        }
        divisors.add(n);
        Collections.sort(divisors);
        System.out.println("factors of "+n+" are = ");
        for(int ele :divisors) System.out.print(ele+" ");
	}
};