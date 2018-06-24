package assignment07;

import static org.junit.Assert.assertEquals;

import java.awt.Point;

import org.junit.Test;

public class TriangleTest {


    @Test(expected = IllegalArgumentException.class) 
    public void testTriangle() {
        new Triangle(new Point(1,1), new Point(2,2), new Point(3,3));
    }
    
    @Test
    public void areaTestTriangle() {
    	Triangle areaTest = new Triangle(new Point(1,4), new Point(4,4), new Point(4,1));
    	
    	assertEquals(4.5, areaTest.getArea(), .1);
    }
}
