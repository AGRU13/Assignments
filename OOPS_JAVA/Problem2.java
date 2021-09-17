class Car{
	String type;
	String color;
	String make;
	String gear_type;
	long cost;
	double mileage;
	Car(String _type,String _color, String _make, String _gear_type,long _cost, double _mileage){
		type=_type;
		color=_color;
		make=_make;
		gear_type=_gear_type;
		cost=_cost;
		mileage=_mileage;
	}
	void show(){
		System.out.println("Details of the car := ");
		System.out.println("Car Type =  "+type+"\nCar Color = "+color+"\nCar's make = "+make+"\n Gear Type = "+gear_type+"\nMileage = "+mileage+"\nCost in Rupees= "+cost);;
	} 
}

public class Problem2{

	public static void main(String args[]){
		Car obj=new Car("Sports","Red","Audi","Manual Transmission",13300000,18.25);
		obj.show();
	}
}