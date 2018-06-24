package assignment07;

import java.util.ArrayList;

public class Student {
	private Person person;
	private String major;
	private boolean hasAmerHist;
	private ArrayList<GenEd> genedList = new ArrayList<>();
	
	public Student(Person p, String maj, boolean b) {
		this.person = p;
		this.major =  maj;
		this.hasAmerHist = b;
	}
	
	public void addGenEd(GenEd genEd) {
		genedList.add(genEd);
	}
	
	public String getName() {
		return person.getName();
	}
	
	public void setMajor(String maj) {
		this.major = maj;
	}
	
	public String auditGenEd() {
		Auditor audit = new Auditor(genedList, hasAmerHist);
		
		if(major.equalsIgnoreCase("Computer Science") || major.equalsIgnoreCase("Nursing")){
			audit = new Auditor1FL(genedList, hasAmerHist);
		}
		else if(major.toLowerCase().indexOf("engineering") > 0) {
			audit = new Auditor0FL(genedList, hasAmerHist);
		}
		
		return audit.missingGeneds().toString();
	}
	
}
