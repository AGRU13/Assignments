class test{
	static int count=0;
	void add(){
		count++;
	}
	void show(){
		System.out.println("Value of count variable is = "+count);
	} 
}

public class Problem4{
	public static void main(String args[]){
		test ob1=new test();
		test ob2=new test();
		test ob3=new test();
		test ob4=new test();
		System.out.println("Value of count accessed through first object = ");
		ob1.show();
		System.out.println("Adding 1 to the value of count through first object.");
		ob1.add();
		System.out.println("Value of count accessed through second object = ");
		ob2.show();
		System.out.println("Adding 1 to the value of count through second object.");
		ob2.add();
		System.out.println("Value of count accessed through third object = ");
		ob3.show();
		System.out.println("Adding 1 to the value of count through third object.");
		ob3.add();
		System.out.println("Value of count accessed through fourth object = ");
		ob4.show();
		System.out.println("Adding 1 to the value of count through fourth object.");
		ob4.add();
		System.out.println("Value of count accessed through first object = ");
		ob1.show();
	}
}