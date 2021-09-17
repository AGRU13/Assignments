import java.util.Scanner;

class NullStringException extends Exception{
    NullStringException(){};
    public String toString(){
        return "Entered String is null, exiting from the program!!";
    }
};

public class Problem5{
	public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        String strings[]=new String[10];
        System.out.println("Enter strings: ");
        try{
            for(int i=0;i<10;i++){
                strings[i]=sc.nextLine();
                if(strings[i].length()==0) throw new NullStringException();
            }
        }catch(NullStringException e){
            System.out.println(e);
        }
    }
};