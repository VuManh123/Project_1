import java.util.*;

class Graph {
    private int V;
    private List<Edge>[] adj;

    public Graph(int V) {
        this.V = V;
        adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }
    }

    public void addEdge(int u, int v, int w) {
        adj[u - 1].add(new Edge(u, v, w));
    }

    public int shortestPath(int s, int t) {
        int[] distance = new int[V];
        Arrays.fill(distance, Integer.MAX_VALUE);
        distance[s - 1] = 0;

        PriorityQueue<Edge> minHeap = new PriorityQueue<>();
        minHeap.add(new Edge(s, s, 0));

        while (!minHeap.isEmpty()) {
            Edge curr = minHeap.poll();
            int u = curr.to;

            if (u == t) {
                return distance[u - 1];
            }

            for (Edge edge : adj[u - 1]) {
                int v = edge.to;
                int weight = edge.weight;

                if (distance[u - 1] != Integer.MAX_VALUE && distance[u - 1] + weight < distance[v - 1]) {
                    distance[v - 1] = distance[u - 1] + weight;
                    minHeap.add(new Edge(u, v, distance[v - 1]));
                }
            }
        }

        return -1; // No path from s to t
    }
}

class Edge implements Comparable<Edge> {
    int from, to, weight;

    public Edge(int from, int to, int weight) {
        this.from = from;
        this.to = to;
        this.weight = weight;
    }

    @Override
    public int compareTo(Edge other) {
        return Integer.compare(this.weight, other.weight);
    }
}

public class ShortestPath_ver1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Graph graph = new Graph(n);

        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            int w = scanner.nextInt();
            graph.addEdge(u, v, w);
        }

        int s = scanner.nextInt();
        int t = scanner.nextInt();

        int shortestPath = graph.shortestPath(s, t);
        System.out.println(shortestPath);
    }
}
