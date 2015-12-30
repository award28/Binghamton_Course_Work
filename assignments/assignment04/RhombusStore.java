package assignment04;

import java.util.Arrays;

public class RhombusStore {
	private Rhombus[] storage = new Rhombus[10];
	int size;

	public void add(Rhombus r) {
		if(size == storage.length){
			storage = Arrays.copyOf(storage, storage.length + storage.length/2);
		}
		else {
			storage[size] = r;
			size++;
		}
	}

	public int size() {
		return size;
	}
	
	public Rhombus get(int i) {
		if(i < 0 || i >= size) {
			throw new IndexOutOfBoundsException(i + " can only be from 0 to size-1");
        	}
		
		return storage[i];
	}

	public void insert(int i, Rhombus r) {
		if(i < 0 || i > size) {
            		throw new IndexOutOfBoundsException(i + " can only be from 0 to size");
        	}
		
		if(i == size) {
			add(r);
		}
		else {
			for(int j  = size-1; j >= i; j--){
				storage[j+1] = storage[j];
			}
			storage[i] = r;
			size++;
			if(storage.length == size) {
				storage = Arrays.copyOf(storage, storage.length + storage.length/2);
			}
		}

	}

	
}
