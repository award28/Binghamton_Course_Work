package assignment01;

import java.time.LocalDate;

public class Person {
	private String firstNames;
	private String lastNames;
	private String socialSecurityNumber;
	private Gender gender;
	private LocalDate dateOfBirth;
	public Person(String firstNames, String lastNames, String socialSecurityNumber, Gender gender, LocalDate dateOfBirth){

		this.firstNames = firstNames;
		this.lastNames = lastNames;
		this.socialSecurityNumber = socialSecurityNumber;
		this.gender = gender;
		this.dateOfBirth = dateOfBirth;
	}

	public String getFirstNames(){
		return firstNames;
	}

	public String getLastNames(){
		return lastNames;
	}

	public String getSocialSecurityNumber(){
		return socialSecurityNumber;
	}

	public Gender getGender(){
		return gender;
	}

	public LocalDate getDateOfBirth() {
		return dateOfBirth;
	}

	public void setFirstNames(String newFirstName) {
		firstNames = newFirstName;
	}

	public void setLastNames(String newLastName) {
		lastNames = newLastName;
	}

	public void setGender(Gender newGender) {
		gender = newGender;
	}

	public void setDateOfBirth(LocalDate date) {
		dateOfBirth = date;
	}

	public boolean isOlderThan(Person other){
		return dateOfBirth.isBefore(other.dateOfBirth);
	}

	public int getAgeInYears(){
		LocalDate today = LocalDate.now();
		int ageInYears = 0;

		if (today.isBefore(dateOfBirth)){

			int currentMonth = today.getMonthValue();
			int currentDay = today.getDayOfMonth();
			int currentYear = today.getYear();
			int birthMonth = dateOfBirth.getMonthValue();
			int birthDay = dateOfBirth.getDayOfMonth();
			int birthYear = dateOfBirth.getYear();
			ageInYears = currentYear-birthYear;

			if (currentMonth < birthMonth){
				ageInYears = ageInYears - 1;
			}

			else if (currentMonth == birthMonth){

				if (currentDay < birthDay){
					ageInYears = ageInYears - 1;
				}
			}
		}
		else {
			ageInYears = -1;
		}
		return ageInYears;		
	}
}

