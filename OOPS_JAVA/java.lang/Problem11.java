import java.util.Scanner;

public class Problem11{
	public static void main(String args[]){
		Scanner sc=new Scanner(System.in);
        System.out.println("Enter the first string: ");
        String str1=sc.nextLine();
        System.out.println("Enter the second string: ");
        String str2=sc.nextLine();
        str1=str1.replaceAll("\\s","");
        str2=str2.replaceAll("\\s","");
        System.out.println("First string after removing whitespaces: "+str1);
        System.out.println("Second string after removing whitespaces: "+str2);
        if(str1.equals(str2))  System.out.println("Strings are equal!!");
        else System.out.println("Strings are not equal!!");
	}
};