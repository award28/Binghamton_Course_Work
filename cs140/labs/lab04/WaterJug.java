package lab04;

public class WaterJug {
	public int milliliters = 0;
	
	public int getMilliliters() {
		return milliliters;
	}

	public void fillUp(int ml) {
		milliliters += ml;
	}
	
	public int pourOut(int ml) {
		if(milliliters >= ml) {
			milliliters = milliliters - ml;
		}
		else {
			ml = 0;
		}
		
		return ml;
	}	
}
