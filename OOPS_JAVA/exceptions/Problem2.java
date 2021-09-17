public class Problem2{
	public static void main(String args[]) throws Exception{
        int len=args.length;
        if(len!=3) {
            throw new Exception("Number of Command line Arguments should be 3");
        }
        int st=0,en=0;
        try{
            st=Integer.parseInt(args[0]);
            en=Integer.parseInt(args[1]);
        }catch(NumberFormatException e){
            System.out.println("First and Second arguments should be valid integers!!");
            return ;
        }
        String str=args[2];
        if(st<0){
            throw new Exception("First argument should not be negative!!");
        }
        else if(st>=str.length()){
            throw new Exception("First argument greater than string length");
        }
        else if(st>=en){
            throw new Exception("First argument should be less than second argument");
        }
        else if(en>str.length()){
            throw new Exception("Second argument greater than string length!!");
        }
        System.out.println(str);
        System.out.println(st+" "+en);
        str=str.substring(st,en);
        for(int i=str.length()-1;i>=0;i--)
            System.out.print(str.charAt(i));
    }
};