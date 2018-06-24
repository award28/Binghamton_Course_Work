package assignment05;

public class Tester2 {
	
	public static void main(String[] args) {

		//Line
		double[] arrTest1 = {1.0, 1.0, 1.0, 1.0};
		//Triangle
		double[] arrTest2 = {1.0, 2.0, 1.0, 1.0};
		//Triangle
		double[] arrTest3 = {1.0, 1.0, 2.0, 1.0};
		//Square
		double[] arrTest4 = {2.0, 3.0, 2.0, 3.0};
		//Rectangle
		double[] arrTest5 = {1.0, 4.0, 1.0, 4.0};
		//Rhombus
		double[] arrTest6 = {2.0, 3.0, 1.0, 2.0};
		//Parallelogram
		double[] arrTest7 = {1.0, 3.0, 4.0, 6.0};
		//Trapezoid
		double[] arrTest8 = {6.0, 1.0, 3.0, 2.0};
		//Symmetrical Trapezoid
		double[] arrTest9 = {2.0, 4.0, 1.0, 5.0};		

		Quadrilateral test1 = new Quadrilateral(arrTest1);
		Quadrilateral test2 = new Quadrilateral(arrTest2);
		Quadrilateral test3 = new Quadrilateral(arrTest3);
		Quadrilateral test4 = new Quadrilateral(arrTest4);
		Quadrilateral test5 = new Quadrilateral(arrTest5);
		Quadrilateral test6 = new Quadrilateral(arrTest6);
		Quadrilateral test7 = new Quadrilateral(arrTest7);
		Quadrilateral test8 = new Quadrilateral(arrTest8);
		Quadrilateral test9 = new Quadrilateral(arrTest9);

		System.out.println(test1.form());
		System.out.println(test2.form());
		System.out.println(test3.form());
		System.out.println(test4.form());
		System.out.println(test5.form());
		System.out.println(test6.form());
		System.out.println(test7.form());
		System.out.println(test8.form());
		System.out.println(test9.form());
	}
}
