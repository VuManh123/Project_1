//JAVA
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

@SuppressWarnings({"unchecked", "deprecation"})
// Ford-Fulkerson
public class MaxFlow {
    static int maxFlow(int[][] capacity, int source, int dest) {
        int n = capacity.length;
        int[][] residualCapacity = new int[n][n];
        // Khoi tao bang gia tri ma tran kha nang canh
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                residualCapacity[i][j] = capacity[i][j];
            }
        }

        int[] parent = new int[n];
        int maxFlow = 0;

        while (true) {
            boolean[] visited = new boolean[n];
            Queue<Integer> queue = new LinkedList<>();
            queue.add(source);
            visited[source] = true;
            parent[source] = -1;

            while (!queue.isEmpty()) {
                int u = queue.poll();

                for (int v = 0; v < n; v++) {
                    if (!visited[v] && residualCapacity[u][v] > 0) {
                        queue.add(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }

            if (visited[dest]) {
                int pathFlow = Integer.MAX_VALUE;
                for (int v = dest; v != source; v = parent[v]) {
                    int u = parent[v];
                    pathFlow = Math.min(pathFlow, residualCapacity[u][v]);
                }

                for (int v = dest; v != source; v = parent[v]) {
                    int u = parent[v];
                    residualCapacity[u][v] -= pathFlow;
                    residualCapacity[v][u] += pathFlow;
                }

                maxFlow += pathFlow;
            } else {
                break;
            }
        }
        return maxFlow;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int N = scanner.nextInt();
        int M = scanner.nextInt();

        int s = scanner.nextInt();
        int t = scanner.nextInt();

        int[][] capacity = new int[N][N];

        for (int i = 0; i < M; i++) {
            int u = scanner.nextInt() - 1;
            int v = scanner.nextInt() - 1;
            int c = scanner.nextInt();
            capacity[u][v] += c;
        }

        int maxFlow = maxFlow(capacity, s - 1, t - 1);
        System.out.println(maxFlow);

        scanner.close();
    }
}
