package assignment09;

import java.util.ArrayList;

public interface Measurer09Gen<T> {
    double measure(T arg);
    
    /**
     * Computes the average measure of the elements
     * of an ArrayList of Measurable elements
     * @param list an ArrayList of Rectangle elements
     * @param meas Computes the area of a rectangle
     * @return the average of all the areas
     */
    static <V> double average(ArrayList<V> list, Measurer09Gen<V> meas) {
		double average = 0;
    	
		for(V i : list) {
    		average += meas.measure(i);
    	}
		average = average/list.size();
		
    	return average;
    }
    
    /**
     * Compute the object type with maximum measure in
     * an ArrayList of Measurable elements and returning 
     * the first elements largest measure if there is a
     * tie
     * @param list an ArrayList of Rectangle elements
     * @param meas an ArrayList of Measurable elements
     * @return the object type with the maximum measure
     */
    static <V> V maximum(ArrayList<V> list, Measurer09Gen<V> meas) {
    	double maximum = meas.measure(list.get(0));
    	V retVal = null;
    	for(V i : list) {
    		if(maximum < meas.measure(i)) {
    			maximum = meas.measure(i);
    			retVal = i;
    		}
    	}
    	return retVal;
    }
}