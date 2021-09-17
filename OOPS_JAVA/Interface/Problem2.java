interface AntiLockBrakes{
	String antiLockBrakes();
}

interface CruiseControl{
	String cruiseControl();
}

interface PowerSteering{
	String powerSteering();
}

abstract class Auto{
	abstract void display();
} 

class Model1 implements PowerSteering{
	public String powerSteering(){
		return "Power Steering";
	}

	void display(){
		System.out.println("Optional Functionality present in Model1= "+powerSteering());
	}
}

class Model2 implements AntiLockBrakes,CruiseControl{
	public String antiLockBrakes(){
		return  "Anti-Lock Brakes";
	}

	public String cruiseControl(){
		return "Cruise Control";
	}

	void display(){
		System.out.println("Optional Functionalities present in Model2= "+antiLockBrakes()+" and "+cruiseControl());
	}
}

class Model3 implements CruiseControl{
	public String cruiseControl(){
		return "Cruise Control";
	}

	void display(){
		System.out.println("Optional Functionality present in Model3= "+cruiseControl());
	}
}

class Problem2{
	public static void main(String args[]){
		Model1 objm1=new Model1();
		Model2 objm2=new Model2();
		Model3 objm3=new Model3();
		objm1.display();
		objm2.display();
		objm3.display();
	}
}