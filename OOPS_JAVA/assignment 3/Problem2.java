class Student{
	String name;
	int roll;
	int sem;
	double marks;
	Student(String name,int roll,int sem,double marks){
		this.name=name;
		this.roll=roll;
		this.sem=sem;
		this.marks=marks;
	}
	void show(){
		System.out.println("Student Information:= ");
		System.out.println("Name: "+name);
		System.out.println("Roll Number: "+roll);
		System.out.println("Semester: "+sem);
		System.out.println("Marks: "+marks);
	}
}

public class Problem2{
	public static void main(String args[]){
		Student stu=new Student("Ayush Agrawal",510818055,5,516.50);
		stu.show();
	}
}	
