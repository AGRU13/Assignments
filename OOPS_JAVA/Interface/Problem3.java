interface LuminousObject{
	void lightOff();
	void lightOn();
}

class SolidObject{
}

class Cone extends SolidObject {
}

class Cube extends SolidObject{
}

class LuminousCone extends Cone implements LuminousObject{
	public void lightOff(){
		System.out.println("Light Off for Luminuous Cone.");	
	}	
	public void lightOn(){
		System.out.println("Light On for Luminuous Cone.");	
	}
}

class LuminousCube extends Cube implements LuminousObject{
	public void lightOff(){
		System.out.println("\nLight Off for Luminuous Cube.");	
	}	
	public void lightOn(){
		System.out.println("Light On for Luminuous Cube.");	
	}
}

 
class Problem3{
	public static void main(String args[]){
		LuminousObject obj;
		obj=new LuminousCone();
		obj.lightOff();
		obj.lightOn();
		obj=new LuminousCube();
		obj.lightOff();
		obj.lightOn();	
	}
}