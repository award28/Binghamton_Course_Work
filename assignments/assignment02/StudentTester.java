package assignment02;

import java.time.LocalDate;
import assignment01.Person;
import assignment01.Gender;

public class StudentTester {

	public static void main(String[] args){
		//Student Star Lord
		LocalDate dob1 = LocalDate.of(1995,12,10);
		Gender gen1 = Gender.MALE;
		Person futureStudent = new Person("Star", "Lord", "247225490", gen1, dob1);
		Student student = new Student(futureStudent);

		//Course 1
		Course course1 = new Course("Africa,Carib,Amer","AFST","180R",4);
		Offering offering1 = new Offering(course1,12574,201190);
		MyClass class1 = new MyClass(offering1, "A");
		student.addToMyClass(class1);

		//Course 2
		Course course2 = new Course("Calculus I", "MATH", "221", 4);
		Offering offering2 = new Offering(course2,11084,201190);
		MyClass class2 = new MyClass(offering2, "B+");
		student.addToMyClass(class2);

		//Course 3
		Course course3 = new Course("Coming to Voice", "WRIT", "111", 4);
		Offering offering3 = new Offering(course3,94123,201190);
		MyClass class3 = new MyClass(offering3, "A-");
		student.addToMyClass(class3);

		//Course 4
		Course course4 = new Course("Buried Cities & Lost Tribes", "ANTH", "125", 4);
		Offering offering4 = new Offering(course4,12544,201220);
		MyClass class4 = new MyClass(offering4, "C-");
		student.addToMyClass(class4);

		//Course 5
		Course course5 = new Course("Programming with Objects", "CS", "140", 4);
		Offering offering5 = new Offering(course5,10428,201220);
		MyClass class5 = new MyClass(offering5, "D");
		student.addToMyClass(class5);

		//Course 6
		Course course6 = new Course("Calculus II", "MATH", "222", 4);
		Offering offering6 = new Offering(course6,11094,201220);
		MyClass class6 = new MyClass(offering6, "A");
		student.addToMyClass(class6);
		//Course 7
		Course course7 = new Course("Intro Topics In Computer Science", "CS", "101", 4);
		Offering offering7 = new Offering(course7,10039,201290);
		MyClass class7 = new MyClass(offering7, "C+");
		student.addToMyClass(class7);

		//Course 8
		Course course8 = new Course("Comp Sys I:Machine Org", "CS", "120", 4);
		Offering offering8 = new Offering(course8,22837,201290);
		MyClass class8 = new MyClass(offering8, "F");
		student.addToMyClass(class8);

		//Course 9
		Course course9 = new Course("Pop, Rock, And Soul Musics", "MUS", "115", 4);
		Offering offering9 = new Offering(course9,10165,201190);
		MyClass class9 = new MyClass(offering9, "P");
		student.addToMyClass(class9);

		System.out.printf("Student gpa: %.3f\n",student.gpa());
	}
}
