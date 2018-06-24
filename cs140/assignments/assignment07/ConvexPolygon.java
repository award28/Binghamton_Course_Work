package assignment07;

import java.awt.Point;
import java.util.ArrayList;

public class ConvexPolygon extends Polygon {

	public ConvexPolygon(Point... arg) {
		super(arg);
		// TODO Auto-generated constructor stub
		
		if (arg.length > 2 && !isConvex()) {
			throw new IllegalArgumentException("Points do not form a convex polygon");
		}
	}
	
	public double getArea() {
		ArrayList<Point> list = (ArrayList<Point>) getPoints().clone();
		list.add(list.get(0)); 
		double area;
		double totalX = 0;
		double totalY = 0;
		
		for(int i = 0; i < list.size()-1; i++) {
			totalX += (list.get(i).getX()*list.get(i+1).getY());
			totalY += (list.get(i).getY()*list.get(i+1).getX());
		}
		
		area = (totalX - totalY)/2;
		
		return Math.abs(area);
	}
}