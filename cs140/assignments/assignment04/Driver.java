package assignment04;
public class Driver {
    public static void main(String[] args) {
        System.out.println(Rhombus.FORTY_FIVE_DEGREES);
        Rhombus test = new Rhombus(100, 45);
        Rhombus test2 = new Rhombus(50, 60);
        System.out.println(test.getAcuteAngle());
        System.out.println(test.getArea());
        System.out.println(test2.getArea());
        Rhombus[] array = {test, test2, null};
        array[2] = new Rhombus(200,30);
        for(Rhombus r : array) {
            System.out.println(r.getArea());
        }
        System.out.println(test.getAreaOfRhombus(200, Math.PI/6));

	double[] resizeTest = {50.0, 10.0, 0.0, -100.0, -10.0};

	//Testing the resize method
	for(int i = 0; i < resizeTest.length; i++) {
		test = new Rhombus(100, 45);
		test.resize(resizeTest[i]);
		System.out.println(i+1 + " resize test--> " + test.getArea());
	}
	//Testing the reshapeRadians method
	test.reshapeRadians(Math.PI/5);
	System.out.println("Reshape radians test--> " + test.getArea());
	//Testing the reshapeDegrees method
	test.reshapeDegrees(80);
	System.out.println("Reshape degrees test--> " + test.getArea());

    }
}
