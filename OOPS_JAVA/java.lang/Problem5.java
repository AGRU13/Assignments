public class Problem5{
	public static void main(String args[]){
		String str=new String("132,342,5434,231,45345");
        System.out.println("The string is  = "+str);
        System.out.println("Last number in the string is = "+str.substring(str.lastIndexOf(',')+1));
	}
};