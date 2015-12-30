package lab04;

public class Refrigerator {
	WaterJug[] waterJugs;
	int numOfWJ;
	int index = 0;
	
	public Refrigerator(int numOfWJ) {
		this.waterJugs = new  WaterJug[numOfWJ];
	}

	public void insertWaterJug(WaterJug wj) {
		if(wj != null) {
			waterJugs[index] = wj;
			index++;
		}
	}

	public int collect (int ml) {
		int totalRemoved = 0;

		for(int i = 0; i < waterJugs.length; i++) {
			totalRemoved += waterJugs[i].pourOut(ml);
		}
		return totalRemoved;
	}

	public void restock (int ml) {
		for(int i = 0; i < waterJugs.length; i++) {
			waterJugs[i].fillUp(ml);
		}
	}
}
