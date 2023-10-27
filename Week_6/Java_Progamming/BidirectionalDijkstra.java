import java.util.*;

class Node implements Comparable<Node> {
    int id;
    int dist;

    public Node(int id, int dist) {
        this.id = id;
        this.dist = dist;
    }

    @Override
    public int compareTo(Node other) {
        return Integer.compare(this.dist, other.dist);
    }
}

public class BidirectionalDijkstra {
    static ArrayList<ArrayList<Node>> graph;
    static int n;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        int m = scanner.nextInt();

        graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt() - 1;
            int v = scanner.nextInt() - 1;
            int w = scanner.nextInt();
            graph.get(u).add(new Node(v, w));
        }

        int s = scanner.nextInt() - 1;
        int t = scanner.nextInt() - 1;

        int result = bidirectionalDijkstra(s, t);
        System.out.println(result);
    }

    public static int bidirectionalDijkstra(int s, int t) {
        int[] distS = new int[n];
        int[] distT = new int[n];

        Arrays.fill(distS, Integer.MAX_VALUE);
        Arrays.fill(distT, Integer.MAX_VALUE);

        distS[s] = 0;
        distT[t] = 0;

        PriorityQueue<Node> pqS = new PriorityQueue<>();
        PriorityQueue<Node> pqT = new PriorityQueue<>();

        pqS.add(new Node(s, 0));
        pqT.add(new Node(t, 0));

        while (!pqS.isEmpty() || !pqT.isEmpty()) {
            int minDistS = processQueue(pqS, distS, distT);
            int minDistT = processQueue(pqT, distT, distS);

            if (minDistS != Integer.MAX_VALUE && minDistT != Integer.MAX_VALUE) {
                int shortestPath = minDistS + minDistT;
                return shortestPath;
            }
        }

        return -1;
    }

    public static int processQueue(PriorityQueue<Node> pq, int[] dist, int[] otherDist) {
        if (!pq.isEmpty()) {
            Node node = pq.poll();
            int u = node.id;
            int uDist = node.dist;

            for (Node neighbor : graph.get(u)) {
                int v = neighbor.id;
                int w = neighbor.dist;

                if (uDist > dist[u]) {
                    continue;
                }
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.add(new Node(v, dist[v]));

                    if (otherDist[v] != Integer.MAX_VALUE) {
                        return dist[v] + otherDist[v];
                    }
                }
            }
        }
        return Integer.MAX_VALUE;
    }
}
