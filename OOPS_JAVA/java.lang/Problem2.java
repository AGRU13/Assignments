import java.util.Random;

public class Problem2{
	public static void main(String args[]){
		int arr[][]=new int[3][2];
        double rowAverage=0,colAverage=0,grandAverage=0;
		Random r=new Random();
		System.out.println("Matrix = \n");
		for(int i=0;i<3;i++){
			for(int j=0;j<2;j++){
				arr[i][j]=r.nextInt(100000);
                System.out.print(arr[i][j]+" ");
				grandAverage+=arr[i][j];
			}
			System.out.println();
		}
        System.out.println("Row wise averages = ");
        for(int i=0;i<3;i++){
            rowAverage=0;
			for(int j=0;j<2;j++){
				rowAverage+=arr[i][j];
			}
            rowAverage/=2;
			System.out.println("Average of row "+(i+1)+" is = "+rowAverage);
		}
        System.out.println("Column wise averages = ");
        for(int j=0;j<2;j++){
            colAverage=0;
			for(int i=0;i<3;i++){
				colAverage+=arr[i][j];
			}
            colAverage/=3;
			System.out.println("Average of column "+(j+1)+" is = "+colAverage);
		}
		grandAverage/=6;
		System.out.println("The average of the all the array elements is = "+grandAverage);
	}
};
