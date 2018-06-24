package assignment07;

public class Driver {
	public static void main(String[] args) {
		Person person1 = new Person("Marty McFly");
		Person person2 = new Person("Doc Emmitt Brown");
		
		Student student1 = new Student(person1, "History", true);
		Student student2 = new Student(person2, "History", false);
		
		student1.addGenEd(GenEd.FL1);
		student1.addGenEd(GenEd.A);
		student1.addGenEd(GenEd.N);
		student1.addGenEd(GenEd.J);
		
		student2.addGenEd(GenEd.FL1);
		student2.addGenEd(GenEd.A);
		student2.addGenEd(GenEd.N);
		student2.addGenEd(GenEd.J);
		
		System.out.println("Student1 when History: " + student1.auditGenEd());		
		System.out.println("Student2 when History: " + student2.auditGenEd());
		
		student1.setMajor("Computer Science");		
		student2.setMajor("Computer Science");
		
		System.out.println("Student1 when Computer Science: " + student1.auditGenEd());		
		System.out.println("Student2 when Computer Science: " + student2.auditGenEd());
		
		student1.setMajor("Electrical Engineering");		
		student2.setMajor("Electrical Engineering");
		
		System.out.println("Student1 when Electrical Engineering: " + student1.auditGenEd());
		System.out.println("Student2 when Electrical Engineering: " + student2.auditGenEd());

		
	}
}
