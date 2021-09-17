interface L1{
}

interface L2{
}

interface L3 extends L1,L2{
}

interface L4{
}

class X implements L3{
}

class W extends X implements L4{
}

class Problem6{
	public static void main(String args[]){
		W obj=new W();
		System.out.println("Does W implements interface L1: "+(obj instanceof L1));
		System.out.println("Does W implements interface L2: "+(obj instanceof L2));
		System.out.println("Does W implements interface L3: "+(obj instanceof L3));
		System.out.println("Does W implements interface L4: "+(obj instanceof L4));
		System.out.println("Is W of type class X: "+(obj instanceof X));
	}
}