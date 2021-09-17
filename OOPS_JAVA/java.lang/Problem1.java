import java.util.Random;

public class Problem1{
	public static void main(String args[]){
		double arr[][]=new double[4][11],average=0;
		Random r=new Random();
		System.out.println("Array = \n");
		for(int i=0;i<4;i++){
			for(int j=0;j<11;j++){
				arr[i][j]=1000*r.nextDouble();
				System.out.print(arr[i][j]+" ");
				average+=arr[i][j];
			}
			System.out.println();
		}
		average/=44;
		System.out.println("The average of the array elements is = "+average);
	}
};
