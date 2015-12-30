package lab09;

import java.util.Set;
import java.util.TreeSet;
import java.util.Map;
import java.util.HashMap;

public class Graph {
    private Set<Integer> nodes;
    private Set<Edge> edges;

    /**
     * Create a graph from a map of edges
     * @param edges a mapping of edges, where the key k holding value v denotes
     *              an edge from node k to node v
     * @return the Graph object representing the same structure given by the edges
     */
    public static Graph fromMap(Map<Integer, Integer> edges) {
        Graph graph = new Graph();
    	
    	for (Integer i: edges.keySet()) {
        	graph.addEdge(i, edges.get(i));
        }
    	
    	return graph;
    }

    public Graph() {
        this.nodes = new TreeSet<>();
        this.edges = new TreeSet<>();
    }

    public void addEdge(int f, int t) {
        this.edges.add(new Edge(f, t));
    }

    public void addNode(int n) {
        this.nodes.add(n);
    }

    public Set<Edge> getEdges() {
        return this.edges;
    }

    public Set<Integer> getNodes() {
        return this.nodes;
    }

    /**
     * Determines if a node can be reached from another node
     * @param f the start node
     * @param t the node we are trying to reach from `f`
     * @return true  if the node `t` can be reached from the node `f`
     *         false otherwise
     */
    public boolean reachable(int f, int t) {
        Map<Integer, Set<Integer>> m = getConnections();
    	return  m.get(f).contains(t);
    }

    /**
     * Gets a map of connections among the nodes in this Graph
     * @return a map between nodes and the nodes you can reach from them,
     *         where the map having key k and value v means that node k
     *         is connected to (is reachable by) all nodes in the set v
     */
    public Map<Integer, Set<Integer>> getConnections() {
        Map<Integer, Set<Integer>> m = new HashMap<>();
        
        if()
    	
    	return m;
    }
}