package assignment07;

import java.awt.Point;
import java.util.ArrayList;

public class Polygon {
    ArrayList<Point> points = new ArrayList<>();

    public Polygon(Point... arg){
        for(Point p : arg) {
        points.add(p);
        }
    }

    public boolean isConvex() {
        if (points.size()<3)
            return true;
        boolean sign=false;
        int n=points.size();
        for(int i=0;i<n;i++) {
            double dx1 = points.get((i+2)%n).x-points.get((i+1)%n).x;
            double dy1 = points.get((i+2)%n).y-points.get((i+1)%n).y;
            double dx2 = points.get(i).x -points.get((i+1)%n).x;
            double dy2 = points.get(i).y-points.get((i+1)%n).y;
            double zcrossproduct = dx1*dy2 - dy1*dx2;
            if(zcrossproduct == 0) return false;
            if (i==0) sign=zcrossproduct > 0;
            else if (sign!=(zcrossproduct > 0)) return false;
        }
        return true;
    }
    
    public ArrayList<Point> getPoints() {
    	return points;
    }
}
