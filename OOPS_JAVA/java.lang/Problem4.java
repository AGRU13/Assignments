public class Problem4{
	public static void main(String args[]){
		String str=new String("quick brown fox jumps over the lazy dog");
        System.out.println("The string is  = "+str);
        System.out.println("Last 10 characters are = "+str.substring(str.length()-10));
	}
};