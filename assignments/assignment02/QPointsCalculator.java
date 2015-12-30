package assignment02;

public class QPointsCalculator{

	public static double points(String letterGrade, int credits){
		
		double points = 0.0;

		if(letterGrade.equals("A")){
			points = 4.0*credits;
		}
		else if(letterGrade.equalsIgnoreCase("A-")){
			points = 3.7*credits;
		}
		else if(letterGrade.equalsIgnoreCase("B+")){
			points = 3.3*credits;
		}
		else if(letterGrade.equalsIgnoreCase("B")){
			points = 3.0*credits;
		}
		else if(letterGrade.equalsIgnoreCase("B-")){
			points = 2.7*credits;
		}
		else if(letterGrade.equalsIgnoreCase("C+")){
			points = 2.3*credits;
		}
		else if(letterGrade.equalsIgnoreCase("C")){
			points = 2.0*credits;
		}
		else if(letterGrade.equalsIgnoreCase("C-")){
			points = 1.7*credits;
		}
		else if(letterGrade.equalsIgnoreCase("D")){
			points = 1.0*credits;
		}
		else if(!("P".equalsIgnoreCase(letterGrade) || "F".equalsIgnoreCase(letterGrade))){
			throw new IllegalArgumentException("Invalid Letter Grade");
		}
		return points;
	}
}
