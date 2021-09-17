import java.util.Scanner;

public class Problem6{
	public static void main(String args[]){
		Scanner sc=new Scanner(System.in);
        System.out.println("Input a String!");
		String inputString=sc.nextLine();
		int digits=0,letters=0;
		for(int i=0;i<inputString.length();i++){
			if(inputString.charAt(i)>='a' && inputString.charAt(i)<='z') letters++;
			else if(inputString.charAt(i)>='A' && inputString.charAt(i)<='Z') letters++;
			else if(inputString.charAt(i)>='0' && inputString.charAt(i)<='9') digits++;
		}
        System.out.println("Number of letters in the input string = "+letters+" Number of digits in the input string = "+digits);
	}
};