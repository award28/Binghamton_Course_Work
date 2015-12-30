package lab04;

public class Driver {
	
	public static void main(String[] args) {
		
		Refrigerator fridge = new Refrigerator(5);
		int totalCollected = 0;
		
		WaterJug wj1 = new WaterJug();
		WaterJug wj2 = new WaterJug();
		WaterJug wj3 = new WaterJug();
		WaterJug wj4 = new WaterJug();
		WaterJug wj5 = new WaterJug();

		wj1.fillUp(100);
		wj2.fillUp(100);
		wj3.fillUp(100);
		wj4.fillUp(100);
		wj5.fillUp(100);

		fridge.insertWaterJug(wj1);
		fridge.insertWaterJug(wj2);
		fridge.insertWaterJug(wj3);
		fridge.insertWaterJug(wj4);
		fridge.insertWaterJug(wj5);

		totalCollected += fridge.collect(25);

		System.out.println(totalCollected);	

		System.out.println(wj1.getMilliliters());

		fridge.restock(25);

		System.out.println(wj1.getMilliliters());
	}
}
