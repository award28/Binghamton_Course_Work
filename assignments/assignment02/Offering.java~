package assignment02;

public class Offering implements Comparable<Offering> {

	private Course course;
	private int CRN;
	private int semester;

	public Offering (Course course, int CRN, int semester){
	
		this.course = course;
		this.CRN = CRN;
		this.semester = semester;
	}
	
	public Course getCourse() {
		return this.course;
	}
	
	public int getCRN() {
		return this.CRN;
	}
	
	public int getSemester() {
		return this.semester;
	}

	public int getNumCredits(){
		return course.getNumCredits();	
	}

	public int compareTo(Offering other) {
       			if(other == null) return - 1;
       			return semester - other.semester;
   	}	
}
