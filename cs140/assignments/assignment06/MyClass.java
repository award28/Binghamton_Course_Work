package assignment06;

public class MyClass implements Comparable<MyClass>{

	private Offering course;
	private double qualityPoints;
	private int gpaCredits;
	private boolean failed;

	public MyClass(Offering cls, String letterGrd) {

		this.course = cls;
		this.gpaCredits = cls.getNumCredits();
		this.qualityPoints = QPointsCalculator.points(letterGrd.toUpperCase(), gpaCredits);

		if (letterGrd.equalsIgnoreCase("P")){
			this.gpaCredits = 0;
		}
		else if (letterGrd.equalsIgnoreCase("F")){
			this.failed = true;
			this.gpaCredits = 0;
		}
	}

	public double getQualityPoints() {
		return this.qualityPoints;
	}

	public int getGpaCredits() {
		return this.gpaCredits;
	}

	public int compareTo(MyClass other) {
	        if(other == null) return -1;
        	return course.compareTo(other.course);
    	}

	public void modifyRepeat(MyClass other) {
		if(course.getCourse().getRubric().equals(other.course.getCourse().getRubric()) && course.getCourse().getNumber().equals(other.course.getCourse().getNumber())) {
			if(course.getSemester() > other.course.getSemester() && !other.failed) {
				qualityPoints = 0;
				gpaCredits = 0;
			}
		}
	}
}
