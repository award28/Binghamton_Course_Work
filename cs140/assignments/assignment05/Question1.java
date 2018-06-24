package assignment05;

public class Question1 {
	private long[] array;
	
	public Question1(int n) {
		if(n <= 0) {
			array = new long[0];
		}
		else {
			array = new long[n];
		}
	}
	
	public void insert(long[] some) {
		if(!(some == null || some.length == 0)) {
			for(int i = 0; i < some.length || i < array.length; i++) {
				array[i] = some[i];
			}
		}
	}
	/** Description of multiples(int n)
	*
	* Test the objects of array to see if they're an exact multiple of n. If n is
	* not zero it checks the array to get the number of exact multiples, and then
	* makes the array multiples that length. It then sets the indeces of that 
	* array to the exact multiples. Then multiples() returns the array multiples.
	* If n is 0, multiples() returns an empty array.
	*
	*@author	Austin Ward
	*@version	1.0 Build 5 Oct 3, 2015.
	*@param n	Integer to test the arrays indeces for exact multiples of n.
	*@return	Returns an array of exact multiples w/ regards to n.
	*/
	public long[] multiples(int n) {
		long[] multiples;
		int numOfExacts = 0;
		int j = 0;

		if(n != 0) {
			for(int i = 0; i < array.length; i++) {
				if(array[i] % n == 0) {
					numOfExacts++;
				}
			}
			multiples = new long[numOfExacts];

			for(int i = 0; i < array.length; i++) {
				if(array[i] % n == 0) {
					multiples[j] =  array[i];
					j++;
				}
			}
		}
		else {
			multiples = new long[0];
		}
		return multiples;
	}
}
