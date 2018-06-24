package assignment10;

import java.util.ArrayList;
import java.util.Collections;

public class MagicSquare {

	public int[][] build(ArrayList<Integer> list) {
		int len = (int)Math.round(Math.sqrt(list.size()));
		int ROW_COUNT = len;
		int COLUMN_COUNT = len;
		int[][] array = new int[ROW_COUNT][COLUMN_COUNT]; 
		if(len*len == list.size()) {
			//For rows
			for(int i = 0; i < len; i++) {
				//For columns
				for(int j = 0; j < len; j++) {
					array[i][j] = list.get(len*i+j);
				}
			}
		}		
		return array;	
	}

	
	public boolean isMagicSquare(ArrayList<Integer> list) {
		ArrayList<Integer> listCopy = new ArrayList<>();
		boolean retVal = true;
		int len = (int)Math.round(Math.sqrt(list.size()));
		int[][] array;
		int[] rows;
		int[] columns;
		int matches = 0;
		int tempRow = 0;
		int tempColumn = 0;
		
		for(int i = 0; i < list.size(); i ++) {
			listCopy.add(list.get(i));
		}	
		Collections.sort(listCopy);
	
		for(int i = 0; i < listCopy.size(); i++) {
			for(int j = listCopy.size() - 1; j > i; j--) {
				if(listCopy.get(i) != listCopy.get(j)) {
					retVal = true;				
				}
				else {
					matches++;
				}
			}
		}				
		array = build(list);
				
		if(len*len == list.size()) {
			rows = new int[len];
			columns= new int[len];
			
			for(int i = 0; i < len; i++) {		
				for(int j = 0; j < len; j++) {
					tempRow += array[i][j];
					tempColumn += array[j][i];	
				}
				rows[i] = tempRow;
				columns[i] = tempColumn;
				tempRow = 0;
				tempColumn = 0;				
			}
			
			for(int i = 0; i < len-1; i++) {
				if(rows[i] != rows[i+1] || columns[i] != columns[i+1]) {
					retVal = false;
				}
				
			}
		}
		else {
			retVal = false;
		}
		if(matches > 0) {
			retVal = false;
		}
		return retVal;
	}
	
	public void test() {
		ArrayList<Integer> squareTest1 = new ArrayList<>();
		squareTest1.add(16);
		squareTest1.add(3);
		squareTest1.add(2);
		squareTest1.add(13);
		squareTest1.add(5);
		squareTest1.add(10);
		squareTest1.add(11);
		squareTest1.add(8);
		squareTest1.add(9);
		squareTest1.add(6);
		squareTest1.add(7);
		squareTest1.add(12);
		squareTest1.add(4);
		squareTest1.add(15);
		squareTest1.add(14);
		squareTest1.add(1);
		
		ArrayList<Integer> squareTest2 = new ArrayList<>();
		squareTest2.add(15);
		squareTest2.add(3);
		squareTest2.add(2);
		squareTest2.add(13);
		squareTest2.add(5);
		squareTest2.add(10);
		squareTest2.add(11);
		squareTest2.add(8);
		squareTest2.add(9);
		squareTest2.add(6);
		squareTest2.add(7);
		squareTest2.add(12);
		squareTest2.add(4);
		squareTest2.add(15);
		squareTest2.add(14);
		squareTest2.add(1);
		
		ArrayList<Integer> squareTest3 = new ArrayList<>();
		squareTest3.add(17);
		squareTest3.add(3);
		squareTest3.add(2);
		squareTest3.add(13);
		squareTest3.add(5);
		squareTest3.add(10);
		squareTest3.add(11);
		squareTest3.add(8);
		squareTest3.add(9);
		squareTest3.add(6);
		squareTest3.add(7);
		squareTest3.add(12);
		squareTest3.add(4);
		squareTest3.add(15);
		squareTest3.add(14);
		squareTest3.add(1);
		
		ArrayList<Integer> squareTest4 = new ArrayList<>();
		squareTest4.add(17);
		squareTest4.add(24);
		squareTest4.add(1);
		squareTest4.add(8);
		squareTest4.add(15);
		squareTest4.add(23);
		squareTest4.add(5);
		squareTest4.add(7);
		squareTest4.add(14);
		squareTest4.add(16);		
		squareTest4.add(4);
		squareTest4.add(6);
		squareTest4.add(13);
		squareTest4.add(20);
		squareTest4.add(22);		
		squareTest4.add(10);
		squareTest4.add(12);
		squareTest4.add(19);
		squareTest4.add(21);
		squareTest4.add(3);		
		squareTest4.add(11);
		squareTest4.add(18);
		squareTest4.add(25);
		squareTest4.add(2);
		squareTest4.add(9);		
		
		System.out.println("4x4 magic Square: " + isMagicSquare(squareTest1));
		System.out.println("Expected: true");
		System.out.println("4x4 non magic Square(two of the same ints): " + isMagicSquare(squareTest2));
		System.out.println("Expected: false");
		System.out.println("4x4 non magic Square(Rows and columns sums aren't equal): " + isMagicSquare(squareTest3));
		System.out.println("Expected: false");
		System.out.println("5x5 magic Square: " + isMagicSquare(squareTest4));
		System.out.println("Expected: true");
	}
	
	public static void main(String[] args) {
		MagicSquare firstTest = new MagicSquare();
		firstTest.test();
	}
}
