abstract class Airplane{
	int serialNumber;
	int passengerCapacity;
	String type;
	Airplane(int sn,int pc,String tp){
		serialNumber=sn;
		passengerCapacity=pc;
		type=tp;
	}
	public abstract String toString();
}

class B747 extends Airplane{
	B747(int sn,int pc,String tp){
		super(sn,pc,tp);
	}
	public String toString(){
		return "\ntype : "+type+" B747"+"\nSerial Number : "+serialNumber+"\nPassenger Capacity : "+ passengerCapacity;
	}
}

class B757 extends Airplane{
	B757(int sn,int pc,String tp){
		super(sn,pc,tp);	
	}
	public String toString(){
		return "\ntype : "+type+" B757"+"\nSerial Number : "+serialNumber+"\nPassenger Capacity : "+ passengerCapacity;
	}
}

class B767 extends Airplane{
	B767(int sn,int pc,String tp){
		super(sn,pc,tp);
	}
	public String toString(){
		return "\ntype : "+type+" B767"+"\nSerial Number : "+serialNumber+"\nPassenger Capacity : "+ passengerCapacity;
	}
}

class Problem1{
	public static void main(String args[]){
		B747 obj1=new B747(1234,800,"Airbus");
		B757 obj2=new B757(8976,500,"Boeing");
		B767 obj3=new B767(4532,600,"Boeing");
		System.out.println(obj1.toString());
		System.out.println(obj2.toString());
		System.out.println(obj3.toString());
	}
}