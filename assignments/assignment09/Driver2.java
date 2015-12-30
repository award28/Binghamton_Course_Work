package assignment09;

import java.awt.Rectangle;
import java.util.ArrayList;

public class Driver2 {
	
	public static void main(String[] args) {
		ArrayList<Rectangle> list = new ArrayList<Rectangle>();
		list.add(new Rectangle(6,5));
		list.add(new Rectangle(6,6));
		list.add(new Rectangle(6,4));
		Measurer09Gen<Rectangle> meas = c -> ((Rectangle)c).getWidth()*((Rectangle)c).getHeight();

		
		System.out.println("Average value: " + Measurer09Gen.average(list, meas));
		System.out.println("Expected value: 30");
		System.out.println("Maximum value: " + 
		Measurer09Gen.maximum(list, meas).getWidth()*Measurer09Gen.maximum(list, meas).getHeight());
		System.out.println("Expected value: 36");
		
		ArrayList<String> list1 = new ArrayList<String>();
		list1.add("Hello");
		list1.add("Not a Rectangle");
		list1.add("Also not one");
		
		try {
			System.out.println("Average output: " + Measurer09Gen.average(list1, str->str.length()));
			System.out.println("Expected: 10.6 repeating");
		}
		catch(Exception e) {
			System.out.println("ClassCastException expected for average");
		}
		
		try {
			System.out.println("Maximum output: " + Measurer09Gen.maximum(list1, String::length));
			System.out.println("Expected: Not a Rectangle");
		}
		catch(Exception e) {
			System.out.println("ClassCastException expected for maximum");
		}
	}
}
