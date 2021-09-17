interface K1{
	void methodK();
	int intK=1;
}

interface K2 extends K1{
	public void methodK();
}

interface K3 extends K2{
	public void methodK();
}

class U implements K3{
	public void methodK(){
		System.out.println("\nVariable intK = "+intK);
	}
}

class Problem5{
	public static void main(String[] args){
		U obj=new U();
		obj.methodK();
	}
}