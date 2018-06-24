package assignment01;

import java.time.LocalDate;

public class Employee{
		private Person employee;
		private String CompanyName;
		private double salary;
		public Employee(Person employee, String CompanyName, double salary){
			this.employee = employee;
			this.CompanyName = CompanyName;
			this.salary = salary;
		}

		public String getCompanyName(){
			return CompanyName;
		}

		public double getSalary(){
			return salary;
		}

		public String getFirstNames() {
			return employee.getFirstNames();
		}

		public LocalDate getDateOfBirth() {
			return employee.getDateOfBirth();
		}

		public String getLastNames(){
			return employee.getLastNames();
		}

		public String getSocialSecurityNumber(){
			return employee.getSocialSecurityNumber();
		}

		public Gender getGender(){
			return employee.getGender();
		}

		public void increaseSalary(double percentIncrease){
			percentIncrease = 1 + (percentIncrease * .01);
			salary = salary * percentIncrease;
 		}


}
