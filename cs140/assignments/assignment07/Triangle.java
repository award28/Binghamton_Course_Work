package assignment07;

import java.awt.Point;

public class Triangle extends ConvexPolygon {

	public Triangle(Point... arg) {
		super(arg);
		// TODO Auto-generated constructor stub
		
		if (arg.length != 3) {
			throw new IllegalArgumentException("The points do not form a triangle");
		}
	}
}
