package assignment05;

public class Quadrilateral {
	private double topLeft;
	private double topRight;
	private double bottomLeft;
	private double bottomRight;
	
	public Quadrilateral(double[] arr) {
		if(arr.length != 4) {
			throw new IllegalArgumentException("Must provide 4 values");
		}
		topLeft = Math.min(arr[0], arr[1]);
		topRight = Math.max(arr[0], arr[1]);
		bottomLeft = Math.min(arr[2], arr[3]);
		bottomRight = Math.max(arr[2], arr[3]);
	}

	public String form() {
		String form = "error";

		if(topLeft == topRight && bottomLeft == bottomRight) {
			form = "Line";
		}
		else if((topLeft == topRight && bottomLeft != bottomRight) || 
		(topLeft != topRight && bottomLeft == bottomRight)) {
			form = "Triangle";
		}
		else if(topRight == bottomRight && topLeft == bottomLeft) {
			if(topRight - topLeft > 1) {
				form = "Rectangle";
			}
			else {
				form = "Square";
			}
		}
		else if(topRight - bottomRight == topLeft - bottomLeft) {
			if(topRight - topLeft > 1) {
				form = "Parallelogram";
			}
			else {
				form = "Rhombus";
			}
		}
		else if((topRight - topLeft < bottomRight - bottomLeft) ||
		(topRight - topLeft > bottomRight - bottomLeft)) {
			if (bottomLeft - topLeft != topRight - bottomRight) {
				form = "Trapezoid";
			}
			else {
				form = "Symmetric Trapezoid";
			}
		}
				
			
			
			
		
		return form;
	}
} 
