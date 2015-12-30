package assignment07;

import static org.junit.Assert.*;
import java.awt.Point;
import org.junit.Test;

public class ConvexPolygonTest {

    @Test(expected = IllegalArgumentException.class) 
    public void testConvexPolygon() {
        new ConvexPolygon(new Point(1,6), new Point(2,1), new Point(3,3), new Point(4,1), new Point(5,6));
    }
    
    @Test
    public void test2ConvexPolygon() {
        new ConvexPolygon(new Point(1,3), new Point(2,6), new Point(4,6), new Point(5,3), new Point(3,1));
    }
    
    @Test
    public void areaTestConvexPolygon() {
    	ConvexPolygon areaTest = new ConvexPolygon(new Point(1,4), new Point(4,4), new Point(4,1),  new Point(1,1));
    	
    	assertEquals(9, areaTest.getArea(), .1);
    }
}
