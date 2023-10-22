import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class MST_Kruskal {
    /*Cau truc du lieu Union-find + Kruskal
    * Kruskal: Bat dau voi canh nho nhat (ko tao chu trinh)
    * Lap lai buoc tren den khi thu duoc (N-1) canh*/
    static class Edge{
        int src; // Nguon
        int dest; // Dich
        int weight; // Trong so
        public Edge(int src, int dest, int weight){
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }
    }
    static class Graph{
        int V; // So luong dinh
        int E; // So luong canh
        Edge[] edges;
        public Graph(int V, int E){
            this.E = E;
            this.V = V;
            edges = new Edge[E];
        }
    }
    static int find(int[] parent, int i) {
        if (parent[i] != i)
            parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    static void union(int[] parent, int[] rank, int x, int y) {
        int xRoot = find(parent, x);
        int yRoot = find(parent, y);

        if (xRoot != yRoot) {
            if (rank[xRoot] < rank[yRoot])
                parent[xRoot] = yRoot;
            else if (rank[xRoot] > rank[yRoot])
                parent[yRoot] = xRoot;
            else {
                parent[yRoot] = xRoot;
                rank[xRoot]++;
            }
        }
    }

    static int mstKruskal(Graph graph) {
        int V = graph.V;
        Edge[] result = new Edge[V];
        int e = 0, i = 0;

        Arrays.sort(graph.edges, (a, b) -> a.weight - b.weight);

        int[] parent = new int[V];
        int[] rank = new int[V];
        for (int v = 0; v < V; v++) {
            parent[v] = v;
            rank[v] = 0;
        }

        while (e < V - 1 && i < graph.E) {
            Edge nextEdge = graph.edges[i++];
            int x = find(parent, nextEdge.src);
            int y = find(parent, nextEdge.dest);

            if (x != y) {
                result[e++] = nextEdge;
                union(parent, rank, x, y);
            }
        }
        int minimumCost = 0;
        for (i = 0; i < e; i++)
            minimumCost += result[i].weight;

        return minimumCost;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int M = scanner.nextInt();

        Graph graph = new Graph(N, M);

        for (int i = 0; i < M; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            int w = scanner.nextInt();
            graph.edges[i] = new Edge(u - 1, v - 1, w);
        }

        int result = mstKruskal(graph);
        System.out.println(result);
    }
}
