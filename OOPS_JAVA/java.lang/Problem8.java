public class Problem8{
	public static void main(String args[]){
        System.out.println("Following are the numbers that are evenly divided by 17 in the range 1-100: ");
		for(int i=1;i<=100;i++){
            if(i%2==0&&i%17==0) System.out.println(i);
        }
	}
};