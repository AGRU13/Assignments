class Check{
	void show(Check obj){
		System.out.println("Function called using this keyword");
	}

	void print(){	
		show(this);
	}
}

public class Problem3{
	public static void main(String args[]){
		Check obj=new Check();
		obj.print();
	}
}