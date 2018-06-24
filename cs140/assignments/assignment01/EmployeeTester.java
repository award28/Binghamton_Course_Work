package assignment01;

import java.time.LocalDate;

public class EmployeeTester{
	public static void main(String[]args){
		LocalDate dob1 = LocalDate.of(1996,1,26);
		Gender gen1 = Gender.FEMALE;
		Person futureEmployee = new Person("Debbie", "Chusit", "902478925", gen1, dob1);
		Employee employee1 = new Employee(futureEmployee, "Oracle", 123456);
		
		System.out.println("Employee name: \t\t" + employee1.getFirstNames() + " " +
		employee1.getLastNames());
		System.out.println("Employee Gender: \t" + employee1.getGender());
		System.out.println("Employee DOB: \t\t" + employee1.getDateOfBirth());
		employee1.increaseSalary(25);
		System.out.println("Employee Salary: \t" + employee1.getSalary());
	}
}
	
