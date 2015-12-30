package assignment05;
import java.util.Arrays;

public class Tester1 {


	public static void main(String[] args) {
		long[] arrTest1 = {};
		long[] arrTest2 = null;
		long[] arrTest3 = {57438L, 90574L, 025247L, 753425L, 457802L, 95724052L, 74807L};
		long[] arrTest4 = {10, 0, 0, 15, 20, 4, 8, 6, 7, 100};

		Question1 test1 = new Question1(arrTest1.length);
		Question1 test2 = new Question1(0);
		Question1 test3 = new Question1(arrTest3.length);
		Question1 test4 = new Question1(arrTest4.length);		

		test1.insert(arrTest1);		
		test2.insert(arrTest2);
		test3.insert(arrTest3);
		test4.insert(arrTest4);

		System.out.println(Arrays.toString(test1.multiples(2)));
		System.out.println(Arrays.toString(test2.multiples(3)));
		System.out.println(Arrays.toString(test3.multiples(5)));
		System.out.println(Arrays.toString(test4.multiples(4)));
		
		}
}
