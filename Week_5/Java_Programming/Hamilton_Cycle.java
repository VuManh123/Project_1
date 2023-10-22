import java.util.Scanner;

public class Hamilton_Cycle {

    static final int maxn = 101;
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int T = sc.nextInt();
        while (T-- > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            int[][] adj = new int[maxn][maxn]; // Ma tran ke cua do thi
            int[] deg = new int[maxn]; // Bac cua dinh
            boolean[] isFree = new boolean[maxn]; // Dinh chua use
            int[] circuit = new int[maxn];

            for (int i = 1; i <= m; i++) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                adj[u][v]++;
                adj[v][u]++;
                deg[u]++;
                deg[v]++;
            }

            for (int i = 1; i <= n; i++) {
                isFree[i] = true;
            }
            circuit[1] = 1;

            if (!checkHamiltonGraph(n, deg)) {
                System.out.println(0);
            } else {
                findHamiltonCircuit(2, n, adj, circuit, isFree);
                boolean isHamiltonian = true;
                for (int i = 1; i <= n; i++) {
                    if (circuit[i] == 0) {
                        isHamiltonian = false;
                        break;
                    }
                }
                System.out.println(isHamiltonian ? 1 : 0);
            }
        }
    }

    public static boolean checkHamiltonGraph(int n, int[] deg) {
        for (int u = 1; u <= n; u++) {
            if (deg[u] < 2) { //Check bac cua dinh phai lon nhon bang 2
                return false;
            }
        }
        return true;
    }

    //Use DFS
    public static void findHamiltonCircuit(int i, int n, int[][] adj, int[] circuit, boolean[] isFree) {
        for (int v = 1; v <= n; v++) {
            if (isFree[v] && adj[circuit[i - 1]][v] > 0) {
                circuit[i] = v;
                if (i < n) {
                    isFree[v] = false;
                    findHamiltonCircuit(i + 1, n, adj, circuit, isFree);
                    isFree[v] = true;
                }
            }
        }
    }
}
