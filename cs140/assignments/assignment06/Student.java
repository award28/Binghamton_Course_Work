package assignment06;

import java.util.ArrayList;

public class Student {

Person student;
ArrayList<MyClass> myClasses = new ArrayList<MyClass>();

	public Student(Person student){
		this.student = student;
	}

	public void addToMyClass(MyClass mc) {
	    	myClasses.add(mc);
	}

	public double gpa(){

		int totalGpaCredits = 0;
		double totalQualityPoints = 0;
		double gpa;
	
		for(int i = 0; i < myClasses.size(); i++){
			if(myClasses != null) {
				myClasses.get(i).getGpaCredits();
				totalGpaCredits += myClasses.get(i).getGpaCredits();
				totalQualityPoints += myClasses.get(i).getQualityPoints();
			}
		}
		
		if (totalGpaCredits == 0){
			gpa = 0;
		}
		else{
			gpa = totalQualityPoints / totalGpaCredits;
		}

	return gpa;
	}
}
