package assignment09;

import java.util.ArrayList;

public interface Measurer09 {
    double measure(Object arg);
    
    static double average(ArrayList<?> list, Measurer09 meas) {
		double average = 0;
    	
    	for(int i = 0; i < list.size(); i++) {
    		average += meas.measure(list.get(i));
    	}
    	average = average/list.size();
    	
    	return average;
    }
    
    static double maximum(ArrayList<?> list, Measurer09 meas) {
    	double maximum = meas.measure(list.get(0));
    	
    	for(int i = 0; i < list.size(); i++) {
    		if(maximum < meas.measure(list.get(i))) {
    			maximum = meas.measure(list.get(i));
    		}
    	}
    	return maximum;
    }
}