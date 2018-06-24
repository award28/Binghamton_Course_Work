package assignment01;

import java.time.LocalDate;

public class PersonTester{

	public static void main(String[]args){
	
		LocalDate dob1 = LocalDate.of(1995,8,29);
		Gender gen1 = Gender.MALE;
		Person person1 = new Person("Austin", "Ward", "102619851", gen1, dob1);

		LocalDate dob2 = LocalDate.of(1968,6,9);
		Gender gen2 = Gender.MALE;
		Person person2 = new Person("Marty", "McFly", "990231013", gen2, dob2);
		
		LocalDate dob3 = LocalDate.of(2016,10,22);
		Gender gen3 = Gender.FEMALE;
		Person person3 = new Person("Emmett", "Brown", "201021620", gen3, dob3);

		System.out.println("Name: \t\t" + person1.getFirstNames() + " " + 
		person1.getLastNames());
		System.out.println("Gender: \t" + person1.getGender());
		System.out.println("Date of Birth: \t" + person1.getDateOfBirth());
		System.out.println(person1.isOlderThan(person2) + "\n");

		System.out.println("Name: \t\t" + person2.getFirstNames() + " " +
		person2.getLastNames());
		System.out.println("Gender: \t" + person2.getGender());
		System.out.println("Date of Birth: \t" + person2.getDateOfBirth());
		System.out.println(person2.isOlderThan(person3) + "\n");

		System.out.println("Name: \t\t" + person3.getFirstNames() + " " +
		person3.getLastNames());
		System.out.println("Gender: \t" + person3.getGender());
		System.out.println("Date of Birth: \t" + person3.getDateOfBirth());
		System.out.println(person3.isOlderThan(person1) + "\n");
	}


}
