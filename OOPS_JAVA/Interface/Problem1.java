interface Material{
	String PLASTIC="plastic";
	String RUBBER="rubber";
	String LEATHER="leather";
	String COPPER="copper";
	String GOLD="gold";
	String SILVER="silver";
	String IRON="iron";
	String STEEL="steel";  
}

abstract class MatObject implements Material{
	protected String material;
	MatObject(String _material){
		material=_material;
	}
	abstract void display();
}

class Ball extends MatObject{
	Ball(String _material){
		super(_material);	
	}		
	
	void display(){
		System.out.println("This Ball is made up of: "+material);
	}
}

class Coin extends MatObject{
	Coin(String _material){
		super(_material);	
	}		
	
	void display(){
		System.out.println("This Coin is made up of: "+material);
	}
}

class Ring extends MatObject{
	Ring(String _material){
		super(_material);	
	}		
	
	void display(){
		System.out.println("This Ring is made up of: "+material);
	}
}

class Problem1{
	public static void main(String args[]){
		MatObject[] obj=new MatObject[3];
		obj[0]=new Ball(Material.PLASTIC);
		obj[1]=new Ring(Material.SILVER);
		obj[2]=new Coin(Material.COPPER);	
		for(MatObject object:obj)
			object.display();
	}
}
