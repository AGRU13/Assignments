public class Problem6{
	public static void main(String args[]){
        try{
            int arr[]=new int[5];
            arr[5]=100;
        }catch(ArrayIndexOutOfBoundsException e){
            System.out.println("Trying to acces array out of size array element");
        }
        System.out.println("back to main");
    }
};