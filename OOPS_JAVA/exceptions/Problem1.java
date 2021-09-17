import java.util.Random;

class LessBalanceException extends Exception{
    private int amount;
    LessBalanceException(int _amount){
        amount=_amount;
    }
    @Override
    public String toString(){
        return "Cannot withdraw amount "+amount+ " ,Insufficient balance in the account!!";
    }
}

class Account{
    int accNo;
    int bal;
    String name;
    Account(int _accNo,int _bal,String _name){
        accNo=_accNo;
        bal=_bal;
        name=_name;
    }

    void withdraw(int amount) throws LessBalanceException{
        System.out.println("Available balance: "+bal);
        bal-=amount;
        if(bal<1000){
            bal+=amount;
            throw new LessBalanceException(amount);
        }
        System.out.println(amount+" debited from the account");
    }
}

public class Problem1{
	public static void main(String args[]){
        Random r=new Random();
        Account obj[]=new Account[6];
        obj[0]=new Account(1231,1000+r.nextInt(2000),"ANIL");
        obj[1]=new Account(6345,1000+r.nextInt(2000),"SUNIL");
        obj[2]=new Account(2138,1000+r.nextInt(2000),"RAJESH");
        obj[3]=new Account(8234,1000+r.nextInt(2000),"SURESH");
        obj[4]=new Account(3472,1000+r.nextInt(2000),"MOBAK");
        for(int i=0;i<5;i++){
            try{
                obj[i].withdraw(1000);
            }catch(LessBalanceException e){
                System.out.println(e);
            }
        }
	}
};