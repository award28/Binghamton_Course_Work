package pippin;

public class Memory {

	public static final int DATA_SIZE = 512;
	private int changedIndex = -1;
	private int[] data = new int[DATA_SIZE];

	public int getData(int index) {
		return data[index];
	}

	public void setData(int index, int value) {
		data[index] = value;
		changedIndex = index;
	}

	public int getChangedIndex() {
		return changedIndex;
	}

	int[] getDataArray() {
		return data;
	}

	public void clear() {
		for (int i = 0; i < DATA_SIZE; i++) {
			data[i] = 0;
		}
		changedIndex = -1;
	}
}
