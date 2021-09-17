import pk1.*;

public class Problem9{
	public static void main(String args[]){
        Same obj=new Same(1000);
        Sbclass sbobj=new Sbclass(4153);
        Prclass probj=new Prclass(1);
        System.out.println("Calling protected variable from same package non-sub class"+obj.getVar());
        System.out.println("Calling protected variable from same package sub class"+sbobj.getVar());
        System.out.println("Calling protected variable from different package non-sub class"+probj.var);
    }
};