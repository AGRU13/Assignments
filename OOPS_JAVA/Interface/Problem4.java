interface P{
	int p=10;
	void displayP();
}

interface P1 extends P{
	int p1=20;
	void displayP1();
}

interface P2 extends P{
	int p2=30;
	void displayP2();
}

interface P12 extends P1,P2{
	int p12=1000;
	void displayP12();	
} 

class Q implements P12{
	public void displayP(){
		System.out.println("Value of P: "+p);
	}
	public void displayP1(){
		System.out.println("Value of P1: "+p1);
	}
	public void displayP2(){
		System.out.println("Value of P2: "+p2);
	}
	public void displayP12(){
		System.out.println("Value of P12: "+p12);
	}
}

class Problem4{
	public static void main(String args[]){
		Q obj=new Q();
		obj.displayP();
		obj.displayP1();	
		obj.displayP2();
		obj.displayP12();
	}
}