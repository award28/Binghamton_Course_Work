package assignment02;

public class Course{

	private String name;
	private String rubric;
	private String number;
	private int numCredits;

	public Course (String name, String rubric, String number, int numCredits) {

		this.name = name;
		this.rubric = rubric;
		this.number = number;
		this.numCredits = numCredits;
		}

		public String getName(){
			return this.name;
		}

		public String getRubric(){
			return this.rubric;
		}

		public String getNumber(){
			return this.number;
		}
	
		public int getNumCredits(){
			return this.numCredits;
		}

}
