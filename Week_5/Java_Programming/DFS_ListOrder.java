import java.util.*;
public class DFS_ListOrder {
    /*Sap xep tu lon den be
    Su dung danh sach kep
    Use stack*/
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); // Number of nodes
        int m = sc.nextInt(); // Number of edges

        List<List<Integer>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            graph.get(u - 1).add(v);
            graph.get(v - 1).add(u);
        }

        List<Integer> visitedNodes = dfs(graph, n);

        // Print the sequence of visited nodes
        for (int node : visitedNodes) {
            System.out.print(node + " ");
        }
    }

    public static List<Integer> dfs(List<List<Integer>> graph, int n) {
        List<Integer> visited = new ArrayList<>();
        boolean[] isVisited = new boolean[n];

        for (int i = 0; i < n; i++) {
            if (!isVisited[i]) {
                dfsRecursive(graph, i, isVisited, visited);
            }
        }
        return visited;
    }

    private static void dfsRecursive(List<List<Integer>> graph, int node, boolean[] isVisited, List<Integer> visited) {
        isVisited[node] = true;
        visited.add(node + 1);

        for (int neighbor : graph.get(node)) {
            if (!isVisited[neighbor - 1]) {
                dfsRecursive(graph, neighbor - 1, isVisited, visited);
            }
        }
    }
}
