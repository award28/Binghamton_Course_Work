package lab09;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;

public class Driver {

    public static boolean test(String exp, Object act) {
        System.out.println("Expecting: " + exp);
        System.out.println("Got:       " + act.toString());
        System.out.println("           -");
        return exp.equals(act.toString());
    }

    public static void main(String[] args) {
        List<Boolean> answers = new ArrayList<Boolean>();
        Map<Integer, Integer> emap = new HashMap<Integer, Integer>(){{
                put(2, 3);
                put(1, 4);
                put(5, 6);
                put(10, 11);
            }};
        Graph ge = Graph.fromMap(emap);
        System.out.println("--------");

        answers.add(test("[1, 2, 3, 4, 5, 6, 10, 11]", ge.getNodes()));
        answers.add(test("[(1, 4), (2, 3), (5, 6), (10, 11)]", ge.getEdges()));

        Graph g = new Graph();

        for (int i = 0; i < 20; ++i) {
            g.addNode(i);
        }

        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(10, 11);
        g.addEdge(10, 12);
        g.addEdge(11, 19);
        g.addEdge(12, 18);
        g.addEdge(18, 19);
        g.addEdge(3, 4);
        g.addEdge(5, 3);

        System.out.println("--------");

        answers.add(test("true", g.reachable(0, 1)));
        answers.add(test("true", g.reachable(0, 2)));
        answers.add(test("false", g.reachable(0, 19)));
        answers.add(test("true", g.reachable(1, 2)));
        answers.add(test("true", g.reachable(10, 19)));
        answers.add(test("false", g.reachable(3, 10)));
        answers.add(test("true", g.reachable(5, 4)));

        Map<Integer, Set<Integer>> m = g.getConnections();

        System.out.println("--------");

        answers.add(test("[1, 2]", m.get(0)));
        answers.add(test("[2]", m.get(1)));
        answers.add(test("[4]", m.get(3)));
        answers.add(test("[11, 12, 18, 19]", m.get(10)));
        answers.add(test("[19]", m.get(11)));
        answers.add(test("[18, 19]", m.get(12)));
        answers.add(test("[]", m.get(13)));
        answers.add(test("[]", m.get(8)));
        answers.add(test("[3, 4]", m.get(5)));

        int correct = (int) answers.stream().filter(a -> a).count();
        System.out.printf("%2d/%2d correct\n", correct, answers.size());
    }
}