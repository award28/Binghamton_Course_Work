package assignment10;

import java.util.ArrayList;
import java.util.Collections;

public class ABubbleSortUtility {

    public <E extends Comparable<E>> void aBubbleSort(ArrayList<E> list) {
        boolean changeOccurred = true;
        E temp;
        
        while(changeOccurred) {
        	changeOccurred = false;
	        for (int i = 0; i < list.size() - 1; i++) {
	        	if(list.get(i).compareTo(list.get(i+1)) > 0) {
	        		temp = list.get(i);
	        		list.set(i, list.get(i+1));
	        		list.set(i+1, temp);
	        		changeOccurred = true;
	        	}
	        }
        }     
    }
    
    public void test() {
        System.out.println("---------STARTING\n");
        RandomNameGenerator helper = new RandomNameGenerator();
        ArrayList<String> names = new ArrayList<String>();
        
        for(int i = 0; i < 50; i++) {
       	 names.add(helper.getRandomName());
       	 //System.out.println(names.get(i));
        }       
        System.out.println("---------\nNOW SORT THEM\n");
        
        aBubbleSort(names);

        for(int i = 0; i < 50; i++) {
       	 //System.out.println(names.get(i));
        } 
    }  
}