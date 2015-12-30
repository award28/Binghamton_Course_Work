package assignment04;

public class Rhombus {
    private double sideLength;
    private double acuteAngle;
    public static final double FORTY_FIVE_DEGREES = Math.PI/4;

    public Rhombus(double side, double degrees) {
        if (side < 0) throw new IllegalArgumentException("cannot make side negative");
        if (degrees <= 0 || degrees > 90) throw new IllegalArgumentException("angle must be acute");
        sideLength = side;
        acuteAngle = Math.toRadians(degrees);
    }

    public void resize(double percent) {
        if (percent < -100) throw new IllegalArgumentException("cannot make side negative");
        // IF percent IS POSITIVE, INCREASE THE sideLength BY percent%
	if(percent > 0 && percent != 50) {
		sideLength = sideLength * (1 + (0.01 * percent));
	}
        // NOTE if percent is 50 then the sideLength would become sideLength + sideLength/2
	else if(percent == 50) {
		sideLength = sideLength + sideLength/2;
	}
        // IF percent IS -100, sideLength BECOMES 0.0
	else if(percent == -100) {
		sideLength = 0.0;
	}
	// IF percent IS NEGATIVE, DECREASE THE sideLength BY (-percent)%
	else {
		sideLength = sideLength * (1 + (0.01 * percent));
	}
    }

    public void reshapeRadians(double newAngle) {
        if (newAngle <= 0 || newAngle > Math.PI/2) throw new IllegalArgumentException("angle must be acute");
        acuteAngle = newAngle;
    }

    public void reshapeDegrees(double degrees) {
        if (degrees <= 0 || degrees > 90) throw new IllegalArgumentException("angle must be acute");
        acuteAngle = Math.toRadians(degrees);
    }

    public double getSide() {
        return sideLength;
    }

    public double getAcuteAngle() {
        return acuteAngle;
    }

    public double getArea() {
        return sideLength*sideLength*Math.sin(acuteAngle);
    }

    public static double getAreaOfRhombus(double side, double radians) {
        if(side < 0 || radians < 0 || radians > Math.PI/2)
            throw new IllegalArgumentException("side must positive and radians must be between 0 and pi/2");
        // RETURN THE AREA OF A Rhombus WITH SIDE LENGHT "side" AND
        // THE ACUTE ANGLE EQUAL TO "radians"
	return side*side*Math.sin(radians);
    }

    public static void main(String[] args) {
        //side = 5;
        Rhombus test = new Rhombus(100, 25);
//static methods in a class only have DIRECT access to 
//the static fields or static methods of a class.
//They only have access to instance fields and
//instance methods INDIRECTLY through a reference to
//an instance of the class (an object of the class)
        System.out.println(FORTY_FIVE_DEGREES);
        System.out.println(getAreaOfRhombus(200,FORTY_FIVE_DEGREES));
        System.out.println(Rhombus.getAreaOfRhombus(200,FORTY_FIVE_DEGREES));
        System.out.println(Rhombus.FORTY_FIVE_DEGREES);
        System.out.println(test.sideLength);
        System.out.println(test.getArea());
    }
}
