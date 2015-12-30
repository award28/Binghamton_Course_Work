package assignment04;

public class Tester {

	public static void main(String[] args){
		RhombusStore store = new RhombusStore();
		
		for(int i = 1; i < 21; i++) {
			store.add(new Rhombus(i,45));
		}
		
		for(int i = 0; i < store.size(); i++){
			System.out.print(store.get(i).getSide() + " ");
		}

		System.out.println();

		for(int i = 22; i<33; i++) {
			store.insert(5, new Rhombus(i,45));
		}
		
		for(int i = 0; i < store.size(); i++) {
			System.out.print(store.get(i).getSide() + " ");
		}
		System.out.println();
	}
}
		
