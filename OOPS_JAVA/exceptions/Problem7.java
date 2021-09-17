import java.util.Scanner;

class StudentNotPresentException extends Exception{
    int roll;
    StudentNotPresentException(int _roll){
        roll=_roll;
    }
    @Override
    public String toString(){
        return "Student with roll number = "+roll+" ,not present in the database";
    }
}

class Students{
    private String name;
    private String branch;
    private int roll;
    Students(String _name,String _branch,int _roll){
        name=_name;
        branch=_branch;
        roll=_roll;
    }

    int getRoll(){
        return roll;
    }

    void show(){
        System.out.println("Student information: ");
        System.out.println("Name = "+name);
        System.out.println("Branch = "+branch);
        System.out.println("roll = "+roll);
    }
};

public class Problem7{
	public static void main(String args[]){
        Students obj[]=new Students[20];
        String names[]={"John","Mclovin","Henry","Ada","Mobak","Arjan","Saransh","Ayush",
                    "Kennedy","Victoria","Charles","Pewds","Corpse","Pokimane","Amit","Aman",
                    "Anuj","Sajal","Aditya","Saurav"};
        String branches[]={"IT","CST","ECE","ME","CE","AE","IT","CST","ECE","ME","CE","AE",
                        "IT","CST","ECE","ME","CE","AE","IT","CST"};
        int rolls[]={818055,718005,618021,518032,918067,318045,818078,718012,618001,518023,918084,318057,
                    818074,718017,618037,518083,918091,318010,818020,718044};
        System.out.println("Roll number of the students present in the database: ");
        for(int i=0;i<20;i++){
            System.out.println(rolls[i]);
            obj[i]=new Students(names[i],branches[i],rolls[i]);
        }
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter roll number to get information about the student.");
        int rollForInfo=sc.nextInt(),flag=0;
        try{
            for(int i=0;i<20;i++){
                if(obj[i].getRoll()==rollForInfo) {
                    obj[i].show();
                    flag=1;
                    break;
                }
            }
            if(flag==0) throw new StudentNotPresentException(rollForInfo);
        }catch(StudentNotPresentException e){
            System.out.println(e);
        }         
    }
};