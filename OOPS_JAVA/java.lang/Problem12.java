import java.util.Scanner;

public class Problem12{
	public static void main(String args[]){
		Scanner sc=new Scanner(System.in);
        System.out.println("Enter a string");
        String str=sc.nextLine();
        str=str.toLowerCase();
        int vowels=0,i=0;
        while(i<str.length()){
            char ch=str.charAt(i);
            if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u')  vowels++;
            i++;
        }
        System.out.println("Number of vowels in the given string is = "+vowels);
	}
};