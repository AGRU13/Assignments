class MotorCycle{
	String color;
	String type;
	int speed;
	MotorCycle(String color,String type,int speed){
		this.color=color;
		this.type=type;
		this.speed=speed;
	}
	void show(){
		System.out.println("Features of this MotorCyle are:= ");
		System.out.println("Color = "+color);
		System.out.println("Type = "+type);
		System.out.println("Speed = "+speed);
	}
}
public class Problem1{
	public static void main(String args[]){
		MotorCycle m1=new MotorCycle("Black","Chopper",50);
		MotorCycle m2=new MotorCycle("Green","Dirt bike",70);
		MotorCycle m3=new MotorCycle("Red","Cruiser",40);
		MotorCycle m4=new MotorCycle("Brown","Scooter",30);
		m1.show();
		m2.show();
		m3.show();
		m4.show();
	}
}