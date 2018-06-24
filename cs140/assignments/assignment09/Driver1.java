package assignment09;

import java.awt.Rectangle;
import java.util.ArrayList;

public class Driver1 {
	
	public static void main(String[] args) {
		ArrayList<Rectangle> list = new ArrayList<Rectangle>();
		list.add(new Rectangle(6,4));
		list.add(new Rectangle(6,6));
		list.add(new Rectangle(6,5));
		Measurer09 meas = c -> ((Rectangle)c).getWidth()*((Rectangle)c).getHeight();
		
		System.out.println("Average value: " + Measurer09.average(list, meas));
		System.out.println("Expected value: 30");
		System.out.println("Maximum value: " + Measurer09.maximum(list, meas));
		System.out.println("Expected value: 36");
		
		ArrayList<String> list1 = new ArrayList<String>();
		list1.add("Hello");
		list1.add("Not a Rectangle");
		list1.add("Also not one");
		
		try {
			System.out.println(Measurer09.average(list1, meas));
		}
		catch(Exception e) {
			System.out.println("ClassCastException expected for average");
		}
		
		try {
			System.out.println(Measurer09.maximum(list1, meas));
		}
		catch(Exception e) {
			System.out.println("ClassCastException expected for maximum");
		}
	}
}
