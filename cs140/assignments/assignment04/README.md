Assignment 4 Due on Friday October 2nd
===

Lab exam in Lab October 1st

Class exam in class October 8th.

Here is the class Rhombus dicussed in class on Friday. There is some new code in the main method
and there are some methods missing. Also some exceptions are inserted to handle bad cases.

```java
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
        // NOTE if percent is 50 then the sideLength would become sideLength + sideLength/2
        // IF percent IS NEGATIVE, DECREASE THE sideLength BY (-percent)%
        // IF percent IS -100, sideLength BECOMES 0.0
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
```

Here is the Driver from Friday's class:

```java
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
		System.out.println(Rhombus.getAreaOfRhombus(200, Math.PI/6));
	}

}
```

QUESTIONS.

* Complete the `resize` and `getAreaOfRhombus` methods in Rhombus
* Add tests to Driver for `resize`, `reshapeRadians` and `reshapeDegrees`, including tests that show the exceptions are thrown when
bad arguments are used.
* Write a class `RhombusStore` that has two fields: a private field `storage`, which is an array of `Rhombus`, and an `int` called `size`.
`storage` is initially an array of `length` 10.
* Import java.util.Arrays
* Do not write a constructor, Java gives us a default constructor.
* Write a method `public void add(Rhombus r)` which add `r` at the next open space in `storage` and makes `storage` bigger if there is not
enough space. Here is how: (i) assign `r` to the array `storage` at index `size`; (ii) increment `size` by 1; (iii) if `size` is equal to
`storage.length`, make `storage` 50% bigger using

```java
storage = Arrays.copyOf(storage, storage.length + storage.length/2);
```

* Provide a getter method for `size` BUT CALL IT `public int size()`
* Write  `public Rhombus get(int i)` that returns the element in `storage` at index `i` but the first instruction is

```java
		if(i < 0 || i >= size) {
			throw new IndexOutOfBoundsException(i + " can only be from 0 to size-1");
		}
```

* Here is the tricky one: write a method `public void insert(int i, Rhombus r)`, which makes an _extra_ space in `storage`
at index `i` and places `r` there. First if `i` is equal to `size`, just call `add(r)`. THE REST IS IN AN ELSE: Start with a range check:

```java
		if(i < 0 || i > size) {
			throw new IndexOutOfBoundsException(i + " can only be from 0 to size");
		}
```

Now write a for loop from `j = size-1` down to `i` (including `i`), decrementing `j` by 1 on each loop, and in the loop copy the element in
`storage` at index `j` TO the index `j+1`.

Next put `r` in `storage` at index `i` and increment `size`.

Finally if `size` is now equal to `storage.length`, use the same code to grow `storage` by 50% that we used in the `add` method.

* Write a class `Tester` and in the `main` method, do the following:

 - make an object `store` of type RhombusStore
 - in a for loop with counter `i` from 1 to `i < 21` add new Rhombus(i, 45). That will add ~~10~~ 20 different Rhombus objects to the RhombusStore.
 - in a second for loop for `i` from 0 to `i < store.size()`, print (_not_ println) `store.get(i).getSide() + " "` and observe
 whether the `add` method has worked.
 - do a println
 - you shold have

```
1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 15.0 16.0 17.0 18.0 19.0 20.0
```

 - in a for loop from 'i = 22` to `i < 33`, call `store.insert(5, new Rhombus(i, 45)`. Print out the contents of `store` as you did in the second loop
 and observe if the method behaved correctly.
 - you should have

 ```
 1.0 2.0 3.0 4.0 5.0 32.0 31.0 30.0 29.0 28.0 27.0 26.0 25.0 24.0 23.0 22.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 15.0 16.0 17.0 18.0 19.0 20.0
 ```