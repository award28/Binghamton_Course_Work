package assignment06;
import java.util.HashMap;
import java.util.Map;
public class QPointsCalculator {
    public static double points(String letterGrade, int credits) {
        Map<String, Double> map = new HashMap<>();
        map.put("A", 4.0);
        map.put("A-", 3.7);
        map.put("B+", 3.3);
        map.put("B", 3.0);
        map.put("B-", 2.7);
        map.put("C+", 2.3);
        map.put("C", 2.0);
        map.put("C-", 1.7);
        map.put("D", 1.0);
        map.put("P", 0.0);
        map.put("F", 0.0);
        if(map.containsKey(letterGrade.toUpperCase())) {
            return map.get(letterGrade.toUpperCase())*credits;
        } else {
            throw new IllegalArgumentException("Invalid Letter Grade");
        }
    }
}
