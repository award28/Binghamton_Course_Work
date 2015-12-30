package lab09;

public class Edge implements Comparable<Edge> {
    public final int from;
    public final int to;
    /**
     * Create an edge from node `from` to node `to`
     */
    public Edge(int from, int to) {
        this.from = from;
        this.to = to;
    }

    public int compareTo(Edge other) {
        int d = this.from - other.from;
        return d != 0 ? d : this.to - other.to;
    }

    public String toString() {
        return "(" + this.from + ", " + this.to + ")";
    }
}