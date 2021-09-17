import java.util.*;

class Distance
{
	private double metres;
	
	public void getDistance()
	{
		Scanner sc=new Scanner(System.in);
		
		System.out.print("Enter distance in metres: ");
		metres=sc.nextDouble();
	}
	public void showDistance()
	{
		System.out.println("Distance: "+ metres);
	}
	
	public void addDistance(Distance D1, Distance D2)
	{
		metres=D1.metres+D2.metres;
	}
}

public class Problem4
{
	public static void main(String []s)
	{

		Distance D1=new Distance();
		Distance D2=new Distance();
		Distance D3=new Distance();
			
		System.out.println("Enter first distance: ");
		D1.getDistance();
			
		System.out.println("Enter second distance: ");
		D2.getDistance();
			
		D3.addDistance(D1,D2);

		System.out.println("Total distance is:" );
		D3.showDistance();
	}
	
}
