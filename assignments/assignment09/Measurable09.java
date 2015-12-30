package assignment09;

import java.util.ArrayList;

public interface Measurable09 {

	double getMeasure();

	/**
	 * Computes the average measure of the non-null  
	 * elements of an array of Measurable elements.
	 * @param array an array of Measurable elements.
	 * @return the average of the measures of the non-null  
	 * elements in array or 0 if the array is null, empty, 
	 * or filled with null elements.
	 */
	static double average(Measurable09[] array) {
		double retVal = 0.0;
		int nonNullCount = 0;
		if(array != null && array.length > 0) {
			for(Measurable09 m : array) {
				if(m != null) {
					retVal += m.getMeasure();
					nonNullCount++;
				}
			}
			if(nonNullCount > 0)
				retVal /= nonNullCount;
		}
		return retVal;
	}

	/**
	 * Computes the average measure of the non-null 
	 * elements of an ArrayList of Measurable elements.
	 * @param list an ArrayList of Measurable elements.
	 * @return the average of the measures of the 
	 * non-null elements in list or 0 if the list is null, 
	 * empty, or filled with null elements.
	 */
	static double average(ArrayList<Measurable09> list) {
		double retVal = 0.0;
		int nonNull = 0;
		for(int i = 0; i < list.size(); i++) {
			if(list.get(i) != null) {
				retVal += list.get(i).getMeasure();
				nonNull++;
			}
		}
		retVal = retVal/nonNull;
		return retVal;
	}

	/**
	 * Compute the element with maximum measure in an 
	 * ArrayList of Measurable elements, ignoring null 
	 * elements and returning the first element of largest 
	 * measure if there is a tie. 
	 * @param list an ArrayList of Measurable elements
	 * @return the first non-null element with largest measure 
	 * in list. Returns null if list is null, empty, or filled  
	 * with null elements.
	 */
	static Measurable09 maximum(ArrayList<Measurable09> list) {
		Measurable09 retVal = null;
		double maxValue = list.get(0).getMeasure();
		for(int i = 0; i < list.size(); i++) {
			if(list.get(i) != null && list.get(i).getMeasure() > maxValue) {
				maxValue = list.get(i).getMeasure();
				retVal  = list.get(i);
			}
		}
		return retVal;
	}

	/**
	 * Determines if all the elements in an array are 
	 * instances of the given class (and not instances of a 
	 * subclass of the given class or any other class).
	 * @param array an array of elements of a reference type.
	 * @param cls a specific Class.
	 * @return true if all the elements of the array are 
	 * instantiated from the class cls and false otherwise.
	 */
	static boolean uniform(Object[] array, Class<?> cls) {
		boolean retVal = true;
		for(int i = 0; i < array.length; i++) {
			if(array[i].getClass() != cls) {
				retVal = false;
			}
		}
		return retVal;
	}
}